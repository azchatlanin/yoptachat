#include <string>
#include <format>

#include "httplib.h"

#include "hack/logger/logger.hpp"

#include "helpers/inspector.hpp"
#include "helpers/function_manager.hpp"
#include "helpers/verification.hpp"
#include "helpers/execute.hpp"

namespace var
{
  inline const int PORT = 5000;
  inline const std::string HOST = "0.0.0.0";
  inline const std::string HEADER_FLAG_JSON = "application/json"; 
  inline const std::string HEADER_TOKEN = "TRS-server-token";
  inline const std::string HEADER_FUNCTION = "TRS-server-function";
}

namespace https
{
  class server : public httplib::Server
  {
    public:
      server() = default;
      ~server() = default;

    public:
      void init(std::string service_name, std::string url = "/")
      {
        m_service_name = service_name;
        API_URL = url;

        set_read_timeout(5, 0);
        set_write_timeout(5, 0);
        set_idle_interval(0, 1'000'000);
        set_payload_max_length(1024 * 1024 * 50); // 50MB
                                                  
        set_CORS();
        set_POST();
      }

      template<typename Function>
      void registration(std::string func_name, Function insp, Function func) 
      { 
        m_inspector.registration(func_name, insp);
        m_function_manager.registration(func_name, func); 
      }

      void run()
      {
        try 
        {
          hack::log(" ")(std::format("[{}]", m_service_name), "listen:", var::HOST, var::PORT);
          listen(var::HOST, var::PORT);
        }
        catch(std::exception& e)
        {
          hack::error(" ")("error server run:", e.what());
        }
        catch(...)
        {
          hack::error()("SUPPER ERROR!!! GOOD LUCK MY FRIEND!!! :)");
        }
      }

    private:
      std::string m_service_name { "base_service" };
      std::string API_URL { "/" };
      inspector m_inspector;
      function_manager m_function_manager;


    private:
      void set_CORS()
      {
        Options(R"(\*)", [](const auto& req, auto& res) { res.set_header("Allow", "POST, HEAD, OPTIONS"); });
        Options(API_URL, [](const auto& req, auto& res)
        {
          res.set_header("Access-Control-Allow-Origin", "*");
          res.set_header("Allow", "POST, HEAD, OPTIONS");
          res.set_header("Access-Control-Allow-Methods", "OPTIONS, HEAD, POST");
          res.set_header("Access-Control-Allow-Headers", 
              std::format("X-Requested-With, Content-Type, Accept, Origin, Authorization, {}, {}", var::HEADER_TOKEN, var::HEADER_FUNCTION).c_str());
        });
      }
      
      void set_POST()
      {
        Post(API_URL, [&](const httplib::Request& req, httplib::Response& res) {
          res.set_header("Access-Control-Allow-Origin", "*");
          res.set_header("Access-Control-Allow-Headers", "*");
          res.set_header("Access-Control-Allow-Methods", "POST");
          res.set_header("Access-Control-Allow-Credentials", "false");

          hack::transaction tr;

          try
          {
            tr.set_data(req);
            verification(m_inspector, m_function_manager, tr);
            execute(m_function_manager, tr);
          }
          catch(hack::exception& ex)
          {
            ex.transaction(tr);
            ex.service(m_service_name);
            ex.log();// это понеобходимости
            // Тут нужно осуществить логирование в БД 
          }

          res.set_content(nlohmann::to_string(tr.m_data.m_result), var::HEADER_FLAG_JSON); 
        });
      }
  };
}

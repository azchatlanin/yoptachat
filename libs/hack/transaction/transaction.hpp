#pragma once

#include <string>

#include "hack/security/uuid.hpp"
#include "hack/exception/exception.hpp"
#include "hack/utils/json_converter.hpp"

namespace hack
{
  namespace var
  {
    // ATTENITON!!!
    // данные переменные встречаются тут по ходу кода в разных файлах.
    // т.к. это пока разрабатывается и есть несколько вопросов, то когда эти вопросы будут решены
    // мы эти переменные сгрупируем в отдельный файл.
    const std::string NO_VALID_DATA = "no valid data";
    const std::string ALIEN_SYSTEM_ERROR = "alien system error";
  };

  // Данный класс является что-то типа контракта(одного) у grpc.
  // А точнее сущности, которая создается при вызове функции и передается до ее полного завершения.
  // Содержит в себе все необходимые данные для выполения этой вызванной функции.
  // Скорее всего ему тут не место. А нужно перенести обратно в сервер. Но это после решения вопросов.
  class transaction : public hack::utils::json_converter
  {
    public:
      transaction() : m_transaction_id { hack::security::generate_uuid() } { };
      ~transaction() = default;

    public:
      std::string m_transaction_id;

      struct passport
      {
        int m_id = -1000; // Эта сущность, которая зашифрована в токене. Например id организации
        std::string m_function_name;
        std::string m_token = "no token";
      } m_passport;

      struct data
      {
        JSON m_payload;
        JSON m_result {
          { "status", "completed" },
          { "result", "" }
        }; 
      } m_data;

    public:
      template<typename Request>
      void set_data(const Request& req)
      {
        set_function(req);
        set_token(req);
        set_payload(req);
      }

      JSON convert_to_json() override
      {
        JSON j;
        j["transaction_id"] = m_transaction_id;
        j["function_name"] = m_passport.m_function_name;
        j["token"] = m_passport.m_token;
        j["payload"] = m_data.m_payload;
        j["result"] = m_data.m_result;
        j["id"] = m_passport.m_id;

        return j;
      }

    private:
      template<typename Request>
      void set_function(const Request& req)
      {
        try
        {
          m_passport.m_function_name = req.get_header_value("TRS-server-function");
          if (m_passport.m_function_name.empty()) throw std::invalid_argument{ var::NO_VALID_DATA };
        }
        catch(std::exception& e)
        {
        }
        catch(...)
        {
          hack::exception ex; 
          ex.description(var::ALIEN_SYSTEM_ERROR); 
          throw ex;
        }
      }

      template<typename Request>
      void set_token(const Request &req)
      {
        try
        {
          m_passport.m_token = req.get_header_value("TRS-server-token");
          if (m_passport.m_token.empty()) throw std::invalid_argument{ var::NO_VALID_DATA };
        }
        catch(std::exception& e)
        {
          hack::exception ex;
          ex.description("dont get token from headers, because it system error, or maybe is field be empty");
          ex.system_error(e);
          throw ex;
        }
        catch(...)
        {
          hack::exception ex; 
          ex.description(var::ALIEN_SYSTEM_ERROR); 
          throw ex;
        }
      }

      template<typename Request>
      void set_payload(const Request &req)
      {
        if (req.body.empty()) return;
        try
        {
          m_data.m_payload = JSON::parse(req.body);
        }
        catch(const std::exception& e)
        {
          hack::exception ex;
          ex.description("Dont parser body from string");
          ex.system_error(e);
          throw ex; 
        }
        catch(...)
        {
          hack::exception ex;
          ex.description(var::ALIEN_SYSTEM_ERROR);
          throw ex; 
        }
      }
  };
}

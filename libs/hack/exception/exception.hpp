#pragma once

#include <experimental/source_location>

#define DEF_LINE() std::experimental::source_location::current().line()
#define DEF_LOCATION() std::experimental::source_location::current()

#include "hack/utils/color.hpp"
#include "hack/utils/using.hpp"
#include "hack/utils/json_converter.hpp"

namespace hack
{
  // Общий класс ошибки, которая выбьрасывается из любой точки проекта.
  // Досихпор находится в разработке и осмысливании как его луше сделать чтоб прям вот ....
  class exception : public utils::json_converter
  {
    public:
      exception(const std::experimental::source_location loc = DEF_LOCATION()) : m_location { loc } {}
      ~exception() = default;

    public:
      void message(const std::string v) noexcept { m_message = v; }
      void description(const std::string v) noexcept { m_description = v; }
      void system_error(const std::exception& e) noexcept { m_system_error = e.what(); }
      void service(const std::string v) noexcept { m_service = v; }

      template<typename Param>
      void params(std::string key, Param value) { m_params[key] = value; }

      // если что-то не значительное, но в больших обемах, то можно использовать этот метод
      // на выходе будет что-то типа { "arg_1" : 123, "arg_2" : "value" }
      template<typename... Args>
      void variadic_params(Args... args)
      {
        int i = 0;
        ([&] { m_params["arg_" + std::to_string(++i)] = args; }(), ...);      
      }

      template<typename Transaction>
      void transaction(Transaction& tr) 
      { 
        m_params["transaction"] = tr.convert_to_json(); 
        tr.m_data.m_result["status"] = "error";
        tr.m_data.m_result["result"] = m_message;
      }

      void log()
      {
        std::cout << utils::color::bold << utils::color::red <<"["+m_service+"] " << utils::color::reset
                  << m_location.file_name() << ":" 
                  << utils::color::italic << utils::color::yellow << m_location.function_name() << "()" << utils::color::reset
                  << utils::color::bold << utils::color::blue << "[" << m_location.line() << "]" << utils::color::reset << ": "
                  << m_message << std::endl;

        if (!m_description.empty())
          std::cout << utils::color::bold << utils::color::red <<"["+m_service+"] " << utils::color::reset
                    << m_location.file_name() << ":" 
                    << utils::color::italic << utils::color::yellow << m_location.function_name() << "()" << utils::color::reset
                    << utils::color::bold << utils::color::blue << "[" << m_location.line() << "]" << utils::color::reset << ": "
                    << m_description << std::endl;
        
        if (!m_system_error.empty())
          std::cout << utils::color::bold << utils::color::red <<"["+m_service+"] " << utils::color::reset
                    << m_location.file_name() << ":" 
                    << utils::color::italic << utils::color::yellow << m_location.function_name() << "()" << utils::color::reset
                    << utils::color::bold << utils::color::blue << "[" << m_location.line() << "]" << utils::color::reset << ": "
                    << m_system_error << std::endl;
      }

      JSON convert_to_json() override
      {
        JSON j;
        j["description"] = m_description;
        j["system_error"] = m_system_error;
        j["location"] = m_location.file_name();
        j["function_name"] = m_location.function_name();
        j["message"] = m_message;
        j["service"] = m_service;
        j["params"] = m_params;

        return j;
      }

    private:
      std::string m_message { "no valid data" };
      std::string m_description;
      std::string m_system_error;
      std::string m_service;
      std::experimental::source_location m_location;
      JSON m_params;
  };
}


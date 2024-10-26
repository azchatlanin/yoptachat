#pragma once

#include <map>
#include <functional>
#include <string>

#include "hack/exception/exception.hpp"
#include "hack/transaction/transaction.hpp"

namespace https
{
  // Каждая функция, которую мы вызываем на сервере принимает один параметр - hack::transaction.
  // Данный класс, вляется управленцем дял всех зарегестрированных в системе функций
  class function_manager
  {
    using functions = std::map<const std::string, std::function<void(hack::transaction&)>>;

    public:
      function_manager() = default;
      ~function_manager() = default;

    private:
      functions m_functions;

    public:
      void valid(std::string func_name) const
      { 
        if (m_functions.count(func_name) == 0)
        {
          hack::exception ex;
          ex.description("this function is not register in function manager.");
          throw ex; 
        }
      }
      
      template<typename Key, typename Function>
      void registration(const Key k, const Function f) noexcept
      {
        m_functions[k] = f;
      }

      void execute(hack::transaction& tr) 
      {
        m_functions[tr.m_passport.m_function_name](tr);
      }
  }; 
}

#pragma once

#include <string>
#include <map>
#include <functional>

#include "hack/exception/exception.hpp"
#include "hack/transaction/transaction.hpp"

namespace https
{
  // Громкоговорящее название :)
  class inspector
  {
    using functions = std::map<const std::string, std::function<void(hack::transaction&)>>;

    public:
      inspector() = default;
      ~inspector() = default;

    public:
      template<typename Key, typename Function>
      void registration(const Key k, const Function f) noexcept
      {
        m_functions[k] = f;
      }

      void valid(hack::transaction& tr) 
      {
        if (!valid(tr.m_passport.m_function_name))
        {
          hack::exception ex;
          ex.description("this function is not register in inspector.");
          throw ex; 
        }

        m_functions[tr.m_passport.m_function_name](tr);
      }

    private:
      bool valid(std::string func_name) const noexcept
      { 
        return m_functions.count(func_name) > 0; 
      }

    private:
      functions m_functions;
  };
}

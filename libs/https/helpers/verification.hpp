#pragma once

#include "hack/exception/exception.hpp"
#include "hack/transaction/transaction.hpp"

#include "inspector.hpp"
#include "function_manager.hpp"

namespace https
{
  // Общий метод для проверки зарегестрированных функций и их входящих параметров от клиента.
  inline void verification(inspector& ins, function_manager& fm, hack::transaction& tr)
  {
    try
    {
      fm.valid(tr.m_passport.m_function_name);
      ins.valid(tr); 
    } 
    catch (hack::exception& ex)
    {
      throw ex;
    }
    catch (std::exception& e) 
    { 
      hack::exception ex;
      ex.description("payload failed verification");
      ex.system_error(e);
      throw ex;
    }
    catch (...) 
    { 
      hack::exception ex;
      ex.description("is alien system error it can be very dangerous!!! good luck my friend!");
      throw ex;
    } 
  }
}

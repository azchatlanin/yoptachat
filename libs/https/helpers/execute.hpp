#pragma once

#include "hack/exception/exception.hpp"
#include "hack/transaction/transaction.hpp"

#include "function_manager.hpp"

namespace https
{
  inline void execute(function_manager& fm, hack::transaction& tr)
  { 
    try
    {
      fm.execute(tr); 
    } 
    catch (hack::exception& ex)
    {
      throw ex;
    }
    catch (std::exception& e) 
    { 
      hack::exception ex;
      ex.description("it can be very dangerous. this error when we execute function");
      ex.message("execute error");
      ex.system_error(e);
      throw ex;
    }
    catch (...) 
    { 
      hack::exception ex;
      ex.description("is alien system error it can be very dangerous!!! good luck my friend!");
      ex.message("execute error");
      throw ex;
    } 
  }
}

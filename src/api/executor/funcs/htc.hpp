#pragma once

#include "hack/transaction/transaction.hpp"

namespace executor
{
  inline void healthcheck(hack::transaction& tr)
  {
    tr.m_data.m_result["status"] = "ok";
    tr.m_data.m_result["result"] = "executor ok";
  }
}


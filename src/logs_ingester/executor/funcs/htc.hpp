#pragma once

#include "hack/transaction/transaction.hpp"
#include "hack/logger/logger.hpp"

namespace logs_ingester::executor
{
  inline void healthcheck(hack::transaction& tr)
  {
    tr.log();

    tr.m_data.m_result["status"] = "ok";
    tr.m_data.m_result["result"] = "executor ok";
  }
}


#pragma once

#include "hack/transaction/transaction.hpp"
#include "hack/utils/json_compare.hpp"

namespace logs_ingester::inspector::json_data
{
  inline auto healthcheck = R"(
    {
      "key": "value",
      "key_int": 1
    }
  )"_json;
}

namespace logs_ingester::inspector
{
  inline void healthcheck(hack::transaction& tr)
  {
    auto [ok, msg] = hack::json::compare(tr, json_data::healthcheck);
    if (!ok) 
    { 
      hack::exception ex;
      ex.description(msg); 
      throw ex; 
    }
  }
}

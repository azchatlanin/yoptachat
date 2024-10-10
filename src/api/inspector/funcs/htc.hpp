#pragma once

#include "hack/transaction/transaction.hpp"
#include "hack/utils/json_compare.hpp"

namespace inspector::json_data
{
  inline auto healthcheck = R"(
    {
      "key": "value",
      "key_int": 1
    }
  )"_json;
}

namespace inspector
{
  inline void healthcheck(hack::transaction& tr)
  {
    hack::json::compare(tr, json_data::healthcheck);
  }
}

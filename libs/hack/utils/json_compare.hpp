#pragma once

#include <utility>
#include <string>

#include "hack/utils/using.hpp"
#include "hack/string/string_concat_helper.hpp"

// простой сравниватель json-ов
namespace hack::json
{
  using compare_result = std::pair<bool, std::string>;

  namespace
  {
    inline compare_result compare_impl(JSON& target, JSON& comp)
    {
      if (target.empty())
        return { false, "payload is empty" };

      for (auto&& [key, comp_v] : comp.items())
      {
        if (comp_v.is_object()) 
        {
          auto [ok, k] = compare_impl(target[key], comp_v);
          if (!ok) return { ok, k };
        }

        if (target[key].type_name() != comp_v.type_name())
          return { false, hack::string::str_concat + "field - [" + key + "] is invalid."};
      }

      if (target.size() != comp.size()) return { false, "payload not competed" };

      return { true, "" };
    }
  }

  // HERE
  // можно поставить концепт на то , что структура Transaction
  // иеет необходимые поля и методы
  template<typename Transaction>
  inline compare_result compare(Transaction& base, JSON& comp)
  {
    return compare_impl(base.m_data.m_payload, comp);
  }
}

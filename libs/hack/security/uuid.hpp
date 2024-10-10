#pragma once

#include <uuid/uuid.h>
#include <regex>
#include <string>

namespace hack::security
{
  inline std::string generate_uuid()
  {
    std::string uuid;
    uuid_t uuid_obj;
    uuid_generate_time_safe(uuid_obj);
    char uuid_ch[UUID_STR_LEN]; 
    uuid_unparse_lower(uuid_obj, uuid_ch);
    std::stringstream ss;
    ss << uuid_ch;
    ss >> uuid;
    return uuid;
  }

  inline bool validate_uuid(const std::string& s)
  {
    static const std::regex e("^[0-9a-f]{8}-[0-9a-f]{4}-[0-5][0-9a-f]{3}-[089ab][0-9a-f]{3}-[0-9a-f]{12}$", std::regex_constants::icase);
    return std::regex_match(s, e);
  }
}


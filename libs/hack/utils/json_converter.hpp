// Данный интерфейс предназначен для более понятного и не меняющегося апи по преобразованию данных в json формат и обратно.
// Любой класс, который этого требует должен наследоваться от этого интерфейса чтобы не городить зоопарк разноименных для этого методов.
// Возможно в будущем я либо напишу рефлектор либо это будет вынесено в отдельную hack_cpp

#pragma once

#include "hack/utils/using.hpp"

namespace hack::utils
{
  struct json_converter
  {
    json_converter() = default;
    virtual ~json_converter() = default;
    virtual JSON convert_to_json() = 0;
  };
}


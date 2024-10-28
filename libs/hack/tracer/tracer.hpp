#pragma once

#include <condition_variable>
#include <queue>
#include <mutex>

#include "hack/exception/exception.hpp"

namespace hack
{
  // Интерфейс отвечающий за все виды отправки всех видов 
  // логов туда куда нужно.
  // Чтоб не плодить разнообразные методы - все логеры должны наследовать именнно этот класс
  // и передавать производный класс в сервер
  class tracer
  {
    public:
      tracer() = default;
      ~tracer() = default;

    public:
      virtual void add(hack::exception&& ex) = 0;
      virtual void process() = 0;

    protected:
      std::mutex m_mutex;
      std::condition_variable m_cond;
      std::queue<hack::exception> m_exceptions;
  };
}

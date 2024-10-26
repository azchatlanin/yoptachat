#pragma once

#include <condition_variable>
#include <queue>
#include <mutex>

#include "hack/exception/exception.hpp"

namespace https
{
  // Класс отвечающий за все виды отправки всех видов 
  // логов туда куда нужно.
  class tracer
  {
    public:
      tracer() = default;
      ~tracer() = default;

    public:
      void add(hack::exception&& ex) 
      {
        std::scoped_lock lock(m_mutex);
        m_exceptions.push(std::move(ex));
        m_cond.notify_one();
      }

      void process() 
      { 
        std::unique_lock l { m_mutex };
        m_cond.wait(l, [this]() { return !m_exceptions.empty(); });
        auto ex = std::move(m_exceptions.front());
        m_exceptions.pop();

        ex.log();
      }

    private:
      std::mutex m_mutex;
      std::condition_variable m_cond;
      std::queue<hack::exception> m_exceptions;
  };
}

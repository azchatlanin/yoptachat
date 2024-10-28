#pragma once

#include <condition_variable>
#include <queue>
#include <mutex>

#include "hack/tracer/tracer.hpp"

namespace logs_ingester::utils
{
  // Класс отвечающий за все виды отправки всех видов 
  // логов туда куда нужно.
  class tracer : public hack::tracer
  {
    public:
      tracer() = default;
      ~tracer() = default;

    public:
      void add(hack::exception&& ex) override
      {
        std::scoped_lock lock(m_mutex);
        m_exceptions.push(std::move(ex));
        m_cond.notify_one();
      }

      void process() override
      { 
        std::unique_lock l { m_mutex };
        m_cond.wait(l, [this]() { return !m_exceptions.empty(); });
        auto ex = std::move(m_exceptions.front());
        m_exceptions.pop();

        ex.log();
      }
  };
}


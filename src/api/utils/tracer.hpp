#pragma once

#include <condition_variable>
#include <queue>
#include <mutex>

#include "https/https.hpp"
#include "hack/tracer/tracer.hpp"

namespace api::utils
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


        httplib::Client cli("localhost:5001");

        httplib::Headers headers = {
          { "TRS-server-function", "healthcheck" },
          { "TRS-server-token", "internal_service_token" },
          { "Content-Type", https::var::HEADER_FLAG_JSON },
          { "Cookie", "unione_lang=ru" }
        };

        auto res = cli.Post("/api", headers, ex.convert_to_json().dump(), https::var::HEADER_FLAG_JSON);
      }
  };
}


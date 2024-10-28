#pragma once

#include "https/https.hpp"

#include "api/inspector/inspector.hpp" // IWYU pragma: keep
#include "api/executor/executor.hpp" // IWYU pragma: keep
#include "api/utils/tracer.hpp"

// API
namespace services::api
{
  inline void run()
  {
    https::server<::api::utils::tracer> srv;
    srv.init("API", "/api");
    srv.PORT = 5'000;

    srv.registration("healthcheck", ::api::inspector::healthcheck, ::api::executor::healthcheck);
    srv.run();
  }
}

// LOGS_INGESTER
#include "logs_ingester/inspector/inspector.hpp" // IWYU pragma: keep
#include "logs_ingester/executor/executor.hpp" // IWYU pragma: keep
#include "logs_ingester/utils/tracer.hpp"

namespace services::logs_ingester
{
  inline void run()
  {
    https::server<::logs_ingester::utils::tracer> srv;
    srv.PORT = 5'001;
    srv.init("LOGS_INGESTER", "/api");

    srv.registration("healthcheck", ::logs_ingester::inspector::empty, ::logs_ingester::executor::healthcheck);
    srv.run();
  }
}

#include "https/https.hpp"

#include "api/inspector/inspector.hpp" // IWYU pragma: keep
#include "api/executor/executor.hpp" // IWYU pragma: keep

auto main(int argc, char* args[]) -> int
{
  https::server srv;
  srv.init("API", "/api");

  srv.registration("healthcheck", inspector::healthcheck, executor::healthcheck);
  srv.run();
}

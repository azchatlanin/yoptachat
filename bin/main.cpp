#include "run.hpp"

auto main(int argc, char* args[]) -> int
{
  std::vector<std::thread> ths;
  ths.push_back(std::thread{ services::api::run });
  ths.push_back(std::thread{ services::logs_ingester::run });
  for (auto& th : ths)
    th.join();
}

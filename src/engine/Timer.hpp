#pragma once

#include <engine/Time.hpp>
#include <spdlog/spdlog.h>

namespace blocky
{
  struct Timer
  {
    Timer() : start{Time::millis()} {}

    ~Timer()
    {
      auto diff = Time::millis() - start;
      spdlog::info("Elapsed time: {}", diff);
    }

  private:
    Duration start;
  };
}
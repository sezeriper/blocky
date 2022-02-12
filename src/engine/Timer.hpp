#pragma once

#include <engine/Time.hpp>
#include <spdlog/spdlog.h>
#include <string_view>

namespace blocky
{
  struct Timer
  {
    Timer(std::string_view msg) : msg(msg), start{Time::millis()} {}

    ~Timer()
    {
      auto diff = Time::millis() - start;
      spdlog::info("{}: {}ms", msg, diff);
    }

  private:
    std::string_view msg;
    float start;
  };
}
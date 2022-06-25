#pragma once

#include <engine/gles2/Renderer.hpp>

#include <entt/entt.hpp>

#include <cstdint>

namespace blocky {
namespace Block {

enum class Type : std::uint8_t {
	AIR = 0,
	STONE = 1,
	DIR = 2,
};
}
}

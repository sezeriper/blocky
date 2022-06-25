#pragma once

#include <game/Block.hpp>

#include <glm/glm.hpp>
#include <spdlog/spdlog.h>
#include <FastNoiseLite.h>

#include <array>
#include <algorithm>

namespace blocky {
struct VoxelData {
	using Index = std::uint64_t;
	using Coord = glm::u64vec3;

	static constexpr Coord size{17, 256, 17};
	static constexpr Index voxelCount{size.x * size.y * size.z};

	static constexpr Index coordToIndex(const Coord& coord) {
		return coord.y + (coord.x * size.z * size.y) + (coord.z * size.y);
	}

	static constexpr Coord indexToCoord(Index index) {
		return { index / (size.z * size.y), (index % (size.z * size.y)) / size.z, index % size.z };
	}

	Block::Type& operator[](const Coord& coord) {
		return data[coordToIndex(coord)];
	}

	const Block::Type& operator[](const Coord& coord) const {
		return data[coordToIndex(coord)];
	}

	auto begin() { return data.begin(); }
	auto end() { return data.end(); }

private:
	std::array<Block::Type, voxelCount> data;
};

VoxelData generateVoxels(const glm::vec2& position) {
	VoxelData voxelData;

	FastNoiseLite noise;
	noise.SetFrequency(0.01f);

	for (float x = 0.0f; x < VoxelData::size.x; x += 1.0f) {
	for (float z = 0.0f; z < VoxelData::size.z; z += 1.0f) {
		const float noiseVal = noise.GetNoise(x + position.x, z + position.y);
		const float threshold = (noiseVal * 10.0f) + static_cast<float>(VoxelData::size.y) / 2.0f;
		for (float y = 0.0f; y < VoxelData::size.y; y += 1.0f) {
			voxelData[{x, y, z}] = static_cast<Block::Type>(threshold > y);
		}
	}
	}

	return voxelData;
}
}

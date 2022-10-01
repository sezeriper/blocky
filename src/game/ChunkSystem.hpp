#pragma once

#include <game/VoxelMesher.hpp>
#include <game/VoxelData.hpp>

#include <glm/glm.hpp>
#include <glm/gtx/hash.hpp>
#include <glm/gtx/norm.hpp>
#include <entt/entt.hpp>

#include <unordered_map>

namespace blocky {
struct ChunkSystem {
	using Coord = glm::i64vec2;
	static constexpr glm::vec2 chunkSize{VoxelData::size.x-1, VoxelData::size.z-1};

	void setViewDistance(float distanceInChunks) {
		viewDistanceInChunks = distanceInChunks;
		viewDistance = 8.0f + (16.0f * (viewDistanceInChunks - 1.0f));
		viewDistance2 = viewDistance * viewDistance;
	}

	void update(entt::registry& registry, const glm::vec3& playerPos) {
		const glm::vec2 playerPos2d{playerPos.x, playerPos.z};
		
		for (auto it = chunks.begin(); it != chunks.end();) {
			const auto& coord = it->first;
			const auto& chunk = it->second;

			if (!isVisible(coord, playerPos2d)) {
				const auto& mesh = registry.get<Renderer::Mesh>(chunk);
				Renderer::destroyBuffer(mesh.vertBuf);
				registry.destroy(chunk);
				it = chunks.erase(it);
			}
			else { ++it; }
		}
		
		const Coord start = globalToCoord(playerPos2d - viewDistance);
		const Coord end = globalToCoord(playerPos2d + viewDistance);

		for (std::int64_t x = start.x; x <= end.x; ++x) {
			for (std::int64_t y = start.y; y <= end.y; ++y) {
				const Coord coord{x, y};
				if (isVisible(coord, playerPos2d) && !chunks.contains(coord)) {
					chunks[coord] = instantiate(registry, coord);
				}
			}
		}
	}

private:
	std::unordered_map<Coord, entt::entity> chunks;
	VoxelMesher voxelMesher;

	float viewDistanceInChunks{10.0f};
	float viewDistance{8.0f + (16.0f * (viewDistanceInChunks - 1.0f))};
	float viewDistance2{viewDistance * viewDistance};

	entt::entity instantiate(entt::registry& registry, const ChunkSystem::Coord& coord) {
		auto entity = registry.create();

      	registry.emplace<ChunkSystem::Coord>(entity, coord);

      	const glm::vec2 pos = coordToGlobal(coord);
      	auto& trans = registry.emplace<Renderer::Transform>(entity, 1.0f);
      	trans = glm::translate(trans, {pos.x, 0.0f, pos.y});

		auto& voxelData = registry.emplace<VoxelData>(entity);
		voxelData = generateVoxels(pos);

		auto& mesh = registry.emplace<Renderer::Mesh>(entity);
		mesh = voxelMesher.generate(voxelData);

      	return entity;
	}

	bool isVisible(const Coord& coord, const glm::vec2& playerPos2d) const {
		const glm::vec2 pos = globalChunkCenter(coord);
		const float dist2 = glm::distance2(playerPos2d, pos);
		return dist2 <= viewDistance2;
	}

	constexpr static Coord globalToCoord(const glm::vec2& pos) {
		return glm::floor(pos / chunkSize);
	}

	constexpr static glm::vec2 coordToGlobal(const Coord& coord) {
		return static_cast<glm::vec2>(coord) * chunkSize;
	}

	constexpr static glm::vec2 globalChunkCenter(const Coord& coord) {
		return coordToGlobal(coord) + (chunkSize / 2.0f);
	}
};
}

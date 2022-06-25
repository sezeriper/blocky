#pragma once

#include <game/Block.hpp>
#include <game/VoxelData.hpp>

#include <engine/gles2/Renderer.hpp>

#include <glm/glm.hpp>

#include <vector>

namespace {
using namespace blocky;

enum class Face : std::size_t {
	BACK,
	RIGHT,
	TOP,
	BACK_REV,
	RIGHT_REV,
	TOP_REV,
};

constexpr std::array<std::array<glm::vec3, 4>, 6> faceVertPos {
	glm::vec3(1.0f, 0.0f, 1.0f), // Back Face
	glm::vec3(0.0f, 0.0f, 1.0f),
	glm::vec3(0.0f, 1.0f, 1.0f),
	glm::vec3(1.0f, 1.0f, 1.0f),

	glm::vec3(1.0f, 0.0f, 0.0f), // Right Face
	glm::vec3(1.0f, 0.0f, 1.0f),
	glm::vec3(1.0f, 1.0f, 1.0f),
	glm::vec3(1.0f, 1.0f, 0.0f),

	glm::vec3(0.0f, 1.0f, 0.0f), // Top Face
	glm::vec3(1.0f, 1.0f, 0.0f),
	glm::vec3(1.0f, 1.0f, 1.0f),
	glm::vec3(0.0f, 1.0f, 1.0f),

	glm::vec3(1.0f, 1.0f, 1.0f), // Back Face Reversed
	glm::vec3(0.0f, 1.0f, 1.0f),
	glm::vec3(0.0f, 0.0f, 1.0f),
	glm::vec3(1.0f, 0.0f, 1.0f),

	glm::vec3(1.0f, 1.0f, 0.0f), // Right Face Reversed 
	glm::vec3(1.0f, 1.0f, 1.0f),
	glm::vec3(1.0f, 0.0f, 1.0f),
	glm::vec3(1.0f, 0.0f, 0.0f),

	glm::vec3(0.0f, 1.0f, 1.0f), // Top Face Reversed
	glm::vec3(1.0f, 1.0f, 1.0f),
	glm::vec3(1.0f, 1.0f, 0.0f),
	glm::vec3(0.0f, 1.0f, 0.0f),
};

constexpr std::array<glm::vec2, 4> faceVertUVs {
    glm::vec2(1.0f, 0.0f),
    glm::vec2(0.0f, 0.0f),
    glm::vec2(0.0f, 1.0f),
    glm::vec2(1.0f, 1.0f),
};

// Every face has the same index pattern
constexpr std::array<Renderer::Index, 6> faceIndices {
	0, 1, 2,
	0, 2, 3,
};
}

namespace blocky {
struct VoxelMesher {
	VoxelMesher() {
		const auto indices = generateIndices();
		indexBuf = Renderer::makeIndexBuffer(indices);
	}

	Renderer::Mesh generate(const VoxelData& voxels) const {
		const auto vertices = generateVertices(voxels);

		Renderer::Mesh mesh;
		mesh.vertBuf = Renderer::makeVertexBuffer(vertices);
		mesh.idxBuf = indexBuf;
		mesh.elmCount = (vertices.size() / 4) * 6;

		return mesh;
	}

private:
	Renderer::Buffer indexBuf;
	// 2 triangles per face and 3 index per triangle so 6 in total
	static constexpr GLsizei elmCount = VoxelData::voxelCount * 36;

	static std::vector<Renderer::Index> generateIndices() {
		std::vector<Renderer::Index> indices;
		indices.reserve(elmCount);

		for (std::size_t i = 0; i < VoxelData::voxelCount * 6; ++i) {
			for (std::size_t j = 0; j < 6; ++j) {
				indices.emplace_back(faceIndices[j] + static_cast<Renderer::Index>(i * 4));
			}
		}

		return indices;
	}

	static std::vector<Renderer::Vertex> generateVertices(const VoxelData& voxels) {
		std::vector<Renderer::Vertex> vertices;

		for (std::uint32_t x = 0; x < VoxelData::size.x-1; ++x) {
		for (std::uint32_t z = 0; z < VoxelData::size.z-1; ++z) {
		for (std::uint32_t y = 0; y < VoxelData::size.y-1; ++y) {
			glm::vec3 offset{x, y, z};

			if(isTransparent(voxels[{x, y ,z}])) {
				if (!isTransparent(voxels[{x+1, y, z}]))
					addFace(vertices, Face::RIGHT_REV, offset);
				if (!isTransparent(voxels[{x, y, z+1}]))
					addFace(vertices, Face::BACK_REV, offset);
				if (!isTransparent(voxels[{x, y+1, z}]))
					addFace(vertices, Face::TOP_REV, offset);
			} else {
				if (isTransparent(voxels[{x+1, y, z}]))
					addFace(vertices, Face::RIGHT, offset);
				if (isTransparent(voxels[{x, y, z+1}]))
					addFace(vertices, Face::BACK, offset);
				if (isTransparent(voxels[{x, y+1, z}]))
					addFace(vertices, Face::TOP, offset);
			}
		}
		}
		}

		return vertices;
	}

	static constexpr bool isTransparent(Block::Type block) {
		return block == Block::Type::AIR;
	}

	static void addFace(std::vector<Renderer::Vertex>& vertVec, Face face, const glm::vec3& offset) {
		for (std::size_t j = 0; j < 4; ++j) {
			vertVec.emplace_back(
				faceVertPos[static_cast<std::size_t>(face)][j] + offset
			, faceVertUVs[j]);
		}
	}

};
}

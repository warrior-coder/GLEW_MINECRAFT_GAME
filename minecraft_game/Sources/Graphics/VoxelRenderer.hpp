#pragma once

#include "Mesh.hpp"
#include "../Voxels/Voxel.hpp"
#include "../Voxels/Chunk.hpp"

#define VERTEX_SIZE (3 + 2 + 1) // 3 Ц вершинные координаты, 2 Ц текстурные координаты, 1 Ц свет

#define VERTEX(INDEX, X, Y, Z, U, V, LIGHT)\
	buffer[INDEX + 0] = (X);\
	buffer[INDEX + 1] = (Y);\
	buffer[INDEX + 2] = (Z);\
	buffer[INDEX + 3] = (U);\
	buffer[INDEX + 4] = (V);\
	buffer[INDEX + 5] = (LIGHT);\
	INDEX += VERTEX_SIZE;

const GLint chunkAttributes[] = {
	   3, 2, 1, NULL
};

class VoxelRenderer
{
	float* buffer;
	size_t capacity;

public:
	VoxelRenderer(size_t capacity);
	~VoxelRenderer();

	Mesh* Render(Chunk* chunk);
};


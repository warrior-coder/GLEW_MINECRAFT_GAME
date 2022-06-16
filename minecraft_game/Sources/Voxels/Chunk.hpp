#pragma once

#include <cmath>
#include "Voxel.hpp"

#define CHUNK_W 16
#define CHUNK_H 16
#define CHUNK_D 16
#define CHUNK_VOLUME (CHUNK_W * CHUNK_H * CHUNK_D)

#define IS_IN(X, Y, Z) ((X) >= 0 && (X) < CHUNK_W && (Y) >= 0 && (Y) < CHUNK_H && (Z) >= 0 && (Z) < CHUNK_D)
#define VOXEL(X, Y, Z) (chunk->voxelsArray[((Y) * CHUNK_D + (Z)) * CHUNK_W + (X)])
#define IS_BLOCKED(X, Y, Z) ((IS_IN(X, Y, Z)) && VOXEL(X, Y, Z).id)

class Chunk
{
public:
	Voxel* voxelsArray;

	Chunk();
	~Chunk();
};


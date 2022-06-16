#include "VoxelRenderer.hpp"


VoxelRenderer::VoxelRenderer(size_t capacity)
	: capacity(capacity)
{
	buffer = new float[VERTEX_SIZE * capacity * 6];
}

VoxelRenderer::~VoxelRenderer()
{
	delete[] buffer;
}

Mesh* VoxelRenderer::Render(Chunk* chunk)
{
	Voxel voxel;
	unsigned int id;
	size_t index = 0;

	float faceLight;
	float u, v, uvSize;

	for (int y = 0; y < CHUNK_H; ++y)
	{
		for (int z = 0; z < CHUNK_D; ++z)
		{
			for (int x = 0; x < CHUNK_W; ++x)
			{
				voxel = chunk->voxelsArray[(y * CHUNK_D + z) * CHUNK_W + x];
				id = voxel.id;

				if (!id)
				{
					continue;
				}

				uvSize = 1.0f / 16.0f;
				u = (id % 16) * uvSize;
				v = 1.0f - (float)(1 + id / 16) * uvSize;

				if (!IS_BLOCKED(x, y + 1, z))
				{
					faceLight = 1.0f;
					VERTEX(index, x - 0.5f, y + 0.5f, z - 0.5f, u + uvSize, v, faceLight);
					VERTEX(index, x - 0.5f, y + 0.5f, z + 0.5f, u + uvSize, v + uvSize, faceLight);
					VERTEX(index, x + 0.5f, y + 0.5f, z + 0.5f, u, v + uvSize, faceLight);
					VERTEX(index, x - 0.5f, y + 0.5f, z - 0.5f, u + uvSize, v, faceLight);
					VERTEX(index, x + 0.5f, y + 0.5f, z + 0.5f, u, v + uvSize, faceLight);
					VERTEX(index, x + 0.5f, y + 0.5f, z - 0.5f, u, v, faceLight);
				}
				if (!IS_BLOCKED(x, y - 1, z))
				{
					faceLight = 0.75f;
					VERTEX(index, x - 0.5f, y - 0.5f, z - 0.5f, u, v, faceLight);
					VERTEX(index, x + 0.5f, y - 0.5f, z + 0.5f, u + uvSize, v + uvSize, faceLight);
					VERTEX(index, x - 0.5f, y - 0.5f, z + 0.5f, u, v + uvSize, faceLight);
					VERTEX(index, x - 0.5f, y - 0.5f, z - 0.5f, u, v, faceLight);
					VERTEX(index, x + 0.5f, y - 0.5f, z - 0.5f, u + uvSize, v, faceLight);
					VERTEX(index, x + 0.5f, y - 0.5f, z + 0.5f, u + uvSize, v + uvSize, faceLight);
				}

				if (!IS_BLOCKED(x + 1, y, z))
				{
					faceLight = 0.95f;
					VERTEX(index, x + 0.5f, y - 0.5f, z - 0.5f, u + uvSize, v, faceLight);
					VERTEX(index, x + 0.5f, y + 0.5f, z - 0.5f, u + uvSize, v + uvSize, faceLight);
					VERTEX(index, x + 0.5f, y + 0.5f, z + 0.5f, u, v + uvSize, faceLight);
					VERTEX(index, x + 0.5f, y - 0.5f, z - 0.5f, u + uvSize, v, faceLight);
					VERTEX(index, x + 0.5f, y + 0.5f, z + 0.5f, u, v + uvSize, faceLight);
					VERTEX(index, x + 0.5f, y - 0.5f, z + 0.5f, u, v, faceLight);
				}
				if (!IS_BLOCKED(x - 1, y, z))
				{
					faceLight = 0.85f;
					VERTEX(index, x - 0.5f, y - 0.5f, z - 0.5f, u, v, faceLight);
					VERTEX(index, x - 0.5f, y + 0.5f, z + 0.5f, u + uvSize, v + uvSize, faceLight);
					VERTEX(index, x - 0.5f, y + 0.5f, z - 0.5f, u, v + uvSize, faceLight);
					VERTEX(index, x - 0.5f, y - 0.5f, z - 0.5f, u, v, faceLight);
					VERTEX(index, x - 0.5f, y - 0.5f, z + 0.5f, u + uvSize, v, faceLight);
					VERTEX(index, x - 0.5f, y + 0.5f, z + 0.5f, u + uvSize, v + uvSize, faceLight);
				}

				if (!IS_BLOCKED(x, y, z + 1))
				{
					faceLight = 0.9f;
					VERTEX(index, x - 0.5f, y - 0.5f, z + 0.5f, u, v, faceLight);
					VERTEX(index, x + 0.5f, y + 0.5f, z + 0.5f, u + uvSize, v + uvSize, faceLight);
					VERTEX(index, x - 0.5f, y + 0.5f, z + 0.5f, u, v + uvSize, faceLight);
					VERTEX(index, x - 0.5f, y - 0.5f, z + 0.5f, u, v, faceLight);
					VERTEX(index, x + 0.5f, y - 0.5f, z + 0.5f, u + uvSize, v, faceLight);
					VERTEX(index, x + 0.5f, y + 0.5f, z + 0.5f, u + uvSize, v + uvSize, faceLight);
				}
				if (!IS_BLOCKED(x, y, z - 1))
				{
					faceLight = 0.8f;
					VERTEX(index, x - 0.5f, y - 0.5f, z - 0.5f, u + uvSize, v, faceLight);
					VERTEX(index, x - 0.5f, y + 0.5f, z - 0.5f, u + uvSize, v + uvSize, faceLight);
					VERTEX(index, x + 0.5f, y + 0.5f, z - 0.5f, u, v + uvSize, faceLight);
					VERTEX(index, x - 0.5f, y - 0.5f, z - 0.5f, u + uvSize, v, faceLight);
					VERTEX(index, x + 0.5f, y + 0.5f, z - 0.5f, u, v + uvSize, faceLight);
					VERTEX(index, x + 0.5f, y - 0.5f, z - 0.5f, u, v, faceLight);
				}

			}
		}
	}

	return new Mesh(buffer, index / VERTEX_SIZE, chunkAttributes);
}

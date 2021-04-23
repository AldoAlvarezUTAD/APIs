#pragma once
#include "Vertex.h"
#include <vector>

class Mesh3D
{
public:
	Mesh3D();
	
	glm::vec3 *color;
	unsigned int& ID;// () const { return id; }
	std::vector<Vertex>& Vertices;
	std::vector<unsigned int>& VerticesIDs;

	void AddVertex(Vertex vertex);
	void AddTriangleIdx(int v1, int v2, int v3);

	std::vector<Vertex>GetVertices();
	std::vector<unsigned int>GetVertexIdxList();

	void FlipTextureUpsideDown();
private:
	unsigned int id;
	std::vector<Vertex>vertices;
	std::vector<unsigned int>verticesIDs;
};


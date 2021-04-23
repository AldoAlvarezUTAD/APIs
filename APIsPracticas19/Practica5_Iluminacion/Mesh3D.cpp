#include "Mesh3D.h"

Mesh3D::Mesh3D() :ID(id), Vertices(vertices), VerticesIDs(verticesIDs)
{
	static int idGenerator = -1;
	id = ++idGenerator;
	color = new glm::vec3(1.0f, 1.0f, 1.0f);
	vertices.clear();
}

void Mesh3D::AddVertex(Vertex vertex)
{
	vertices.push_back(vertex);
}

void Mesh3D::AddTriangleIdx(int v1, int v2, int v3)
{
	if (vertices.size() < 3)return;
	verticesIDs.push_back(v1);
	verticesIDs.push_back(v2);
	verticesIDs.push_back(v3);
}

std::vector<Vertex> Mesh3D::GetVertices()
{
	return vertices;
}

std::vector<unsigned int> Mesh3D::GetVertexIdxList()
{
	return verticesIDs;
}

void Mesh3D::FlipTextureUpsideDown()
{
	for (int i = 0; i < vertices.size(); ++i)
		vertices[i].FlipUpsidedown();
}

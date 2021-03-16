#include "TriangleRot.h"


TriangleRot::TriangleRot(Material *material)
{

	Mesh3D *triangleMesh = new Mesh3D();
	triangleMesh->AddVertex(Vertex{ glm::vec4(0.4f, 0.8f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f) });
	triangleMesh->AddVertex(Vertex{ glm::vec4(-0.4f, 0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f) });
	triangleMesh->AddVertex(Vertex{ glm::vec4(0.4f, 0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f) });
	triangleMesh->AddTriangleIdx(0, 2, 1);

	ResetTransform();
	position.z = -1;
	AddMesh(triangleMesh, material);
}


TriangleRot::~TriangleRot()
{
}

void TriangleRot::Update(float deltaTime)
{
	_rotation.y += 3.2f*deltaTime;
}

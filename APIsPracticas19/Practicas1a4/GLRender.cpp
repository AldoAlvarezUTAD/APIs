#include "GLRender.h"
#include <glm/gtx/transform.hpp>  
#include <glm/gtc/matrix_transform.hpp>
#include "State.h"

GLRender::GLRender()
{
}

GLRender::~GLRender()
{
}

void GLRender::SetupObject(Object3D * obj)
{
	int meshCount = obj->GetMeshCount();

	//invierto las coordenadas Y para que esten correctamente renderizadas
	for (int mesh = 0; mesh < meshCount; ++mesh) {

		glMeshAttributes meshAttributes;
		glGenVertexArrays(1, &meshAttributes.bufferID);
		glGenBuffers(1, &meshAttributes.vertexArrayID);
		glGenBuffers(1, &meshAttributes.indexArrayID);

		glBindVertexArray(meshAttributes.bufferID);


		Mesh3D*objMesh = obj->GetMesh(mesh);
		//objMesh->FlipTextureUpsideDown();

		int vertexSize = objMesh->GetVertices().size();
		int vertexIDsSize = objMesh->GetVertexIdxList().size();

		glBindBuffer(GL_ARRAY_BUFFER, meshAttributes.vertexArrayID);
		glBufferData(GL_ARRAY_BUFFER, vertexSize * sizeof(Vertex), objMesh->GetVertices().data(), GL_STATIC_DRAW);


		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshAttributes.indexArrayID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * vertexIDsSize, objMesh->GetVertexIdxList().data(), GL_STATIC_DRAW);


		MeshIDs[objMesh->ID] = meshAttributes;
	}
}

void GLRender::DrawObject(Object3D * obj)
{
	int meshCount = obj->GetMeshCount();
	for (int mesh = 0; mesh < meshCount; ++mesh)
	{
		glMeshAttributes meshAttribures;
		meshAttribures = MeshIDs[obj->GetMesh(mesh)->ID];

		glBindVertexArray(meshAttribures.bufferID);
		glBindBuffer(GL_ARRAY_BUFFER, meshAttribures.vertexArrayID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshAttribures.indexArrayID);

		State::Model = obj->GetModelMatrix();

		obj->GetMaterial(mesh)->Prepare();

		glDrawElements(GL_TRIANGLES, obj->GetMesh(mesh)->GetVertexIdxList().size(), GL_UNSIGNED_INT, nullptr);
	}
}

void GLRender::DrawWorld(World * world)
{
	world->GetActiveCamera()->Prepare();

	for (int obj = 0; obj < world->GetObjectsSize(); ++obj)
	{
		DrawObject(world->GetObject(obj));
	}
}

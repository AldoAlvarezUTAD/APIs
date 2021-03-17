#include "Render.h"
//includes para transformaciones de matrices
#include <glm/gtx/transform.hpp>  
#include <glm/gtc/matrix_transform.hpp>


//lista de objectIDs y bufferObjects 
//Vertex Buffer Object
std::map<int, boIDS> vboList;

void UploadObject(Object* obj)
{
	boIDS boID;
	for (auto meshIt = obj->meshes->begin();
		meshIt != obj->meshes->end();
		meshIt++) {
		//le aviso a opengl que voy a generar buffers
		//necesito arrays de vertices para un id
		glGenVertexArrays(1, &boID.id);
		glGenBuffers(1, &boID.vbo);
		glGenBuffers(1, &boID.idxbo);

		//necesito activar el main  buffer
		glBindVertexArray(boID.id);

		(*meshIt)->FlipUpsidedown();

		//activar operaciones sobre un buffer previamente creado, activo el buffer
		//osea que mi siguiente operacion se va a realizar sobre ese buffer
		glBindBuffer(GL_ARRAY_BUFFER, boID.vbo);
		//voy a subir datos de vertices
		//3 vertices, 4 coordenadas
		glBufferData(GL_ARRAY_BUFFER,
			sizeof(Vertex) * (*meshIt)->vertexList->size(),
			(*meshIt)->vertexList->data(),
			GL_STATIC_DRAW);


		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, boID.idxbo);
		//1 triangulo, 3 vertices
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,
			sizeof(int) * (*meshIt)->vertexIdx->size(),
			(*meshIt)->vertexIdx->data(),
			GL_STATIC_DRAW);


		//vboList[obj->objID] = boID;
		vboList[(*meshIt)->meshID] = boID;
	}
}
void DeleteObject(Object* obj)
{
	boIDS boID;
	boID = vboList[obj->objID];
	glDeleteBuffers(1, &boID.vbo);
	glDeleteBuffers(1, &boID.idxbo);
	glDeleteVertexArrays(1, &boID.id);
}

void DrawObject(Object* obj, camera* cam, light * l)
{
	boIDS boID;
	auto meshIt = obj->meshes->begin();
	auto matIt = obj->materials->begin();
	for (;
		meshIt != obj->meshes->end();
		meshIt++, matIt++) {

		boID = vboList[(*meshIt)->meshID];

		glBindVertexArray(boID.id);
		glBindBuffer(GL_ARRAY_BUFFER, boID.vbo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, boID.idxbo);

		unsigned int shader = (*matIt)->shaderID;
		glUseProgram(shader);

		//obtengo el identificador del MVP
		///shader-> identificador del shader para gpu
		/// nombre de la variable a buscar sobre el shader
		int uniformMVP = glGetUniformLocation(shader, "MVP");
		int texSampler = glGetUniformLocation(shader, "texSampler");

		int textureCoords = glGetAttribLocation(shader, "vtex");
		int vertexArray = glGetAttribLocation(shader, "vpos");
		int normalArray = glGetAttribLocation(shader, "vnorm");


		glEnableVertexAttribArray(vertexArray);
		glVertexAttribPointer(vertexArray, 4,
			GL_FLOAT, GL_FALSE,
			sizeof(Vertex), nullptr);

		glEnableVertexAttribArray(textureCoords);
		glVertexAttribPointer(textureCoords, 2,
			GL_FLOAT, GL_FALSE,
			sizeof(Vertex),
			(void*)sizeof(glm::vec4));

		glEnableVertexAttribArray(normalArray);
		glVertexAttribPointer(normalArray, 3,
			GL_FLOAT, GL_FALSE,
			sizeof(Vertex),
			(void*)(sizeof(glm::vec4) + sizeof(glm::vec2)));

		//activa la unidad de textura a usar
		glActiveTexture(GL_TEXTURE0);
		//activo la textura almacenada para enlazarla con texture0
		glBindTexture(GL_TEXTURE_2D, (*matIt)->texture->textID);
		//meto en texSampler la unidad de textura empleada
		glUniform1i(texSampler, 0);

		//empiezo a crear la matriz MVP creando una matriz identidad 4x4
		glm::mat4 Identity = glm::mat4(1.0f);
		//multiplico la matriz por la posicion 
		glm::mat4 Model = glm::translate(Identity, obj->pos);

		//aplico las rotaciones
		Model = glm::rotate(Model, obj->rot.y, glm::vec3(0.0f, 1.0f, 0.0f));
		Model = glm::scale(Model, obj->scal);


		glm::mat4 View = ComputeViewMatrix(cam);// Identity;
		glm::mat4 Proj = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);

		glm::mat4 MVP = Proj * View * Model;


		//asigno la matriz mvp al shader
		//	solo subo 1 matriz, por eso 1
		//	no esta transpuesta la matriz
		//	le paso el apuntador al primer valor de la matriz
		glUniformMatrix4fv(uniformMVP, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, &Model[0][0]);


		//le paso al shader los valores que espera recibir como globales
		glUniform1f(glGetUniformLocation(shader, "lightAmb"), 1.0f);
		glUniform1i(glGetUniformLocation(shader, "lightType"), l->type);
		glUniform3fv(glGetUniformLocation(shader, "lightPos"),1, &l->pos[0]);
		glUniform3fv(glGetUniformLocation(shader, "lightDir"),1, &l->dir[0]);
		glUniform3fv(glGetUniformLocation(shader, "eyePos"),1, &cam->position[0]);
		glUniform3fv(glGetUniformLocation(shader, "lookAt"),3, &cam->lookAt[0]);
		glUniform1i(glGetUniformLocation(shader, "matShininess"), (*matIt)->shininess);


		glDrawElements(GL_TRIANGLES, (*meshIt)->vertexIdx->size(), GL_UNSIGNED_INT, nullptr);
	}
}
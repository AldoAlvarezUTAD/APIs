#include "Cube.h"



Cube::Cube(Material*top, Material*side)
{
	Mesh3D * sideMesh = new Mesh3D();
	Mesh3D * topMesh = new Mesh3D();
	glm::vec4 bfr = glm::vec4(0.5f, -0.5f, 0.5f, 1.0f);		//bottom front right
	glm::vec4 bfl = glm::vec4(-0.5f, -0.5f, 0.5f, 1.0f);	//bottom front left
	glm::vec4 bbr = glm::vec4(0.5f, -0.5f, -0.5f, 1.0f);	//bottom back right
	glm::vec4 bbl = glm::vec4(-0.5f, -0.5f, -0.5f, 1.0f);	//bottom back left
	glm::vec4 tfr = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);		//top front right
	glm::vec4 tfl = glm::vec4(-0.5f, 0.5f, 0.5f, 1.0f);		//top front left
	glm::vec4 tbr = glm::vec4(0.5f, 0.5f, -0.5f, 1.0f);		//top back right
	glm::vec4 tbl = glm::vec4(-0.5f, 0.5f, -0.5f, 1.0f);	//top back left

	glm::vec2 bl = glm::vec2(0.0f, 0.0f); //bottom left
	glm::vec2 tl = glm::vec2(0.0f, 1.0f); //top left
	glm::vec2 br = glm::vec2(1.0f, 0.0f); //bottom right
	glm::vec2 tr = glm::vec2(1.0f, 1.0f); //top right

	/*
		para que cada cara este correctamente dibujada, necesito repetir vertices con diferente coordenada de textura,
		así como voltear las coordenadas para que se dibujen correctamente
		entonces... cada 2 puntos cambio un vertice si es par, cada 1 cambio la coordenada de textura

		CARA FRONTAL
		8,9		10,11
		0,1		2,3

		CARA TRASERA
		12,13	14,15
		4,5		6,7
	*/
	Vertex sideVertices[16]
	{
		Vertex{ bfl, bl }, // 0
		Vertex{ bfl, br }, // 1
		Vertex{ bfr, bl }, // 2
		Vertex{ bfr, br }, // 3
		Vertex{ bbl, bl }, // 4
		Vertex{ bbl, br }, // 5
		Vertex{ bbr, bl }, // 6
		Vertex{ bbr, br }, // 7

		Vertex{ tfl, tl }, // 8
		Vertex{ tfl, tr }, // 9
		Vertex{ tfr, tl }, // 10
		Vertex{ tfr, tr }, // 11
		Vertex{ tbl, tl }, // 12
		Vertex{ tbl, tr }, // 13
		Vertex{ tbr, tl }, // 14
		Vertex{ tbr, tr }  // 15
	};
	Vertex TopBottomVertices[8]
	{
		Vertex{ bfl, tl },
		Vertex{ bfr, tr },
		Vertex{ bbl, bl },
		Vertex{ bbr, br },

		Vertex{ tfl, tl },
		Vertex{ tfr, tr },
		Vertex{ tbl, bl },
		Vertex{ tbr, br } 
	};

	for (int vertex = 0; vertex < 16; ++vertex) 
		sideMesh->AddVertex(sideVertices[vertex]);
	for (int vertex = 0; vertex < 8; ++vertex) 
		topMesh->AddVertex(TopBottomVertices[vertex]);


	sideMesh->AddTriangleIdx(12, 15, 4);	// cara trasera
	sideMesh->AddTriangleIdx(4, 15, 7);
	sideMesh->AddTriangleIdx(2, 10, 9);		// cara delantera
	sideMesh->AddTriangleIdx(2, 9, 1);
	sideMesh->AddTriangleIdx(6, 14, 11);	// cara izquierda
	sideMesh->AddTriangleIdx(6, 11, 3);
	sideMesh->AddTriangleIdx(0, 8, 13);		// cara derecha
	sideMesh->AddTriangleIdx(0, 13, 5);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	topMesh->AddTriangleIdx(4, 5, 6);	// cara arriba
	topMesh->AddTriangleIdx(5, 7, 6);
	topMesh->AddTriangleIdx(0, 1, 2);	// cara abajo
	topMesh->AddTriangleIdx(1, 3, 2);

	ResetTransform();
	AddMesh(topMesh, top);
	AddMesh(sideMesh, side);
}


Cube::~Cube()
{
}

void Cube::Update(float deltaTime)
{
	rotation.y += 1.0f*deltaTime;
	rotation.x += 0.6f*deltaTime;
}

/*
	glm::vec4 v1 = glm::vec4(0.4f, 0.8f, 0.0f, 1.0f);
	glm::vec4 v2 = glm::vec4(-0.4f, 0.0f, 0.0f, 1.0f);
	glm::vec4 v3 = glm::vec4(0.4f, 0.0f, 0.0f, 1.0f);

	glm::vec2 t1 = glm::vec2(1.0f, 1.0f);
	glm::vec2 t2 = glm::vec2(0.0f, 0.0f);
	glm::vec2 t3 = glm::vec2(1.0f, 0.0f);
	sideMesh->AddVertex(Vertex{ v1, t1 });
	sideMesh->AddVertex(Vertex{ v2, t2 });
	sideMesh->AddVertex(Vertex{ v3, t3 });
	sideMesh->AddTriangleIdx(0, 2, 1);
*/
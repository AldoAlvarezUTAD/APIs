#include "Vertex.h"

void Vertex::FlipUpsidedown()
{
	//texCoord.x = 1 - texCoord.x;
	texCoord.y = 1 - texCoord.y;
}

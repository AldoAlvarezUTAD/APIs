#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture * CreateTexture(const char * fileName)
{
	Texture *tex = new Texture;
	//obtengo la informacion del archivo en formato RGBA
	//cargo los datos de la textura
	unsigned char * data = stbi_load(fileName, &tex->width, &tex->height, NULL, STBI_rgb_alpha);

	//subo los datos a opengl
	//genero los identificadores de la textura
	glGenTextures(1, &tex->textID);
	//activo la textura
	glBindTexture(GL_TEXTURE_2D, tex->textID);

	//que filtro aplico cuando se achica la textura
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//que filtro aplico cuando se escala la textura, mas grande
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//me repite la textura por los ejes XY (st)
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//cargamos la imagen, un mipmap 0, lod 0
	//mipmap -> resolucion de textura en gpu
	//formato para la gpu, y formato de la imagen desde cpu
	glTexImage2D(
		GL_TEXTURE_2D, 0, GL_RGBA, 
		tex->width, tex->height, 
		0,  GL_RGBA, GL_UNSIGNED_BYTE, 
		data);
	glGenerateMipmap(GL_TEXTURE_2D);

	//libero los datos
	stbi_image_free(data);

	return tex;
}

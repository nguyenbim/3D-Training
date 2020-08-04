#include <stdafx.h>
#include"Texture.h"
using namespace std;
Texture::Texture() {};
Texture::~Texture() {};
void Texture::LoadTexture(string strFilePath){
	const char* cstr = strFilePath.c_str();
	int iWidth;
	int iHeight;
	int ibpp;	
	TexId = new GLuint;
	glGenTextures(1, TexId);
	glBindTexture(GL_TEXTURE_2D, *TexId);
	char *imageData = LoadTGA(cstr, &iWidth, &iHeight, &ibpp);
	if (ibpp == 24) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, iWidth, iHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
	}
	else glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, iWidth, iHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_NEAREST_MIPMAP_NEAREST);
	glGenerateMipmap(GL_TEXTURE_2D);	
}

GLuint* Texture::GetTexId() {
	return TexId;
}



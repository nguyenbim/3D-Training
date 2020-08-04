#pragma once
#include<iostream>
#include "../Utilities/utilities.h"
#include"Vertex.h"
#include "Shaders.h"
class Texture {
private:
	int m_TextureID;
	GLuint* TexId;
	
public:
	Texture();
	~Texture();
	void LoadTexture(std::string strFilePath);
	GLuint* GetTexId();
};
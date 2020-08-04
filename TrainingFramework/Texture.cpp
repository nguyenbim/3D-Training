#include "stdafx.h"
#include "Texture.h"



Texture::Texture() {
}

Texture::~Texture() {
}

int* Texture::GetID() {
	return &m_ID;
}

string* Texture::GetTextureName() {
	return &m_strTextureName;
}

string* Texture::GetTiling() {
	return &m_strTiling;
}

GLuint* Texture::GetTextureID() {
	return &m_TextureID;
}
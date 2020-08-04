#pragma once

#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include<iostream>
using namespace std;
class Texture {
private:
	int m_ID = 0;
	string m_strTextureName;
	string m_strTiling;

	GLuint m_TextureID = 0;
public:
	Texture();
	~Texture();

	int* GetID();
	string* GetTextureName();
	string* GetTiling();

	GLuint* GetTextureID();
};
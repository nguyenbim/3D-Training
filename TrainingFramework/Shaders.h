#pragma once
#include "../Utilities/utilities.h"

class Shaders 
{
public:
	GLuint program, vertexShader, fragmentShader, textureId;
	char fileVS[260];
	char fileFS[260];
	GLint positionAttribute;
	GLint uvAttribute;
	int unifromLocation;
	int WVPLoc;
	int Init(char * fileVertexShader, char * fileFragmentShader);
	~Shaders();
};
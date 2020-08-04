#include <stdafx.h>
#include "Shaders.h"

Shaders::Shaders() {};
int Shaders::Init(string strVSFile, string strFSFile)
{
	char* strBuffer = new char[250];

	std::strcpy(strBuffer, strVSFile.c_str());

	vertexShader = esLoadShader(GL_VERTEX_SHADER, strBuffer);

	if (vertexShader == 0)
		return -1;

	std::strcpy(strBuffer, strFSFile.c_str());

	fragmentShader = esLoadShader(GL_FRAGMENT_SHADER, strBuffer);

	if (fragmentShader == 0)
	{
		glDeleteShader(vertexShader);
		return -2;
	}

	program = esLoadProgram(vertexShader, fragmentShader);

	//finding location of uniforms / attributes
	positionAttribute = glGetAttribLocation(program, "a_posL");
	uvAttribute = glGetAttribLocation(program,"a_uv");
	//glBindTexture(GL_TEXTURE_2D, textureId);
	uniformLocation = glGetUniformLocation(program,"u_texture");
	glUniform1i(uniformLocation, 0);
	WVPLoc = glGetUniformLocation(program, "u_mvpMatrix");
	return 0;
}

Shaders::~Shaders()
{
	glDeleteProgram(program);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}
std::string Shaders::GetVSFileStr() {
	return m_strVSFile;
}

std::string Shaders::GetFSFileStr() {
	return m_strFSFile;
}

int* Shaders::GetID() {
	return &m_ID;
}
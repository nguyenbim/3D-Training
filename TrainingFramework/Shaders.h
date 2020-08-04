#pragma once
#include "stdafx.h"
#include "../Utilities/utilities.h"
#include<iostream>

using namespace std;
class Shaders 
{
private:
	int m_ID = 0;
	string m_strVSFile, m_strFSFile;
public:
	Shaders();
	~Shaders();

	GLuint program = 0, vertexShader = 0, fragmentShader = 0;
	GLint positionAttribute = 0;
	GLint uvAttribute = 0;
	GLint uniformLocation = 0;
	GLint WVPLoc = 0;

	int Init(std::string strVSFile, std::string strFSFile);

	int* GetID();
	string GetVSFileStr();
	string GetFSFileStr();
};
#pragma once
#include<iostream>
#include "../Utilities/utilities.h"
#include"Vertex.h"
#include "Shaders.h"

using namespace std;
class Model {
private:
	int m_ModelId;
	int NIndices;
	int NVertices;
	Vertex* Vertices;
	GLuint *Indices;
	GLuint* VBOId;
	GLuint* IBOId;

public:
	
	Model();
	~Model();
	int GetModelID();
	void SetModelID();
	void LoadModel(string strFilePath);
	int GetNVertice();
	Vertex* GetVertices();
	GLuint* GetIndices();
	int GetNIndices();
	GLuint* GetVBOId();
	GLuint* GetIBOId();

};
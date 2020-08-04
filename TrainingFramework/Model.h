#pragma once
#include<iostream>
#include "../Utilities/utilities.h"
#include"Vertex.h"
#include "Shaders.h"
#include<vector>

using namespace std;
class Model {
private:
	int m_ID = 0;
	string m_strModelName;

	vector<Vertex> m_vVerticesData;
	vector<GLuint> m_vIndicesData;
	int m_NIndices=0;
	int m_NVertice=0;
	GLuint m_VBOId=0;
	GLuint m_IBOId=0;

public:
	Model();
	~Model();
	
	int* GetID();
	string* GetModelName();

	vector<Vertex>* GetVerticesData();
	vector<GLuint>* GetIndicesData();

	GLuint* GetVBOId();
	GLuint* GetIBOId();

	int* GetNVertice();
	int* GetNIndices();

};
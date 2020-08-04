#include <stdafx.h>
#include"Model.h"
Model::Model() {};
Model::~Model() {};
int* Model::GetID() {
	return &m_ID;
}
string* Model::GetModelName() {
	return &m_strModelName;
}
vector<Vertex>* Model::GetVerticesData() {
	return &m_vVerticesData;
}
vector<GLuint>* Model::GetIndicesData() {
	return &m_vIndicesData;
}
GLuint* Model::GetVBOId() {
	return &m_VBOId;
}
GLuint* Model::GetIBOId() {
	return &m_IBOId;
}
int* Model::GetNVertice() {
	return &m_NVertice;
}

int* Model::GetNIndices() {
	return &m_NIndices;
}
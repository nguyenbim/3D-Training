#include <stdafx.h>
#include"Model.h"
Model::Model() {};
Model::~Model() {};
void Model::LoadModel(string strFilePath){
	const char* cstr = strFilePath.c_str();
	FILE* fp;
	fp = fopen(cstr, "r");

	//triangle data (heap)


	fscanf(fp, "NrVertices: %d\n", &NVertices);
	printf("%d\n", NVertices);
	Vertices = new Vertex[NVertices];
	for (int i = 0; i < NVertices; i++) {
		int VId = 0;
		fscanf(fp, "   %d. pos:[%f, %f, %f]; norm:[%f, %f, %f]; binorm:[%f, %f, %f]; tgt:[%f, %f, %f]; uv:[%f, %f];\n", &VId, &Vertices[i].pos.x, &Vertices[i].pos.y, &Vertices[i].pos.z, &Vertices[i].normal.x, &Vertices[i].normal.y, &Vertices[i].normal.z, &Vertices[i].binormal.x, &Vertices[i].binormal.y, &Vertices[i].binormal.z, &Vertices[i].tangent.x, &Vertices[i].tangent.y, &Vertices[i].tangent.z, &Vertices[i].uv.x, &Vertices[i].uv.y);
	}

	fscanf(fp, "NrIndices: %d\n", &NIndices);
	Indices = new GLuint[NIndices];
	for (int i = 0; i < NIndices; i += 3) {
		int Id = 0;

		fscanf(fp, "   %d.   %d,    %d,    %d\n", &Id, &Indices[i], &Indices[i + 1], &Indices[i + 2]);

	}
	VBOId = new GLuint;

	glGenBuffers(1, VBOId);
	glBindBuffer(GL_ARRAY_BUFFER, *VBOId);
	glBufferData(GL_ARRAY_BUFFER, NVertices * sizeof(Vertex), Vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	IBOId = new GLuint;
	glGenBuffers(1, IBOId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *IBOId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, NIndices * sizeof(GLuint), Indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}
void Model::SetModelID() {};
int Model::GetModelID() {
	return m_ModelId;
};
int Model::GetNVertice() {
	return NVertices;
}
Vertex* Model::GetVertices(){
	return Vertices;
}
GLuint* Model::GetIndices() {
	return Indices;
}
int Model::GetNIndices() {
	return NIndices;
}
GLuint* Model::GetVBOId() {
	return VBOId;
}
GLuint* Model::GetIBOId() {
	return IBOId;
}
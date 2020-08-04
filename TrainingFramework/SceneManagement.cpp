#include "stdafx.h"
#include "SceneManagement.h"

SceneManagement::SceneManagement() {
}

SceneManagement::~SceneManagement() {
}

void SceneManagement::InitWithFile(std::string strFilePath) {
	FILE* FileStream;
	FileStream = fopen(strFilePath.c_str(), "r");

	// Loading objects;
	fscanf(FileStream, " #Objects: %d\n", &m_ObjectCount);
	printf("%d\n", m_ObjectCount);
	for (int i = 0; i < m_ObjectCount; i++) {
		Object NewObject;

		fscanf(FileStream, " ID %d\n", NewObject.GetID());

		// Loading Model for Object
		int ModelID = -1;
		fscanf(FileStream, " MODEL %d\n", &ModelID);

		// Loading 2D Textures
		int TexturesCount = -1;
		fscanf(FileStream, " TEXTURES %d\n", &TexturesCount);

		for (int f = 0; f < TexturesCount; f++) {
			int TexturesID;
			fscanf(FileStream, " TEXTURE %d\n", &TexturesID);

			NewObject.GetTextureID()->push_back(TexturesID);
		}

		// Loading Cube Textures
		int CubeTexturesCount = -1;
		fscanf(FileStream, " CUBETEXTURES %d\n", &CubeTexturesCount);

		for (int f = 0; f < CubeTexturesCount; i++) {
			int CubeTexturesID;
			fscanf(FileStream, " CUBETEX %d\n", &CubeTexturesID);

			*NewObject.GetCubeTextureID() = CubeTexturesID; // Not handling more than one CubeTex
			break;
		}

		// Loading Shaders;
		fscanf(FileStream, " SHADER %d\n", NewObject.GetShaderID());

		// Loading Object WorldLocation;
		Vector3 vPosition, vRotation, vScale;
		fscanf(FileStream, " POSITION %f, %f, %f \n", &vPosition.x, &vPosition.y, &vPosition.z);
		fscanf(FileStream, " ROTATION %f, %f, %f \n", &vRotation.x, &vRotation.y, &vRotation.z);
		fscanf(FileStream, " SCALE %f, %f, %f \n", &vScale.x, &vScale.y, &vScale.z);

		*NewObject.GetLocation() = vPosition;
		*NewObject.GetRotation() = vRotation;
		*NewObject.GetScale() = vScale;

		m_vObjects.push_back(NewObject);
	}

	// Loading Camera
	float FOV = 0.0f, AspectRatio = 4.0f / 3.0f, Near = 0.0f, Far = 0.0f, Speed = 0.0f;
	fscanf(FileStream, "#CAMERA\n");
	fscanf(FileStream, "NEAR %f\n", &Near);
	fscanf(FileStream, "FAR %f\n", &Far);
	fscanf(FileStream, "FOV %f\n", &FOV);
	fscanf(FileStream, "SPEED %f\n", &Speed);

	Camera::GetInstance()->SetCamera(FOV, AspectRatio, Near, Far, Speed);
	printf("%f", FOV);
}

void SceneManagement::Update(float DeltaTime) {
	for (int i = 0; i < m_ObjectCount; i++) {
		m_vObjects[i].Update();
	}
}

void SceneManagement::Draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	for (int i = 0; i < m_ObjectCount; i++) {
		// Loading Shader
		int iShaderID = *m_vObjects.at(i).GetShaderID();
		Shaders MyShader = ResourceManagement::GetInstance()->GetShader(iShaderID);
		glUseProgram(MyShader.program);

		//	Loading Model and Textures
		int ObjectModelID = *m_vObjects.at(i).GetModelID();
		int ObjectTextureID = m_vObjects.at(i).GetTextureID()->at(0);

		Model ObjectModel = ResourceManagement::GetInstance()->GetModel(ObjectModelID);
		Texture ObjectTexture = ResourceManagement::GetInstance()->GetTexture(ObjectTextureID);

		GLuint VBOId = *ObjectModel.GetVBOId();
		GLuint IBOId = *ObjectModel.GetIBOId();

		GLuint TextureID = *ObjectTexture.GetTextureID();

		int iIndicesCount = *ObjectModel.GetNIndices();

		// Loading Object's WVP
		Matrix WorldMatrix = m_vObjects.at(i).GetWorldMatrix();
		Matrix ViewMatrix = Camera::GetInstance()->GetViewMatrix();
		Matrix ProjectionMatrix = Camera::GetInstance()->GetProjectionMatrix();

		Matrix WVP = WorldMatrix * ViewMatrix * ProjectionMatrix;

		glBindBuffer(GL_ARRAY_BUFFER, VBOId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBOId);
		glBindTexture(GL_TEXTURE_2D, TextureID);

		// Position attribute
		if (MyShader.positionAttribute != -1)
		{
			glEnableVertexAttribArray(MyShader.positionAttribute);
			glVertexAttribPointer(MyShader.positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
		}

		// UV attribute
		if (MyShader.uvAttribute != -1) {
			glEnableVertexAttribArray(MyShader.uvAttribute);
			glVertexAttribPointer(MyShader.uvAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (char*)0 + sizeof(Vector3) + sizeof(Vector3) + sizeof(Vector3) + sizeof(Vector3));
		}

		// Texture Uniform
		if (MyShader.uniformLocation != -1)
		{
			glUniform1i(MyShader.uniformLocation, 0);
		}

		// WVP Uniform
		if (MyShader.WVPLoc != -1) {
			glUniformMatrix4fv(MyShader.WVPLoc, 1, GL_FALSE, &WVP.m[0][0]);
		}

		glDrawElements(GL_TRIANGLES, iIndicesCount, GL_UNSIGNED_INT, 0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindBuffer(GL_TEXTURE_2D, 0);
	}
}
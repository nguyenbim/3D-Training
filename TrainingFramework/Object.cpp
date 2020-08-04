#include <stdafx.h>
#include"Object.h"

Object::Object() {
	m_Test_texture = new Texture();
	m_Test_model = new Model();

	ObjectRotation.x = 0;
	ObjectRotation.y = 0;
	ObjectRotation.z =0;

	ScaleMatrix.SetScale(Vector3(0.5f,0.5f,0.5f));

	Matrix RotationMatrixX, RotationMatrixY, RotationMatrixZ;
	RotationMatrixX.SetRotationAngleAxis(ObjectRotation.x * (3.14 / 180), 1.0f, 0.0f, 0.0f);
	RotationMatrixY.SetRotationAngleAxis(ObjectRotation.y * (3.14 / 180), 0.0f, 1.0f, 0.0f);
	RotationMatrixZ.SetRotationAngleAxis(ObjectRotation.z * (3.14 / 180), 0.0f, 0.0f, 1.0f);
	RotationMatrix = RotationMatrixZ * RotationMatrixX * RotationMatrixY;
	TranslationMatrix.SetTranslation(0.0f, -0.5f, 0.0f);	
};
Object::~Object() {};


void Object::LoadModel(string strFilePath) {
	m_Test_model->LoadModel(strFilePath);
}
void Object::LoadTexture(string strFilePath) {
	m_Test_texture->LoadTexture(strFilePath);
}

Model* Object::GetModel() {
	return m_Test_model;
}

GLuint* Object::GetVBO() {
	return m_Test_model->GetVBOId();
}

GLuint* Object::GetIBO() {
	return m_Test_model->GetIBOId();
}

GLuint* Object::GetTexture() {
	return m_Test_texture->GetTexId();
}
Matrix Object::GetWVP() {
	WorldMatrix.SetIdentity();
	ViewMatrix = Camera::GetInstance()->GetViewMatrix();
	ProjectionMatrix = Camera::GetInstance()->GetProjectionMatrix();
	WorldMatrix =ScaleMatrix * RotationMatrix * TranslationMatrix;
	return WorldMatrix * ViewMatrix * ProjectionMatrix;
}
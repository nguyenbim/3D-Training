#pragma once
#include<iostream>
#include"Texture.h"
#include"Model.h"
#include"Camera.h"
#include"Singleton.h"
using namespace std;
class Object {
private:
	Texture* m_Test_texture;
	Model* m_Test_model;
	Matrix WorldMatrix, ViewMatrix, ProjectionMatrix;
	Matrix ScaleMatrix, RotationMatrix, TranslationMatrix;

	Vector3 WorldLocation;
	Vector3 ObjectRotation; // Angles in degrees
	Vector3 ObjectScale;

public:
	Object();
	~Object();
	void LoadModel(string strFilePath);
	void LoadTexture(string strFilePath);
	Model* GetModel();
	GLuint* GetVBO();
	GLuint* GetIBO();
	GLuint* GetTexture();
	Matrix GetWVP();
};

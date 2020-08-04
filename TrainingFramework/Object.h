#pragma once
#include"stdafx.h"
#include<vector>
#include "../Utilities/utilities.h" 
#include<iostream>
#include"Texture.h"
#include"Model.h"
#include"Camera.h"
#include"Singleton.h"
using namespace std;
class Object {
private:
	int m_ID = 0;
	bool m_IsAttributeChanged = false;

	int m_ModelID = 0;
	vector<int> m_vTextureID;
	int m_CubeTextureID = 0;
	int m_ShaderID = 0;
	Texture* m_Test_texture;
	Model* m_Test_model;
	Matrix m_WorldMatrix, m_ViewMatrix, m_ProjectionMatrix;
	Matrix m_ScaleMatrix, m_RotationMatrix, m_TranslationMatrix;

	Vector3 m_WorldLocation = Vector3(0.0f, 0.0f, 0.0f);
	Vector3 m_ObjectRotation = Vector3(0.0f, 0.0f, 0.0f); // Angles in degrees
	Vector3 m_ObjectScale = Vector3(1.0f, 1.0f, 1.0f);

public:
	Object();
	Object(const Object& oCopy);
	~Object();

	void FlagChanges();
	void Update();

	int* GetID();
	int* GetModelID();
	std::vector<int>* GetTextureID();
	int* GetCubeTextureID();
	int* GetShaderID();

	Vector3* GetLocation();
	Vector3* GetRotation();
	Vector3* GetScale();

	Matrix GetWorldMatrix();
};

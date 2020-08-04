#include"stdafx.h"
#include "../Utilities/utilities.h"
#include<iostream>
#include"Singleton.h"

#pragma once
class Camera{
private:
	static Camera* s_Instance;

	//Attributes for Projection Matrix
	float FOV = float(45*3.14/180);
	float AspectRatio = 4.0f / 3.0f;
	float NearPlane = 0.1f;
	float FarPlane = 100.0f;

	//Attributes for camera speed
	float m_Speed = 10.0f;
	float m_RotateSpeed = 1.0f;

	Vector3 m_Position = Vector3(0.0f, 0.0f, 2.0f);;
	Vector3 m_Target = Vector3(0.0f, 0.0f, 0.0f);
	Vector3 m_Up = Vector3(0.0f, 1.0f, 0.0f);

	Matrix m_ViewMatrix ;
	Matrix m_ProjectionMatrix;
	Matrix m_WorldMatrix;
	Matrix m_RotationMatrix;
	Matrix m_TranslationMatrix;

public:
	Camera();
	~Camera();
	void MoveForward(float deltaTime);
	void MoveBack(float deltaTime);
	void MoveLeft(float deltaTime);
	void MoveRight(float deltaTime);

	Matrix SetRotationAroundY(float angle);
	Matrix SetRotationAroundX(float angle);

	void RotateLeft(float deltaTime);
	void RotateRight(float deltaTime);
	void RotateUp(float deltaTime);
	void RotateDown(float deltaTime);

	Matrix GetViewMatrix();
	Matrix GetWorldMatrix();
	Matrix GetProjectionMatrix();
	Matrix GetTranslationMatrix();
	Matrix GetRotationMatrix();
	//void SetViewMatrix();

	static Camera* GetInstance();

};

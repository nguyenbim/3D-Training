#include"stdafx.h"
#include "../Utilities/utilities.h"
#include"Camera.h"


using namespace std;


Camera::Camera() {};
void Camera::SetCamera(float Fov, float AspectRatio, float Near, float Far, float Speed) {
	m_FOV = float(Fov*3.14/180);
	m_AspectRatio = AspectRatio;
	m_NearPlane = Near;
	m_FarPlane = Far;
	m_Speed = Speed;
}
Camera::~Camera() {};


Matrix Camera::GetTranslationMatrix() {
	return m_TranslationMatrix.SetTranslation(m_Position.x, m_Position.y, m_Position.z);
}
Matrix Camera::GetRotationMatrix() {
	Vector3 zaxis = (m_Position - m_Target).Normalize();
	Vector3 xaxis = (m_Up.Cross(zaxis)).Normalize();
	Vector3 yaxis = (zaxis.Cross(xaxis)).Normalize();
	m_RotationMatrix.m[0][0] = xaxis.x; m_RotationMatrix.m[0][1] = xaxis.y; m_RotationMatrix.m[0][2] = xaxis.z; m_RotationMatrix.m[0][3] = 0;
	m_RotationMatrix.m[1][0] = yaxis.x; m_RotationMatrix.m[1][1] = yaxis.y; m_RotationMatrix.m[1][2] = yaxis.z; m_RotationMatrix.m[1][3] = 0;
	m_RotationMatrix.m[2][0] = zaxis.x; m_RotationMatrix.m[2][1] = zaxis.y; m_RotationMatrix.m[2][2] = zaxis.z; m_RotationMatrix.m[2][3] = 0;
	m_RotationMatrix.m[3][0] = 0; m_RotationMatrix.m[3][1] = 0; m_RotationMatrix.m[3][2] = 0; m_RotationMatrix.m[3][3] = 1;
	return m_RotationMatrix;
}
Matrix Camera::GetViewMatrix() {
	Vector3 zaxis = (m_Position - m_Target).Normalize();
	Vector3 xaxis = (m_Up.Cross(zaxis)).Normalize();
	Vector3 yaxis = (zaxis.Cross(xaxis)).Normalize();
	m_ViewMatrix.m[0][0] = xaxis.x; m_ViewMatrix.m[0][1] = yaxis.x; m_ViewMatrix.m[0][2] = zaxis.x; m_ViewMatrix.m[0][3] = 0;
	m_ViewMatrix.m[1][0] = xaxis.y; m_ViewMatrix.m[1][1] = yaxis.y; m_ViewMatrix.m[1][2] = zaxis.y; m_ViewMatrix.m[1][3] = 0;
	m_ViewMatrix.m[2][0] = xaxis.z; m_ViewMatrix.m[2][1] = yaxis.z; m_ViewMatrix.m[2][2] = zaxis.z; m_ViewMatrix.m[2][3] = 0;
	m_ViewMatrix.m[3][0] = -m_Position.Dot(xaxis); m_ViewMatrix.m[3][1] = -m_Position.Dot(yaxis); m_ViewMatrix.m[3][2] = -m_Position.Dot(zaxis); m_ViewMatrix.m[3][3] = 1;
	return m_ViewMatrix;
}
Matrix Camera::GetWorldMatrix() {
	return GetRotationMatrix()*GetTranslationMatrix();
}
Matrix Camera::GetProjectionMatrix() {
	return m_ProjectionMatrix.SetPerspective(m_FOV, m_AspectRatio, m_NearPlane, m_FarPlane);
}


void Camera::MoveForward(float deltaTime) {
	Vector3 deltaMove = -(m_Position - m_Target).Normalize() * deltaTime * m_Speed;
	m_Position += deltaMove;
	m_Target += deltaMove;
};
void Camera::MoveBack(float deltaTime) {
	Vector3 deltaMove = (m_Position - m_Target).Normalize() * deltaTime * m_Speed;
	m_Position += deltaMove;
	m_Target += deltaMove;
};
void Camera::MoveRight(float deltaTime) {
	Vector3 zaxis = (m_Position - m_Target).Normalize();
	Vector3 xaxis = (m_Up.Cross(zaxis)).Normalize();
	Vector3 deltaMove = -xaxis.Normalize() * deltaTime * m_Speed;
	m_Position += deltaMove;
	m_Target += deltaMove;
};
void Camera::MoveLeft(float deltaTime) {
	Vector3 zaxis = (m_Position - m_Target).Normalize();
	Vector3 xaxis = (m_Up.Cross(zaxis)).Normalize();
	Vector3 deltaMove = xaxis.Normalize() * deltaTime * m_Speed;
	m_Position += deltaMove;
	m_Target += deltaMove;
};

Matrix Camera::SetRotationAroundY(float angle) {
	Matrix rotation;
	Vector4 rotateAxis = Vector4(0, 1, 0, 0);
	rotateAxis = rotateAxis * GetViewMatrix();
	return rotation.SetRotationAngleAxis(angle, rotateAxis.x, rotateAxis.y, rotateAxis.z);
}

void Camera::RotateLeft(float deltaTime) {
	float rotateAngle = deltaTime * m_RotateSpeed;
	Vector4 localTarget = Vector4(0.0f, 0.0f, -(m_Position - m_Target).Length(), 1);
	Vector4 localNewTarget = localTarget * SetRotationAroundY(-rotateAngle);
	Vector4 worldNewTarget = localNewTarget * GetWorldMatrix();
	m_Target.x = worldNewTarget.x;
	m_Target.y = worldNewTarget.y;
	m_Target.z = worldNewTarget.z;
};
void Camera::RotateRight(float deltaTime) {
	float rotateAngle = deltaTime * m_RotateSpeed;
	Vector4 localTarget = Vector4(0.0f, 0.0f, -(m_Position - m_Target).Length(), 1);
	Vector4 localNewTarget = localTarget * SetRotationAroundY(rotateAngle);
	Vector4 worldNewTarget = localNewTarget * GetWorldMatrix();
	m_Target.x = worldNewTarget.x;
	m_Target.y = worldNewTarget.y;
	m_Target.z = worldNewTarget.z;
};
Matrix Camera::SetRotationAroundX(float angle) {
	Matrix rotation;
	Vector4 rotateAxis = Vector4(1, 0, 0, 0);
	rotateAxis = rotateAxis * GetViewMatrix();
	return rotation.SetRotationAngleAxis(angle, rotateAxis.x, rotateAxis.y, rotateAxis.z);
}
void Camera::RotateUp(float deltaTime) {
	float rotateAngle = deltaTime * m_RotateSpeed;
	Vector4 localTarget = Vector4(0.0f, 0.0f, -(m_Position - m_Target).Length(), 1);
	Vector4 localNewTarget = localTarget *  SetRotationAroundX(-rotateAngle);
	Vector4 worldNewTarget = localNewTarget * GetWorldMatrix();
	m_Target.x = worldNewTarget.x;
	m_Target.y = worldNewTarget.y;
	m_Target.z = worldNewTarget.z;
};
void Camera::RotateDown(float deltaTime) {
	float rotateAngle = deltaTime * m_RotateSpeed;
	Vector4 localTarget = Vector4(0.0f, 0.0f, -(m_Position - m_Target).Length(), 1);
	Vector4 localNewTarget = localTarget *  SetRotationAroundX(rotateAngle);
	Vector4 worldNewTarget = localNewTarget * GetWorldMatrix();
	m_Target.x = worldNewTarget.x;
	m_Target.y = worldNewTarget.y;
	m_Target.z = worldNewTarget.z;
};

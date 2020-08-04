#include <stdafx.h>
#include"SceneManagement.h"

SceneManagement* SceneManagement::s_Instance = NULL;


SceneManagement::SceneManagement()
{
}


SceneManagement::~SceneManagement()
{
}
SceneManagement* SceneManagement::GetInstance() {
	if (!s_Instance)
		s_Instance = new SceneManagement;
	return s_Instance;
}
void SceneManagement::AddObject(Object * object)
{
	m_vListObject.push_back(object);
}
void SceneManagement::Init() {};

void SceneManagement::Update(float deltaTime) {};
void SceneManagement::Render() {};


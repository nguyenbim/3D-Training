#include"stdafx.h"
#include<vector>
#include "../Utilities/utilities.h"
#include"Object.h"
#include"Camera.h"

#pragma once
using namespace std;

class SceneManagement
{
private:
	static SceneManagement* s_Instance;
	SceneManagement();
public:
	vector<Object *> m_vListObject;
	
	~SceneManagement();
	void Update(float deltaTime);
	void Render();
	void AddObject(Object *object);
	void Init();
	static SceneManagement* GetInstance();
};
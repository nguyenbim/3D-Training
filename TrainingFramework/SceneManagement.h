#pragma once

#include "stdafx.h"
#include<vector>
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "ResourceManagement.h"
#include "Singleton.h"
#include "Object.h"
#include "Camera.h"

using namespace std;

class SceneManagement : public Singleton<SceneManagement> {
public:
	SceneManagement();
	~SceneManagement();

	void InitWithFile(string strFilePath);

	void Update(float DeltaTime);
	void Draw();
private:
	int m_ObjectCount = 0;
	vector<Object> m_vObjects;
};
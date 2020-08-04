#pragma once

#include "stdafx.h"
#include<vector>
#include "Singleton.h"
#include "Model.h"
#include "Texture.h"
#include "Shaders.h"

#define ResourcesFolder "../Resources/"

class ResourceManagement : public Singleton<ResourceManagement> {
public:
	ResourceManagement();
	~ResourceManagement();

	void InitWithFile(std::string strFilePath);

	Model GetModel(int iID);
	Texture GetTexture(int iID);
	Texture GetCubeTexture(int iID);
	Shaders GetShader(int iID);
private:
	int m_ModelsCount = 0, m_TexturesCount = 0, m_CubeTexturesCount = 0, m_ShadersCount = 0;
	vector<Model> m_vModels;
	vector<Texture> m_vTextures;
	vector<Texture> m_vCubeTextures;
	vector<Shaders> m_vShaders;

	Model LoadModel(int ModelID, string strFilePath);
	Texture LoadTexture(int TextureID, string strFilePath, string strTiling);
	Texture LoadCubeTexture(int TextureID, string strFilePath, string strTiling);
	Shaders LoadShader(int TextureID, string strVSFile, string strFSFile);
};
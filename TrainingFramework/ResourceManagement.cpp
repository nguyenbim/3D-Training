#include "stdafx.h"
#include "ResourceManagement.h"

ResourceManagement::ResourceManagement() {
}

ResourceManagement::~ResourceManagement() {
}

void ResourceManagement::InitWithFile(string strFilePath) {
	
	FILE* FileStream;
	FileStream = fopen(strFilePath.c_str(), "r");

	// TODO: Write handling for successful / failed fopen;

	// Loading models
	fscanf(FileStream, " #Models: %d\n", &m_ModelsCount);
	printf("%d\n", m_ModelsCount);
	for (int i = 0; i < m_ModelsCount; i++) {
		int ModelID = 0;
		char strBuffer[50]; // fscanf really do not like std::string

		fscanf(FileStream, " ID %d\n", &ModelID);
		fscanf(FileStream, " FILE %s\n", strBuffer);

		// TODO: Write handling for double-quoted FilePath string

		Model Model = LoadModel(ModelID, ResourcesFolder + string(strBuffer));
		cout << ResourcesFolder + string(strBuffer)<<endl;
		m_vModels.push_back(Model);
	}

	// Loading 2D textures
	fscanf(FileStream, " #2D Textures: %d\n", &m_TexturesCount);

	for (int i = 0; i < m_TexturesCount; i++) {
		int TextureID = 0;
		char strNameBuffer[50], strTilingBuffer[50];

		fscanf(FileStream, " ID %d\n", &TextureID);
		fscanf(FileStream, " FILE %s\n", strNameBuffer);
		fscanf(FileStream, " TILING %s\n", strTilingBuffer);

		Texture graTexture = LoadTexture(TextureID, ResourcesFolder +string(strNameBuffer), strTilingBuffer);

		m_vTextures.push_back(graTexture);
	}

	// Loading Cube Textures
	fscanf(FileStream, " #Cube Textures: %d\n", &m_CubeTexturesCount);

	for (int i = 0; i < m_CubeTexturesCount; i++) {
		int TextureID = 0;
		char strNameBuffer[50], strTilingBuffer[50];

		fscanf(FileStream, " ID %d\n", &TextureID);
		fscanf(FileStream, " FILE %s\n", strNameBuffer);
		fscanf(FileStream, " TILING %s\n", strTilingBuffer);

		Texture graTexture = LoadCubeTexture(TextureID, ResourcesFolder + string(strNameBuffer), strTilingBuffer);

		m_vCubeTextures.push_back(graTexture);
	}

	// Loading Shaders
	fscanf(FileStream, " #Shaders: %d\n", &m_ShadersCount);

	for (int i = 0; i < m_ShadersCount; i++) {
		int iShaderID = 0, iStateCount = 0;
		char strVSBuffer[100], strFSBuffer[100];

		fscanf(FileStream, " ID %d\n", &iShaderID);
		fscanf(FileStream, " VS %s\n", strVSBuffer);
		fscanf(FileStream, " FS %s\n", strFSBuffer);
		fscanf(FileStream, " STATES %d\n", &iStateCount);

		for (int f = 0; f < iStateCount; f++) {
			// TODO: Handle Shaders states
		}

		Shaders graShaders = LoadShader(iShaderID, string(strVSBuffer),string(strFSBuffer));

		m_vShaders.push_back(graShaders);
	}
}

Model ResourceManagement::LoadModel(int iModelID, string strFilePath) {
	Model Model;

	*Model.GetID() = iModelID;
	printf("%d\n", iModelID);
	*Model.GetModelName() = strFilePath;

	FILE* FileStream;
	FileStream = fopen(strFilePath.c_str(), "r");
	cout << strFilePath << endl;
	// Reading Vertices
	fscanf(FileStream, "NrVertices: %d\n", Model.GetNVertice());

	for (int i = 0; i < *Model.GetNVertice(); i++) {
		Vertex NewVertex;
		fscanf(FileStream, "   %*d. pos:[%f, %f, %f]; norm:[%f, %f, %f]; binorm:[%f, %f, %f]; tgt:[%f, %f, %f]; uv:[%f, %f];\n",
			&NewVertex.pos.x, &NewVertex.pos.y, &NewVertex.pos.z,
			&NewVertex.normal.x, &NewVertex.normal.y, &NewVertex.normal.z,
			&NewVertex.binormal.x, &NewVertex.binormal.y, &NewVertex.binormal.z,
			&NewVertex.tangent.x, &NewVertex.tangent.y, &NewVertex.tangent.z,
			&NewVertex.uv.x, &NewVertex.uv.y
		);
		Model.GetVerticesData()->push_back(NewVertex);
	}

	// Reading Indices
	fscanf(FileStream, "NrIndices: %d\n", Model.GetNIndices());

	for (int i = 0; i < *Model.GetNIndices(); i += 3) {
		GLuint NewIndex1, NewIndex2, NewIndex3;
		fscanf(FileStream, " %*d. %d, %d, %d\n",
			&NewIndex1,
			&NewIndex2,
			&NewIndex3
		);
		Model.GetIndicesData()->push_back(NewIndex1);
		Model.GetIndicesData()->push_back(NewIndex2);
		Model.GetIndicesData()->push_back(NewIndex3);
	}

	// Creating VBO Buffer
	GLuint VBOid;
	
	glGenBuffers(1, &VBOid);
	glBindBuffer(GL_ARRAY_BUFFER, VBOid);
	glBufferData(GL_ARRAY_BUFFER, *Model.GetNVertice() * sizeof(Vertex), Model.GetVerticesData()->data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	*Model.GetVBOId() = VBOid;

	// Creating IBO Buffer
	GLuint IBOid;

	glGenBuffers(1, &IBOid);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBOid);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, *Model.GetNIndices() * sizeof(GLuint), Model.GetIndicesData()->data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	*Model.GetIBOId() = IBOid;

	return Model;
}

Texture ResourceManagement::LoadTexture(int iTextureID, std::string strFilePath, std::string strTiling) {
	Texture Texture;

	*Texture.GetID() = iTextureID;
	*Texture.GetTextureName() = strFilePath;
	*Texture.GetTiling() = strTiling;

	GLuint TextureID;

	// Creating OpenGL ES texture resource and get the handle
	glGenBuffers(1, &TextureID);

	// Bind texture to 2D texture type
	glBindTexture(GL_TEXTURE_2D, TextureID);

	// Create CPU buffer and load image data
	int iWidth, iHeight, iBPP;
	char* bufferTGA = LoadTGA(strFilePath.c_str(), &iWidth, &iHeight, &iBPP);

	// Load data into OpenGL ES texture resource
	if (iBPP == 24) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, iWidth, iHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, bufferTGA);
	}
	else {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, iWidth, iHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, bufferTGA);
	}

	// Release memory
	if (bufferTGA != NULL) delete(bufferTGA);

	// Set wrapping modes
	if (strTiling == "REPEAT") {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}
	else if (strTiling == "CLAMP") {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}
	else {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	// Set filters for minification and magnification
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Unbind texture
	glBindTexture(GL_TEXTURE_2D, 0);

	*Texture.GetTextureID() = TextureID;

	return Texture;
}

Texture ResourceManagement::LoadCubeTexture(int iTextureID, string strFilePath, string strTiling) {
	Texture Texture;
	return Texture;
}

Shaders ResourceManagement::LoadShader(int iTextureID, string strVSFile, string strFSFile) {
	Shaders Shaders;
	strVSFile = ResourcesFolder + strVSFile;
	strFSFile = ResourcesFolder + strFSFile;
	Shaders.Init(strVSFile, strFSFile);
	return Shaders;
}

Model ResourceManagement::GetModel(int iID) {
	for (int i = 0; i < m_ModelsCount; i++) {
		if (*m_vModels.at(i).GetID() == iID) {
			return m_vModels.at(i);
		}
	}
	Model EmptyModel;
	return EmptyModel;
}

Texture ResourceManagement::GetTexture(int iID) {
	for (int i = 0; i < m_TexturesCount; i++) {
		if (*m_vTextures.at(i).GetID() == iID) {
			return m_vTextures.at(i);
		}
	}
	Texture EmptyTexture;
	return EmptyTexture;
}

Texture ResourceManagement::GetCubeTexture(int iID) {
	for (int i = 0; i < m_CubeTexturesCount; i++) {
		if (*m_vCubeTextures.at(i).GetID() == iID) {
			return m_vCubeTextures.at(i);
		}
	}
	Texture EmptyTexture;
	return EmptyTexture;
}

Shaders ResourceManagement::GetShader(int iID) {
	for (int i = 0; i < m_ShadersCount; i++) {
		if (*m_vShaders.at(i).GetID() == iID) {
			return m_vShaders.at(i);
		}
	}
	return m_vShaders.at(0);
}
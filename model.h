#pragma once
#pragma comment(lib,"glew32.lib")
#pragma comment(lib,"glew32s.lib")
#pragma comment(lib,"assimp-vc140-mt.lib")

#include <array>
#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "mesh.h"
#include "shader.h"
#include "texture.h"

class Model
{
public:
	Model() = default;
	~Model();
	__forceinline void SetShader(Shader* shader) { mShader = shader; }
	__forceinline Shader* GetShader() { return mShader; }
	__forceinline void  translate(const glm::vec3& pos) { transform = glm::translate(transform,pos);}
	__forceinline void  rotate(const glm::vec3& rot,float angle,const glm::vec3& dir) { transform = glm::rotate(transform, angle, dir);}
	__forceinline void  scale(const glm::vec3&  scale) { transform = glm::scale(transform, scale); }
	__forceinline const glm::mat4x4& GetTransform() { return transform; } const
	void Update(float deltaTime) {}
	void LoadModel(const std::string& path);
	void Draw(const Shader& shader);
	void Draw();
private:
	std::vector<Texture> textures_loaded;
	std::vector<Mesh> meshes;
	std::string directory;
	glm::mat4x4 transform;
	Shader* mShader;
	void ProcessNode(aiNode* node, const aiScene* scene);
	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
	void LoadMaterialTextures(std::vector<Texture>& textures, aiMaterial* mat, aiTextureType type,
		const std::string& typeName);
};
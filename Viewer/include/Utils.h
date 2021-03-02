#pragma once
#include <glm/glm.hpp>
#include <string>
#include "MeshModel.h"
#include "Camera.h"
#include "Light.h"

class Utils
{
public:
	static glm::vec3 Vec3fFromStream(std::istream& issLine);
	static glm::vec2 Vec2fFromStream(std::istream& issLine);
	static std::shared_ptr<MeshModel> LoadMeshModel(const std::string& filePath);
	static std::shared_ptr<Camera> LoadCamera(const std::string& filePath);
	static std::shared_ptr<Light> LoadLight();
	static std::string GetFileName(const std::string& filePath);
};

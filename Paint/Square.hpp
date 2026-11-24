#pragma once

#include <glm/gtc/type_ptr.hpp>
#include "../includes/GLUtils.hpp"
#include "SceneObject.hpp"

static MeshObject<Vertex> SquareMesh = {
	{
		{{ 0.5f,  0.5f, 0.f}, {0.f, 1.f, 0.f}, {1.f, 0.f}},
		{{-0.5f,  0.5f, 0.f}, {0.f, 1.f, 0.f}, {0.f, 0.f}},
		{{-0.5f, -0.5f, 0.f}, {0.f, 1.f, 0.f}, {0.f, 1.f}},
		{{ 0.5f, -0.5f, 0.f}, {0.f, 1.f, 0.f}, {1.f, 1.f}}
	},
	{
		0, 1, 2,
		0, 2, 3
	}
};

class Square : virtual public SceneObject
{
public:
	Square(glm::mat4 transform, glm::vec3 color) : SceneObject(SquareMesh, transform, color) {};

	~Square() override = default;

	bool IsHit(glm::vec2& point) override
	{
		glm::vec2 reversed = ReverseTransform(point, transform);

		return reversed.x <= SquareMesh.vertexArray[0].position.x && reversed.y <= SquareMesh.vertexArray[0].position.y;
	}
};
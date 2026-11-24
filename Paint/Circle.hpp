#pragma once

#include <glm/gtc/type_ptr.hpp>
#include "../includes/GLUtils.hpp"
#include "SceneObject.hpp"

static MeshObject<Vertex> CircleMesh = {
	{
		{{ 0.5f,		 0.f,		0.f}, {0.f, 0.f, 0.f}, {0.f, 0.f}},
		{{ 0.482963f,	 0.12941f,	0.f}, {0.f, 0.f, 0.f}, {0.f, 0.f}},
		{{ 0.433013f,	 0.25f,		0.f}, {0.f, 0.f, 0.f}, {0.f, 0.f}},
		{{ 0.353553f,	 0.353553f,	0.f}, {0.f, 0.f, 0.f}, {0.f, 0.f}},
		{{ 0.25f,		 0.433013f,	0.f}, {0.f, 0.f, 0.f}, {0.f, 0.f}},
		{{ 0.12941f,	 0.482963f,	0.f}, {0.f, 0.f, 0.f}, {0.f, 0.f}},
		{{ 0.f,			 0.5f,		0.f}, {0.f, 0.f, 0.f}, {0.f, 0.f}},
		{{-0.12941f,	 0.482963f,	0.f}, {0.f, 0.f, 0.f}, {0.f, 0.f}},
		{{-0.25f,		 0.433013f,	0.f}, {0.f, 0.f, 0.f}, {0.f, 0.f}},
		{{-0.353553f,	 0.353553f,	0.f}, {0.f, 0.f, 0.f}, {0.f, 0.f}},
		{{-0.433013f,	 0.25f,		0.f}, {0.f, 0.f, 0.f}, {0.f, 0.f}},
		{{-0.482963f,	 0.12941f,	0.f}, {0.f, 0.f, 0.f}, {0.f, 0.f}},
		{{-0.5f,		-0.f,		0.f}, {0.f, 0.f, 0.f}, {0.f, 0.f}},
		{{-0.482963f,	-0.12941f,	0.f}, {0.f, 0.f, 0.f}, {0.f, 0.f}},
		{{-0.433013f,	-0.25f,		0.f}, {0.f, 0.f, 0.f}, {0.f, 0.f}},
		{{-0.353553f,	-0.353553f,	0.f}, {0.f, 0.f, 0.f}, {0.f, 0.f}},
		{{-0.25f,		-0.433013f,	0.f}, {0.f, 0.f, 0.f}, {0.f, 0.f}},
		{{-0.129409f,	-0.482963f,	0.f}, {0.f, 0.f, 0.f}, {0.f, 0.f}},
		{{ 0.f,			-0.5f,		0.f}, {0.f, 0.f, 0.f}, {0.f, 0.f}},
		{{ 0.12941f,	-0.482963f,	0.f}, {0.f, 0.f, 0.f}, {0.f, 0.f}},
		{{ 0.25f,		-0.433013f,	0.f}, {0.f, 0.f, 0.f}, {0.f, 0.f}},
		{{ 0.353553f,	-0.353553f,	0.f}, {0.f, 0.f, 0.f}, {0.f, 0.f}},
		{{ 0.433013f,	-0.25f,		0.f}, {0.f, 0.f, 0.f}, {0.f, 0.f}},
		{{ 0.482963f,	-0.12941f,	0.f}, {0.f, 0.f, 0.f}, {0.f, 0.f}}
	},
	{
		0,	1,	2,
		2,	3,	4,
		4,	5,	6,
		6,	7,	8,
		8,	9,	10,
		10,	11,	12,
		12,	13,	14,
		14,	15,	16,
		16,	17,	18,
		18,	19,	20,
		20,	21,	22,
		22,	23,	0,
		0,	2,	4,
		4,	6,	8,
		8,	10,	12,
		12,	14,	16,
		16,	18,	20,
		20,	22,	0,
		0,	4,	8,
		8,	12,	16,
		16,	20,	0,
		0,	8,	16
	}
};

class Circle : virtual public SceneObject
{
public:
	Circle(glm::mat4 transform, glm::vec3 color) : SceneObject(CircleMesh, transform, color) {};

	~Circle() override = default;

	bool IsHit(glm::vec2& point) override
	{
		glm::vec2 reversed = ReverseTransform(point, transform);

		return glm::distance(reversed, glm::vec2(0.f, 0.f)) <= CircleMesh.vertexArray[0].position.x;
	}
};
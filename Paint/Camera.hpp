#pragma once

#include <glm/glm.hpp>

class Camera
{
private:
	const float Z_NEAR = 0.f;
	const float Z_FAR = 1.f;

	glm::mat4 projMatrix;

public:
	Camera()
	{
		this->projMatrix = glm::ortho(-1.f, 1.f, 1.f, -1.f, Z_NEAR, Z_FAR);
	}

	~Camera() {}

	inline glm::mat4 GetViewProj() const
	{
		return projMatrix;
	}

	inline void SetViewProj(const float width, const float height)
	{
		float relativeWidth;
		float relativeHeight;

		if (width > height)
		{
			relativeWidth = width / height;
			relativeHeight = 1.f;
		}
		else
		{
			relativeWidth = 1.f;
			relativeHeight = height / width;
		}

		this->projMatrix = glm::ortho(-relativeWidth, relativeWidth, relativeHeight, -relativeHeight, Z_NEAR, Z_FAR);
	}
};
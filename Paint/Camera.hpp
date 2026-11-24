#pragma once

#include <glm/glm.hpp>

class Camera
{
private:
	const float Z_NEAR = 0.f;
	const float Z_FAR = 1.f;

	glm::vec2 relativeSize;
	glm::mat4 projMatrix;

public:
	Camera()
	{
		this->relativeSize = glm::vec2(1.f);
		this->projMatrix = glm::ortho(-1.f, 1.f, 1.f, -1.f, Z_NEAR, Z_FAR);
	}

	~Camera() {}

	inline float GetRelativeWidth() const { return this->relativeSize.x; }

	inline float GetRelativeHeight() const { return this->relativeSize.y; }

	inline glm::mat4 GetViewProj() const { return this->projMatrix; }

	void SetViewProj(const float width, const float height)
	{
		if (width > height)
		{
			this->relativeSize.x = width / height;
			this->relativeSize.y = 1.f;
		}
		else
		{
			this->relativeSize.x = 1.f;
			this->relativeSize.y = height / width;
		}

		this->projMatrix = glm::ortho(-this->relativeSize.x, this->relativeSize.x, this->relativeSize.y, -this->relativeSize.y, Z_NEAR, Z_FAR);
	}

	inline glm::vec2 PositionToCenter(glm::ivec2 windowSize, glm::ivec2 pixel) const
	{
		return ((glm::vec2(pixel) / glm::vec2(windowSize) - 0.5f) * this->relativeSize) * 2.f;
	}

	inline glm::vec2 PositionToTopLeft(glm::ivec2 windowSize, glm::ivec2 pixel) const
	{
		return glm::vec2(pixel) / glm::vec2(windowSize) * this->relativeSize;
	}
};
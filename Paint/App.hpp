#pragma once

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>

// GLEW
#include <GL/glew.h>

// SDL
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

// Utils
#include "../Camera.hpp"
#include "../includes/GLUtils.hpp"

// Mine
#include "SceneObject.hpp"

struct SUpdateInfo
{
	float ElapsedTimeInSec = 0.0f;
	float DeltaTimeInSec = 0.0f;
};

struct Intersection
{
	glm::vec2 uv;
	float t;
};

class App
{
public:
	App();
	~App();

	bool Init();
	void Clean();

	void Update(const SUpdateInfo&);
	void Render();
	void RenderGUI();

	void KeyboardDown(const SDL_KeyboardEvent&);
	void KeyboardUp(const SDL_KeyboardEvent&);
	void MouseMove(const SDL_MouseMotionEvent&);
	void MouseDown(const SDL_MouseButtonEvent&);
	void MouseUp(const SDL_MouseButtonEvent&);
	void MouseWheel(const SDL_MouseWheelEvent&);
	void Resize(int, int);

	void OtherEvent(const SDL_Event&);

protected:
	void SetupDebugCallback();

	// Other data

	float m_ElapsedTimeInSec = 0.0f;

	// Picking

	glm::ivec2 pickedPixel = glm::ivec2(0, 0);

	glm::uvec2 windowSize = glm::uvec2(0, 0);

	// Camera

	Camera camera;

	// Shader

	GLuint programID = 0;

	void InitShaders();
	void CleanShaders() const;

	// Geometry

	void SetCommonUniforms();

	std::vector<SceneObject*> objects;

	void InitGeometry();
	void CleanGeometry();
	void InitObjects();
	void CleanObjects();

	// Texture

	GLuint samplerID = 0;

	void InitTextures();
	void CleanTextures() const;
};
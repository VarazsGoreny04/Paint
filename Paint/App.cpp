#pragma once

#include "../includes/SDL_GLDebugMessageCallback.hpp"

#include <imgui.h>
#include "App.hpp"
#include "SceneObject.hpp"
#include "Square.hpp"
#include "Circle.hpp"
#include "ImageHandler.hpp"

App::App() {}

App::~App() {}

void App::SetupDebugCallback()
{
	GLint context_flags;
	glGetIntegerv(GL_CONTEXT_FLAGS, &context_flags);
	if (context_flags & GL_CONTEXT_FLAG_DEBUG_BIT) {
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, nullptr, GL_FALSE);
		glDebugMessageControl(GL_DONT_CARE, GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR, GL_DONT_CARE, 0, nullptr, GL_FALSE);
		glDebugMessageCallback(SDL_GLDebugMessageCallback, nullptr);
	}
}

void App::InitShaders()
{
	programID = glCreateProgram();
	AttachShader(programID, GL_VERTEX_SHADER, "../Shaders/Vert.vert");
	AttachShader(programID, GL_FRAGMENT_SHADER, "../Shaders/Frag.frag");
	LinkProgram(programID);
}

void App::CleanShaders() const
{
	glDeleteProgram(programID);
}

void App::InitGeometry()
{
}

void App::CleanGeometry()
{
}

void App::InitTextures()
{
	glCreateSamplers(1, &samplerID);
	glSamplerParameteri(samplerID, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glSamplerParameteri(samplerID, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glSamplerParameteri(samplerID, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glSamplerParameteri(samplerID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void App::CleanTextures() const
{
	glDeleteSamplers(1, &samplerID);
}

void App::InitObjects()
{
	objects.clear();

	const size_t size = imageSize;

	const float sizeF = static_cast<float>(size);
	const float offset = (sizeF - 1.f) / 2.f;
	const float scale = 2.f / sizeF;

	for (size_t y = 0; y < size; ++y)
	{
		for (size_t x = 0; x < size; ++x)
		{
			objects.push_back(
				new Square(
					glm::translate(glm::vec3((static_cast<float>(x) - offset), (static_cast<float>(y) - offset), 0.f) * 2.f / sizeF) *
					glm::scale(glm::vec3(scale, scale, 1.f)),
					glm::vec3(static_cast<float>((y + x) % 2))
				)
			);
		}
	}
}

void App::CleanObjects()
{
	for (const SceneObject* object : objects)
		delete object;
}

bool App::Init()
{
	SetupDebugCallback();

	glClearColor(0.125f, 0.25f, 0.5f, 1.0f);

	InitShaders();
	InitGeometry();
	InitTextures();
	InitObjects();

	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);

	glEnable(GL_DEPTH_TEST);

	return true;
}

void App::Clean()
{
	CleanObjects();
	CleanShaders();
	CleanGeometry();
	CleanTextures();
}


void App::Update(const SUpdateInfo& updateInfo)
{
	elapsedTimeInSec = updateInfo.ElapsedTimeInSec;
}

void App::SetCommonUniforms()
{
	glProgramUniformMatrix4fv(programID, ul(programID, "viewProj"), 1, GL_FALSE, glm::value_ptr(camera.GetViewProj()));
}

void App::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	SetCommonUniforms();

	glUseProgram(programID);

	glBindSampler(0, samplerID);

	if (nextImageSize != imageSize)
	{
		imageSize = nextImageSize;

		InitObjects();
	}

	SceneObject::Render(programID, marker, glm::translate(glm::vec3(mousePosition, 0.f)));

	for (const SceneObject* object : objects)
		SceneObject::Render(programID, object);

	glBindTextureUnit(0, 0);
	glBindSampler(0, 0);

	glBindVertexArray(0);

	glUseProgram(0);
}

void App::RenderGUI()
{
	if (ImGui::Begin("Variables"))
	{
		ImGui::SliderInt("Side length", &nextImageSize, 1, 50);
	}
	ImGui::End();
}

void App::KeyboardDown(const SDL_KeyboardEvent& key)
{
	if (key.repeat == 0)
	{
		if (key.keysym.sym == SDLK_F5 && key.keysym.mod & KMOD_CTRL)
		{
			CleanShaders();
			InitShaders();
		}
		if (key.keysym.sym == SDLK_F1)
		{
			GLint polygonModeFrontAndBack[2] = {};

			glGetIntegerv(GL_POLYGON_MODE, polygonModeFrontAndBack);
			GLenum polygonMode = (polygonModeFrontAndBack[0] != GL_FILL ? GL_FILL : GL_LINE);

			glPolygonMode(GL_FRONT_AND_BACK, polygonMode);
		}
	}
}

void App::KeyboardUp(const SDL_KeyboardEvent& key)
{

}

void App::MouseMove(const SDL_MouseMotionEvent& mouse)
{
	mousePosition = camera.PositionToCenter(windowSize, glm::vec2(mouse.x, mouse.y));
}

void App::MouseDown(const SDL_MouseButtonEvent& mouse)
{
	std::vector<std::shared_ptr<glm::vec3>> data;

	for (SceneObject* object : objects)
		data.push_back(std::make_unique<glm::vec3>(object->GetColor()));

	ImageHandler::SaveBMP("image.bmp", data);
}

void App::MouseUp(const SDL_MouseButtonEvent& mouse)
{

}

void App::MouseWheel(const SDL_MouseWheelEvent& wheel)
{

}

void App::Resize(int width, int height)
{
	glViewport(0, 0, width, height);
	windowSize = glm::uvec2(width, height);
	camera.SetViewProj((float)width, (float)height);
}

void App::OtherEvent(const SDL_Event& ev)
{

}
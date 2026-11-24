#pragma once

#include <glm/gtc/type_ptr.hpp>
#include <initializer_list>

static std::initializer_list<VertexAttributeDescriptor> VertexAttribList =
{
	{0, offsetof(Vertex, position), 3, GL_FLOAT},
	{1, offsetof(Vertex, normal), 3, GL_FLOAT},
	{2, offsetof(Vertex, texcoord), 2, GL_FLOAT},
};

class SceneObject
{
protected:
	OGLObject oglObject;
	glm::mat4 transform;
	glm::vec3 color;

	inline static glm::vec2 ReverseTransform(glm::vec2& point, glm::mat4& transform) { return glm::inverse(transform) * glm::vec4(point, 0.f, 0.f); }

	static void DrawObject(const OGLObject& obj, const glm::mat4& world) {
		glUniformMatrix4fv(ul("world"), 1, GL_FALSE, glm::value_ptr(world));
		glUniformMatrix4fv(ul("worldIT"), 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(world))));
		glBindVertexArray(obj.vaoID);
		glDrawElements(GL_TRIANGLES, obj.count, GL_UNSIGNED_INT, nullptr);
	}

public:
	SceneObject(MeshObject<Vertex>& mesh, glm::mat4& transform, glm::vec3& color)
	{
		this->oglObject = CreateGLObjectFromMesh(mesh, VertexAttribList);
		this->transform = transform;
		this->color = color;
	}

	virtual ~SceneObject() = default;

	inline glm::mat4 GetTransform() const { return this->transform; }

	inline void SetTransform(const glm::mat4 transform) { this->transform = transform; }

	inline glm::vec3 GetColor() const { return this->color; }

	inline void SetColor(const glm::vec3& color, const float strength) { this->color = this->color * (1.f - strength) + color * strength; }

	virtual bool IsHit(glm::vec2& point) = 0;

	inline static void Render(const GLuint& programID, const SceneObject* sceneObject)
	{
		glProgramUniform3fv(programID, ul(programID, "color"), 1, glm::value_ptr(sceneObject->color));
		SceneObject::DrawObject(sceneObject->oglObject, sceneObject->transform);
	}

	inline static void Render(const GLuint& programID, const SceneObject* sceneObject, const glm::mat4 transform)
	{
		glProgramUniform3fv(programID, ul(programID, "color"), 1, glm::value_ptr(sceneObject->color));
		SceneObject::DrawObject(sceneObject->oglObject, transform * sceneObject->transform);
	}
};
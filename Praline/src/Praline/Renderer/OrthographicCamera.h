#pragma once

#include <glm/glm.hpp>

namespace Praline
{
	class OrthographicCamera
	{
	public:
		OrthographicCamera(float left, float right, float bottom, float top);
		~OrthographicCamera() = default;

		void SetProjection(float left, float right, float bottom, float top);

		inline const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }
		inline const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		inline const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }

		void SetPosition(const glm::vec3& position);
		inline const glm::vec3& GetPosition() const { return m_Position; }

		void SetRotation(float rotation);
		inline float GetRotation() const { return m_Rotation; }



	private:
		void RecalculateViewMatrix();

	private:
		glm::mat4 m_ProjectionMatrix; // FOV and Aspect Ratio
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;;

		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
		float m_Rotation = 0.0f;
	};
}


#pragma once

#include "RenderCommand.h"
#include <glm/glm.hpp>

namespace Praline
{
	class OrthographicCamera;
	class Shader;
}

namespace Praline
{
	class Renderer
	{
	public:
		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();

		static void Submit(const std::shared_ptr<Shader> shader, const std::shared_ptr<VertexArray>& vertexArray);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData
		{
			glm::mat4 m_ViewProjectionMatrix;
		};

		static SceneData* m_SceneData;
	};
}


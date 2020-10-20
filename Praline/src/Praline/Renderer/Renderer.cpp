#include "PralinePCH.h"
#include "Renderer.h"
#include "Shader.h"

#include "OrthographicCamera.h"

namespace Praline
{
	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

	void Renderer::BeginScene(const OrthographicCamera& camera)
	{
		m_SceneData->m_ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{

	}

	void Renderer::Submit(const std::shared_ptr<Shader> shader, const std::shared_ptr<VertexArray>& vertexArray)
	{
		shader->Bind();
		shader->UploadUniformMat4("u_ViewProjectionMatrix", m_SceneData->m_ViewProjectionMatrix);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}


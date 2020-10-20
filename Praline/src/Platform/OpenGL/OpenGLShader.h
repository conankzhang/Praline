#pragma once

#include "Praline/Renderer/Shader.h"
#include "Praline/Renderer/Buffer.h"

namespace Praline
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertexSource, const std::string& fragmentSource);
		virtual ~OpenGLShader() override;

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) override;

	private:
		uint32_t m_RendererID;
	};
}


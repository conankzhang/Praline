#include "PralinePCH.h"
#include "Shader.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Praline
{
	Shader* Shader::Create(const std::string& vertexSource, const std::string& fragmentSource)
	{
		switch(Renderer::GetAPI())
		{
		case RendererAPI::None:
			PRALINE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::OpenGL:
			return new OpenGLShader(vertexSource, fragmentSource);
		}

		PRALINE_CORE_ASSERT(false, "Unkown RendererAPI!");
		return nullptr;
	}
}

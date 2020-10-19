#include "PralinePCH.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Praline
{
	VertexArray* VertexArray::Create()
	{
		switch(Renderer::GetAPI())
		{
		case RendererAPI::None:
			PRALINE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::OpenGL:
			return new OpenGLVertexArray();
		}

		PRALINE_CORE_ASSERT(false, "Unkown RendererAPI!");
		return nullptr;
	}
}

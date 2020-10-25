#include "PralinePCH.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Praline
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}


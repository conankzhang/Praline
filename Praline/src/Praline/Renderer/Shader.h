#pragma once

#include <string>

#include <glm/glm.hpp>

namespace Praline
{
	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static Ref<Shader> Create(const std::string& vertexSource, const std::string& fragmentSource);
		static Ref<Shader> Create(const std::string& filePath);
	};
}

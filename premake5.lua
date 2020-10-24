workspace "Praline"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

    startproject "Sandbox"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder
IncludeDir = {}
IncludeDir["GLFW"] = "Praline/vendor/GLFW/include"
IncludeDir["Glad"] = "Praline/vendor/GLAD/include"
IncludeDir["ImGui"] = "Praline/vendor/ImGui"
IncludeDir["glm"] = "Praline/vendor/glm"
IncludeDir["stb_image"] = "Praline/vendor/stb_image"

group "Dependencies"
    include "Praline/vendor/GLFW"
    include "Praline/vendor/Glad"
    include "Praline/vendor/ImGui"
group ""

project "Praline"
    location "Praline"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "PralinePCH.h"
    pchsource "Praline/src/PralinePCH.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/vendor/stb_image/**.h",
        "%{prj.name}/vendor/stb_image/**.cpp",
        "%{prj.name}/vendor/glm/glm/**.hpp",
        "%{prj.name}/vendor/glm/glm/**.inl"
    }

    defines
    {
        "_CRT_SECURE_NO_WARNINGS"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.stb_image}"
    }

    links
    {
        "GLFW",
        "Glad",
        "ImGui",
        "opengl32.lib"
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "PRALINE_PLATFORM_WINDOWS",
            "PRALINE_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

    filter "configurations:Debug"
        defines "PRALINE_DEBUG"
        runtime "Debug"
        symbols "on"


    filter "configurations:Release"
        defines "PRALINE_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "PRALINE_DIST"
        runtime "Release"
        optimize "on"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "Praline/vendor/spdlog/include",
        "Praline/src",
        "Praline/vendor",
        "%{IncludeDir.glm}"
    }

    links
    {
        "Praline"
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "PRALINE_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "PRALINE_DEBUG"
        runtime "Debug"
        symbols "on"


    filter "configurations:Release"
        defines "PRALINE_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "PRALINE_DIST"
        runtime "Release"
        optimize "on"

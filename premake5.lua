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

include "Praline/vendor/GLFW"
include "Praline/vendor/Glad"
include "Praline/vendor/ImGui"

project "Praline"
    location "Praline"
    kind "SharedLib"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "PralinePCH.h"
    pchsource "Praline/src/PralinePCH.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}"
    }

    links
    {
        "GLFW",
        "Glad",
        "ImGui",
        "opengl32.lib"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "PRALINE_PLATFORM_WINDOWS",
            "PRALINE_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
        }

    filter "configurations:Debug"
        defines "PRALINE_DEBUG"
        buildoptions "/MDd"
        symbols "On"


    filter "configurations:Release"
        defines "PRALINE_RELEASE"
        buildoptions "/MD"
        optimize "On"

    filter "configurations:Dist"
        defines "PRALINE_DIST"
        buildoptions "/MD"
        optimize "On"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"

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
        "Praline/src"
    }

    links
    {
        "Praline"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "PRALINE_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "PRALINE_DEBUG"
        buildoptions "/MDd"
        symbols "On"


    filter "configurations:Release"
        defines "PRALINE_RELEASE"
        buildoptions "/MD"
        optimize "On"

    filter "configurations:Dist"
        defines "PRALINE_DIST"
        buildoptions "/MD"
        optimize "On"

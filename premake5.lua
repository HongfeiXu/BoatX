workspace "boatx"
    startproject "boatxeditor"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release"
    }

tdir = "bin/%{cfg.buildcfg}/%{prj.name}"
odir = "bin-obj/%{cfg.buildcfg}/%{prj.name}"


-- External Dependencies
external = {}
external["maclibs"] = "external/maclibs"
external["sdl2"] = "external/sdl2"
external["spdlog"] = "external/spdlog"
external["glad"] = "external/glad"

-- Process Glad before anything else
include "external/glad"


project "boatx"
    location "boatx"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir(tdir)
    objdir(odir)

    files
    {
        "%{prj.name}/include/**.h",
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
    }

    externalincludedirs
    {
        "%{prj.name}/include/boatx",
        "%{external.sdl2}/include",
        "%{external.spdlog}/include"
    }

    flags
    {
        "FatalWarnings"
    }

    defines
    {
        "GLFW_INCLUDE_NONE" -- Ensures glad doesn't include glfw
    }

    -- platform relates
    filter {"system:windows" , "configurations:*"}
        systemversion "latest"
        defines
        {
            "BOATX_PLATFORM_WINDOWS"
        }

    filter {"system:macosx" , "configurations:*"}
        xcodebuildsettings
        {
            ["MACOSX_DEPLOYMENT_TARGET"] = "10.15",
            ["UserModernBuildSystem"] = "NO"
        }    
        defines
        {
            "BOATX_PLATFORM_MAC"
        }
    
    filter {"system:linux" , "configurations:*"}
        defines
        {
            "BOATX_PLATFORM_LINUX"
        }

    -- debug\release relates
    filter "configurations:Debug"
        defines
        {
            "BOATX_CONFIG_DEBUG"
        }
        runtime "Debug"
        symbols "on"
        
    filter "configurations:Release"
        defines
        {
            "BOATX_CONFIG_RELEASE"
        }
        runtime "Release"
        symbols "off"
        optimize "on"


project "boatxeditor"
    location "boatxeditor"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"
    links "boatx"

    targetdir(tdir)
    objdir(odir)

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
    }

    externalincludedirs
    {
        "boatx/include"
    }

    flags
    {
        "FatalWarnings"
    }

    filter {"system:windows" , "configurations:*"}
        systemversion "latest"
        defines
        {
            "BOATX_PLATFORM_WINDOWS"
        }
        libdirs
        {
            "%{external.sdl2}/lib"
        }
        links
        {
            "SDL2",
            "glad"
        }

    filter {"system:macosx" , "configurations:*"}
        xcodebuildsettings
        {
            ["MACOSX_DEPLOYMENT_TARGET"] = "10.15",
            ["UserModernBuildSystem"] = "NO"
        }    
        defines
        {
            "BOATX_PLATFORM_MAC"
        }
        abspath = path.getabsolute("%{externals.maclibs}")
        linkoptions {"-f ".. abspath}
        links
        {
            "SDL2.framework",
            "glad"
        }

    filter {"system:linux" , "configurations:*"}
        defines
        {
            "BOATX_PLATFORM_LINUX"
        }
        links
        {
            "SDL2",
            "glad"
        }

    filter "configurations:Debug"
        defines
        {
            "BOATX_CONFIG_DEBUG"
        }
        runtime "Debug"
        symbols "on"
        
    filter "configurations:Release"
        defines
        {
            "BOATX_CONFIG_RELEASE"
        }
        runtime "Release"
        symbols "off"
        optimize "on"


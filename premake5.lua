workspace "boatx"
    startproject "boatxeditor"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release"
    }

project "boatxeditor"
    location "boatxeditor"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
    }

    flags
    {
        "FatalWarnings"
    }

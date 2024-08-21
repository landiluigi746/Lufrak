--Adapted from Jeffery Myers' https://github.com/raylib-extras/game-premake

newoption
{
    trigger = "graphics",
    value = "OPENGL_VERSION",
    description = "version of OpenGL to build raylib against",
    allowed = {
        { "opengl11", "OpenGL 1.1"},
        { "opengl21", "OpenGL 2.1"},
        { "opengl33", "OpenGL 3.3"},
        { "opengl43", "OpenGL 4.3"},
        { "opengles2", "OpenGLES 2.0"},
        { "opengles3", "OpenGLES 3.0"}
    },
    default = "opengl33"
}

function link_to(lib)
    links (lib)
    includedirs ("../"..lib.."/include")
    includedirs ("../"..lib.."/" )
end

workspace ("Lufrak")
    configurations { "Debug", "Release"}
    platforms { "x64" }

    defaultplatform ("x64")

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"

    filter { "platforms:x64" }
        architecture "x86_64"
    
    filter {}

    targetdir "bin/%{cfg.buildcfg}/"

    startproject "Lufrak-App"

os.execute("git submodule update --init")

group "Dependencies"
    include ("Vendor/raylib_premake5.lua")
    include ("Vendor/raygui_premake5.lua")
group ""

include ("App")
include ("Website")
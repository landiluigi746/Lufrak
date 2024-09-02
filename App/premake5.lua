project "Lufrak-App"
    kind "ConsoleApp"
    language "C"
    cdialect "C99"
    location "./"
    targetdir "%{wks.location}/bin/%{cfg.buildcfg}"
    objdir "%{wks.location}/bin-int/%{cfg.buildcfg}"

    targetname "Lufrak"

    filter "configurations:Release"
        kind "WindowedApp"
        entrypoint "mainCRTStartup"

    filter "action:vs*"
        debugdir "$(SolutionDir)"

    filter {"action:vs*", "configurations:Release"}
        kind "WindowedApp"
        entrypoint "mainCRTStartup"
    filter {}

    vpaths
    {
        ["Header Files/*"] = { "Source/**.h" },
        ["Source Files/*"] = { "Source/**.c" },
        ["Resource Files/*"] = { "**.rc" }
    }
    files { "Source/**.h", "Source/**.c", "**.rc", "**.h" }

    includedirs { "Source/**" }
    
    link_raylib()
    include_raygui()
project "Lufrak-App"
    kind "ConsoleApp"
    language "C"
    cdialect "C99"
    location "./"
    targetdir "%{wks.location}/bin/%{cfg.buildcfg}"
    objdir "%{wks.location}/bin-int/%{cfg.buildcfg}"

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
    }
    files { "Source/**.h", "Source/**.c" }

    includedirs { "Source/**" }
    
    link_raylib()
    include_raygui()
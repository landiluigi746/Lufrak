function get_raygui_dir()
    return "%{wks.location}/Vendor/raygui"
end

function include_raygui()
    raygui_dir = get_raygui_dir()

    includedirs { raygui_dir .. "/src", raygui_dir .. "/examples/styles" }
end
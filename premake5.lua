project "Lufrak-Website"
    kind "None"
    location "./"

    vpaths
    {
        ["Resource Files/*"] = { "./**.ico", "./**.jpg", "./**.png" }
    }
    files { "./**.html", "./**.css", "./**.js", "./**.ico", "./**.jpg", "./**.png" }
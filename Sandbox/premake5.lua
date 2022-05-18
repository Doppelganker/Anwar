project "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.cpp"
	}

	includedirs
	{
		"%{wks.location}/Anwar/vendor/spdlog/include",
		"%{wks.location}/Anwar/src",
		"%{wks.location}/Anwar/vendor",
		"%{IncludeDir.glm}",
		"%{IncludeDir.entt}"
	}

	links
	{
		"Anwar"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "ANW_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "ANW_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "ANW_DIST"
		runtime "Release"
		optimize "on"

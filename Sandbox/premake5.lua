project "Sandbox"
	language "C++"
	cppdialect "C++20"
	staticruntime "On"
	kind "ConsoleApp"

	files {
		"src/**.hpp",
		"src/**.cpp"
	}

	flags {
		"FatalCompileWarnings"
	}

	includedirs {
		"include",
		"../ASTL/include"
	}

	targetdir ("%{wks.location}/bin/" .. outputdir .. "%{prj.name}")
	objdir ("%{wks.location}/bin/" .. outputdir .. "%{prj.name}/int")
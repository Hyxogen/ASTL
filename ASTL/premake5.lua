project "ASTL"
	language "C++"
	cppdialect "C++20"
	staticruntime "On"
	kind "StaticLib"

	files {
		"src/**.hpp",
		"src/**.cpp"
	}

	flags {
		"FatalCompileWarnings"
	}

	includedirs {
		"include"
	}

	targetdir ("%{wks.location}/bin/" .. outputdir .. "%{prj.name}")
	objdir ("%{wks.location}/bin/" .. outputdir .. "%{prj.name}/int")
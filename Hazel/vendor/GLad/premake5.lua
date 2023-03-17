project "GLad"
	kind "StaticLib"
	language "C"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"include/glad/glad.h",
		"include/KHR/khrplatform.h",
	
		"src/glad.c"
	}
	
	filter "system:windows"
		staticruntime "On"
		systemversion "latest"

	filter {"system:windows" ,"configurations:Release"}
		buildoptions "/MT"

	
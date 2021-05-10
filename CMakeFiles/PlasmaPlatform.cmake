# Detect target platform
if( ${CMAKE_SYSTEM_NAME} STREQUAL "Windows" )
	set(PLASMA_PLATFORM_WINDOWS 1)	
	set(PLASMA_PLATFORM Windows)
	set(PLASMA_PLATFORM_NAME "Windows")
elseif( ${CMAKE_SYSTEM_NAME} STREQUAL "WindowsStore" )
	set(PLASMA_PLATFORM_UWP 1)
	set(PLASMA_PLATFORM UWP)
	set(PLASMA_PLATFORM_NAME "UWP")
	set(PLASMA_UWP_VERSION_MIN  "10.0.18362.0")
elseif( ${CMAKE_SYSTEM_NAME} STREQUAL "Darwin" )
	if (IOS)
		set(PLASMA_PLATFORM_IOS 1)
		set(PLASMA_PLATFORM IOS)
		set(PLASMA_PLATFORM_NAME "IOS")
	else()
		set(PLASMA_PLATFORM_OSX 1)
		set(PLASMA_PLATFORM MacOS)
		set(PLASMA_PLATFORM_NAME "MacOS")
	endif()
elseif( ${CMAKE_SYSTEM_NAME} STREQUAL "Linux" )
	set(PLASMA_PLATFORM_LINUX 1)
	set(PLASMA_PLATFORM Linux)
	set(PLASMA_PLATFORM_NAME "Linux")
elseif( ${CMAKE_SYSTEM_NAME} STREQUAL "Android" )
	set(PLASMA_PLATFORM_ANDROID 1)
	set(PLASMA_PLATFORM Android)
	set(PLASMA_PLATFORM_NAME "Android")
elseif( ${CMAKE_SYSTEM_NAME} STREQUAL "Emscripten" )
	set(PLASMA_PLATFORM_WEB 1)
	set(PLASMA_PLATFORM Web)
	set(PLASMA_PLATFORM_NAME "Web")
else()
	message(FATAL_ERROR "Unrecognized platform: ${CMAKE_SYSTEM_NAME}")
endif()
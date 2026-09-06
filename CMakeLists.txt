cmake_minimum_required(VERSION 3.5.0)
project(Cloud-System VERSION 1.0.0)
cmake_policy(SET CMP0072 NEW)

find_package(OpenGL REQUIRED)
find_package(OpenCL REQUIRED)

add_executable(Cloud-System
	# User Interface
	srcs/main.cpp
	srcs/rendering.cpp

	# Framework Classes
	framework/core/Logger.cpp

	framework/classes/Objects/ParticleSystem.cpp
	framework/classes/Objects/SkyBox.cpp
	framework/classes/Objects/Camera.cpp

	framework/classes/OpenGL/Shader.cpp
	framework/classes/OpenGL/Window.cpp
	framework/classes/OpenGL/BufferGL.cpp
	framework/classes/OpenGL/PMapBufferGL.cpp

	framework/classes/Utils/PriorityMutex.cpp
	framework/classes/Utils/NoiseGenerator.cpp

	# Dependencies
	dependencies/glad/glad.c
	dependencies/glfw/libglfw3.a
	dependencies/stb_image/stb_def.c
)

target_include_directories(Cloud-System PRIVATE
	${CMAKE_SOURCE_DIR}/includes
	${CMAKE_SOURCE_DIR}/dependencies
	${CMAKE_SOURCE_DIR}/framework
	${CMAKE_SOURCE_DIR}/framework/classes
	${CMAKE_SOURCE_DIR}/framework/core
	${OpenCL_INCLUDE_DIRS}
)

target_link_libraries(Cloud-System PRIVATE
	OpenGL::GL
	glfw
	${OpenCL_LIBRARIES}
)

set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -fsanitize=address -lasan" CACHE STRING "Debug build flags" FORCE)
set(CMAKE_CXX_FLAGS_RELEASE "-Ofast" CACHE STRING "Release build flags" FORCE)
target_compile_options(Cloud-System PRIVATE -Wall -Wextra -Wno-unknown-pragmas -fPIE)

set_target_properties(Cloud-System PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED YES
	CXX_EXTENSIONS NO
)

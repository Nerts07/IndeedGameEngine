# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("openGLfirst")


# Include sub-projects.
file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_executable (openGLfirst "src/main.cpp"  "include/VBO.h" "include/Shaders.h" "include/Textures.h" "include/WindowManager.h" "include/GLload.h" "src/WindowManager.cpp" "src/Shaders.cpp" "src/VBO.cpp" "include/VAO.h" "src/VAO.cpp" "include/EBO.h" "src/EBO.cpp" "src/Texture.cpp" "include/fps.h" "src/Fps.cpp"     "include/Cube.h"   "include/KeyMacros.h"   "include/Inputs.h" "src/Inputs.cpp"    "src/Cam.cpp"  "include/Cam.h")

set_property(TARGET openGLfirst PROPERTY CXX_STANDARD 20)
add_definitions(-DDEBUG)

install(DIRECTORY res/ DESTINATION openGLfirst\res)  # Copy resources

target_include_directories("${CMAKE_PROJECT_NAME}" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/")

if(PRODUCTION_BUILD)
	# setup the ASSETS_PATH macro to be in the root folder of your exe
	target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCES_PATH="./res/") 

	# remove the option to debug asserts.
	target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC PRODUCTION_BUILD=1) 

else()
	# This is useful to get an ASSETS_PATH in your IDE during development
	target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}./res/")
	target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC PRODUCTION_BUILD=0) 

endif()

if (MSVC)

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3")
elseif (MINGW)

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
elseif(APPLE)

    message(STATUS "Configuring for macOS")

 
    if(CMAKE_SYSTEM_PROCESSOR STREQUAL "arm64")
        message(STATUS "Configuring for Apple Silicon (arm64)")
        set(CMAKE_OSX_ARCHITECTURES "arm64")
    else()
        message(STATUS "Configuring for Intel (x86_64)")
        set(CMAKE_OSX_ARCHITECTURES "x86_64")
    endif()

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -stdlib=libc++")
endif()

add_subdirectory(thirdparty/glm)
add_subdirectory(thirdparty/glad)
add_subdirectory(thirdparty/glfw-3.4)
add_subdirectory(thirdparty/stb_image)




target_link_libraries("${CMAKE_PROJECT_NAME}" PRIVATE glm glfw glad stb_image)
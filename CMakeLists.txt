# CMakeList.txt : CMake project for OpenGL_Application, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("OpenGL_Application")



# TODO: Add tests and install targets if needed.

message(STATUS "Finding and setting packages ")
find_package(OpenGL REQUIRED) 

#get glfw
set(GLFW_INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/include/GLFW")
set(GLFW_LIBRARY "${CMAKE_CURRENT_SOURCE_DIR}/lib/GLFW/glfw3.lib")
message(STATUS "GLFW : OK")
#get glew
set(GLEW_INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/include/GLEW")
set(GLEW_LIBRARY "${CMAKE_CURRENT_SOURCE_DIR}/lib/GLEW/glew32.lib")
message(STATUS "GLEW : OK")
#get glm
set(GLM_INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/include/glm" )
message(STATUS "GLM : OK")
#get imgui
set(IMGUI_INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/include/imgui")
set(IMGUI_BACKENDS_INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/include/imgui/backends")
file(GLOB IMGUI_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/include/imgui/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/include/imgui/backends/*.cpp")
message(STATUS "IMGUI : OK")
#get stb_image
set(STB_IMAGE_INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/include/STB_IMAGE" )
set(STB_IMAGE_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/include/STB_IMAGE/stb_image.cpp" )
message(STATUS "STB_IMAGE : OK")
#get OpenGl headers
file(GLOB OPENGL_SOURCE_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/src/OpenGL/*.h" )
message(STATUS "OpenGl HEADERS : OK")
#get OpenGl sources
file(GLOB OPENGL_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/OpenGL/*.cpp")
message(STATUS "OpenGl SOURCES : OK")
#get Tests headers
file(GLOB TESTS_SOURCE_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/src/Tests/*.h" )
message(STATUS "Test HEADERS : OK")
#get Tests sources
file(GLOB TESTS_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/Tests/*.cpp")
message(STATUS "Test SOURCES : OK")
#get source headers
file(GLOB MY_SOURCE_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" )
message(STATUS "PROJECT HEADERS : OK")
#get source files
file(GLOB MY_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
message(STATUS "PROJECT SOURCES : OK")


#set include directories
include_directories(
		${GLFW_INCLUDE_PATH}
		${GLEW_INCLUDE_PATH}
		${GLM_INCLUDE_PATH}
		${IMGUI_INCLUDE_PATH}
		${IMGUI_BACKENDS_INCLUDE_PATH}
		${STB_IMAGE_INCLUDE_PATH}	
)
message(STATUS "INCLUDE : OK")
add_executable(OpenGL_Application ${MY_SOURCE_HEADERS} ${MY_SOURCE_FILES} ${IMGUI_SOURCES} ${OPENGL_SOURCE_HEADERS} ${OPENGL_SOURCE_FILES} ${TESTS_SOURCE_HEADERS} ${TESTS_SOURCE_FILES})
message(STATUS "EXECUTABLE : OK")
target_link_libraries(OpenGL_Application
	${OPENGL_LIBRARY}
	${GLFW_LIBRARY}
	${GLEW_LIBRARY}
)
message(STATUS "LIBRARIES : OK")


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET OpenGL_Application PROPERTY CXX_STANDARD 20)
endif()
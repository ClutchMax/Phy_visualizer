cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(PolyLine)


# ------------------------------------------------------------------------------
# Find VTK
# ------------------------------------------------------------------------------

find_package(VTK REQUIRED COMPONENTS 
  CommonColor
  CommonCore
  CommonDataModel
  InteractionStyle
  RenderingContextOpenGL2
  RenderingCore
  RenderingFreeType
  RenderingGL2PSOpenGL2
  RenderingOpenGL2
  IOImage
)

if (NOT VTK_FOUND)
  message(FATAL_ERROR "PolyLine: Unable to find the VTK build folder.")
endif()

# ------------------------------------------------------------------------------
# Find wxWidgets
# ------------------------------------------------------------------------------

find_package(wxWidgets REQUIRED COMPONENTS net core base)

if(wxWidgets_USE_FILE)
  include(${wxWidgets_USE_FILE})
endif()


# ------------------------------------------------------------------------------
# Add executable and link dependencies
# ------------------------------------------------------------------------------

add_executable(PolyLine
  sin.cpp
)

target_include_directories(PolyLine PRIVATE
  ${VTK_INCLUDE_DIRS}
  ${wxWidgets_INCLUDE_DIRS}
)

target_link_libraries(PolyLine PRIVATE
  ${VTK_LIBRARIES}
  ${wxWidgets_LIBRARIES}
)

# ------------------------------------------------------------------------------
# Required for VTK to initialize rendering
# ------------------------------------------------------------------------------
vtk_module_autoinit(
  TARGETS PolyLine
  MODULES ${VTK_LIBRARIES}
)

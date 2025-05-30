cmake_minimum_required(VERSION 3.14)
project(MyVTKQtApp)

# Tell CMake to find VTK and required Qt-related modules
find_package(VTK REQUIRED COMPONENTS 
  GUISupportQt
  RenderingQt
  RenderingOpenGL2
)

# Add Qt support (Qt5 here, or replace with Qt6 if needed)
find_package(Qt5 REQUIRED COMPONENTS Widgets)

# Enable MOC/UIC (for signals/slots and .ui files)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Add your sources
add_executable(MyVTKQtApp
  main.cxx
)

# Include VTK use file (sets include dirs and other variables)
include(${VTK_USE_FILE})
include_directories(/usr/include/vtk-9.1)

# Link Qt and VTK
target_link_libraries(MyVTKQtApp
  Qt5::Widgets
  ${VTK_LIBRARIES}
)

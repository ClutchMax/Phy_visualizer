cmake_minimum_required(VERSION 3.14)
project(MyVTKQtApp)

# Tell CMake to find VTK and required Qt-related modules
find_package(VTK REQUIRED COMPONENTS
    CommonCore
    RenderingCore
    InteractionStyle
    RenderingOpenGL2
    RenderingFreeType
    RenderingContext2D
    CommonColor         # <--- this is the missing piece
    GUISupportQt
)


# Add Qt support (Qt5 here, or replace with Qt6 if needed)
find_package(Qt5 REQUIRED COMPONENTS Widgets)

# Enable MOC/UIC (for signals/slots and .ui files)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)


# Add your sources
add_executable(MyVTKQtApp
  src/main.cxx
  src/animator.cxx
  src/strategy_sine_wave.cxx
  src/mainwindow.cxx
  src/strategy_factory.cxx
  include/animator.hxx
  include/animation_strategy.hxx
  include/strategy_sine_wave.hxx
  include/mainwindow.hxx
  include/strategy_factory.hxx
)

# Include VTK use file (sets include dirs and other variables)
include_directories(/usr/include/vtk-9.1)

# Link Qt and VTK
target_link_libraries(MyVTKQtApp
  Qt5::Widgets
  ${VTK_LIBRARIES}
)

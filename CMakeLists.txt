cmake_minimum_required(VERSION 3.16)
project(QtApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

# ---- enable moc, uic, rcc automatically ----
set(CMAKE_AUTOMOC ON)       # <-- this is the key line
set(CMAKE_AUTOUIC ON)       # (for .ui files – safe to leave on)
set(CMAKE_AUTORCC ON)       # (for .qrc files – optional)

add_executable(QtApp
    main.cpp
    simulator.cpp        # or simulation.cpp — make sure the name matches!
    RenderArea.cpp
)

target_link_libraries(QtApp PRIVATE Qt6::Widgets)

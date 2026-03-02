cmake_minimum_required(VERSION 3.19)
project(Worksheet6_GUI LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets LinguistTools)

qt_standard_project_setup()

qt_add_executable(Worksheet6_GUI
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    modelpart.h modelpart.cpp
    modelpartlist.h modelpartlist.cpp
    ModelPart.h
    ModelPart.cpp
    ModelPartList.h
    ModelPartList.cpp
)

qt_add_translations(
    TARGETS Worksheet6_GUI
    TS_FILES Worksheet6_GUI_en_GB.ts
)

target_link_libraries(Worksheet6_GUI
    PRIVATE
        Qt::Core
        Qt::Widgets
)

include(GNUInstallDirs)

install(TARGETS Worksheet6_GUI
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET Worksheet6_GUI
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})

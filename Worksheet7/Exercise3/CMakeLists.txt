cmake_minimum_required(VERSION 3.19)

# 🔥 REQUIRED for vcpkg (MUST be before project)
set(CMAKE_TOOLCHAIN_FILE "C:/Users/papas/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")

project(Worksheet7_Exercise3 LANGUAGES CXX)

# -------------------------------
# Qt setup
# -------------------------------
find_package(Qt6 6.5 REQUIRED COMPONENTS
    Core
    Widgets
    OpenGL
    OpenGLWidgets
    LinguistTools
)

set(CMAKE_AUTORCC ON)

qt_standard_project_setup()

# -------------------------------
# VTK setup (NO OpenVR)
# -------------------------------
set(VTK_GROUP_ENABLE_VR NO)
set(VTK_MODULE_ENABLE_VTK_RenderingOpenVR NO)

find_package(VTK REQUIRED COMPONENTS
    CommonCore
    RenderingCore
    RenderingOpenGL2
    GUISupportQt          # ✅ FIXED (NOT RenderingQt)
    InteractionStyle
    FiltersSources
)

# -------------------------------
# Executable
# -------------------------------
qt_add_executable(Worksheet7_Exercise3
    WIN32
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    modelpart.cpp
    modelpart.h
    modelpartlist.cpp
    modelpartlist.h
    icons.qrc
    optiondialog.h
    optiondialog.cpp
    optiondialog.ui
)

# -------------------------------
# Translations
# -------------------------------
qt_add_translations(TARGETS Worksheet7_Exercise3)

# -------------------------------
# Link libraries
# -------------------------------
target_link_libraries(Worksheet7_Exercise3
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt::OpenGL
        Qt::OpenGLWidgets

        VTK::CommonCore
        VTK::RenderingCore
        VTK::RenderingOpenGL2
        VTK::GUISupportQt     # ✅ FIXED
        VTK::InteractionStyle
        VTK::FiltersSources
)

# -------------------------------
# REQUIRED for VTK
# -------------------------------
vtk_module_autoinit(
    TARGETS Worksheet7_Exercise3
    MODULES
        VTK::CommonCore
        VTK::RenderingCore
        VTK::RenderingOpenGL2
        VTK::GUISupportQt     # ✅ FIXED
        VTK::InteractionStyle
        VTK::FiltersSources
)

# -------------------------------
# Install (safe)
# -------------------------------
include(GNUInstallDirs)

install(TARGETS Worksheet7_Exercise3
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

# -------------------------------
# Qt deploy script
# -------------------------------
qt_generate_deploy_app_script(
    TARGET Worksheet7_Exercise3
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)

install(SCRIPT ${deploy_script})

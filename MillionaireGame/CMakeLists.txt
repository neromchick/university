cmake_minimum_required(VERSION 3.19)
project(MillionaireGame LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(MillionaireGame
    WIN32 MACOSX_BUNDLE
    main.cpp



    startwindow.h startwindow.cpp startwindow.ui
    gamewindow.h gamewindow.cpp gamewindow.ui



)

target_link_libraries(MillionaireGame
    PRIVATE
        Qt::Core
        Qt::Widgets
)

include(GNUInstallDirs)

install(TARGETS MillionaireGame
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET MillionaireGame
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})

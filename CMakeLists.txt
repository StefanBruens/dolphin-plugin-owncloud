cmake_minimum_required(VERSION 2.6)
project(dolphin-plugin-owncloud)
find_package(KDE4 REQUIRED)
include(KDE4Defaults)
include(MacroLibrary)

add_definitions (${QT_DEFINITIONS} ${KDE4_DEFINITIONS})
add_definitions(-DQT_USE_FAST_CONCATENATION -DQT_USE_FAST_OPERATOR_PLUS)
include_directories (${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR} ${KDE4_INCLUDES} ${KDEPIMLIBS_INCLUDE_DIR})

macro_optional_find_package(LibKonq REQUIRED)
macro_log_feature(LIBKONQ_FOUND "KDE-Base/LibKonq" "Provides high-level file management functions." "http://dolphin.kde.org/" FALSE "" "Required to build the Dolphin owncloud plugin.")

include_directories( ${KDE4_INCLUDE_DIR} ${QT_INCLUDES} ${LIBKONQ_INCLUDE_DIR} )

set(fileviewowncloudplugin_SRCS
    fileviewowncloudplugin.cpp
)

# kde4_add_kcfg_files(fileviewowncloudplugin_SRCS fileviewowncloudpluginsettings.kcfgc)
kde4_add_plugin(fileviewowncloudplugin  ${fileviewowncloudplugin_SRCS})
target_link_libraries(fileviewowncloudplugin ${KDE4_KIO_LIBS} ${LIBKONQ_LIBRARY})
install(FILES fileviewowncloudplugin.desktop DESTINATION ${SERVICES_INSTALL_DIR})
# install(FILES fileviewowncloudpluginsettings.kcfg DESTINATION ${KCFG_INSTALL_DIR})
install(TARGETS fileviewowncloudplugin DESTINATION ${PLUGIN_INSTALL_DIR})


macro_display_feature_log()

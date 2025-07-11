# Required cmake version
cmake_minimum_required(VERSION 3.10.0)

# Specify search path for CMake modules to be loaded by include()
# and find_package()
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules")

### Add defaults for cmake
# These defaults need to be included before the project() call.
include(DefineCMakeDefaults)

# This will provide -DCMAKE_BUILD_TYPE=Profiling
# and -DCMAKE_BUILD_TYPE=AddressSanitizer
include(DefineCompilerFlags)
include(DefinePlatformDefaults)

project(cmocka VERSION 1.1.5 LANGUAGES C)

# global needed variables
set(APPLICATION_NAME ${PROJECT_NAME})

# SOVERSION scheme: CURRENT.AGE.REVISION
#   If there was an incompatible interface change:
#     Increment CURRENT. Set AGE and REVISION to 0
#   If there was a compatible interface change:
#     Increment AGE. Set REVISION to 0
#   If the source code was changed, but there were no interface changes:
#     Increment REVISION.
set(LIBRARY_VERSION "1.0.0")
set(LIBRARY_SOVERSION "0")

# include cmake files
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)
include(DefineOptions.cmake)
include(CPackConfig.cmake)
include(CompilerChecks.cmake)

# disallow in-source build
include(MacroEnsureOutOfSourceBuild)
macro_ensure_out_of_source_build("${PROJECT_NAME} requires an out of source build. Please create a separate build directory and run 'cmake /path/to/${PROJECT_NAME} [options]' there.")

# config.h checks
include(ConfigureChecks.cmake)
configure_file(config.h.cmake ${CMAKE_CURRENT_BINARY_DIR}/config.h)

# MinGW DLL Naming Workaround
if (MINGW)
    set(CMAKE_SHARED_LIBRARY_PREFIX "")
endif (MINGW)

# check subdirectories
add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(doc)

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    include(AddCMockaTest)
    if (UNIT_TESTING)
        add_subdirectory(tests)
    endif (UNIT_TESTING)

    if (WITH_EXAMPLES)
        add_subdirectory(example)
    endif ()
endif()

# pkg-config file
configure_file(cmocka.pc.cmake ${CMAKE_CURRENT_BINARY_DIR}/cmocka.pc @ONLY)
install(
  FILES
    ${CMAKE_CURRENT_BINARY_DIR}/cmocka.pc
  DESTINATION
  ${CMAKE_INSTALL_LIBDIR}/pkgconfig
  COMPONENT
    pkgconfig
)

configure_package_config_file(cmocka-config.cmake.in
    "${CMAKE_CURRENT_BINARY_DIR}/cmocka-config.cmake"
    INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/cmocka"
    NO_SET_AND_CHECK_MACRO
    NO_CHECK_REQUIRED_COMPONENTS_MACRO
)

write_basic_package_version_file(${PROJECT_NAME}-config-version.cmake
                                 COMPATIBILITY
                                     AnyNewerVersion)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/cmocka-config.cmake"
              "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake"
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
        COMPONENT devel)

# Add 'make dist' target which makes sure to invoke cmake before
add_custom_target(dist
                  COMMAND ${CMAKE_MAKE_PROGRAM} package_source)

# Link combile database for clangd
execute_process(COMMAND cmake -E create_symlink
                "${cmocka_BINARY_DIR}/compile_commands.json"
                "${cmocka_SOURCE_DIR}/compile_commands.json")

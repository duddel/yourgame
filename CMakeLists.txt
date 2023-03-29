# initialized from yourgamelib commit:
# 891e9275cc1f79d5b5a085fa57f9c2edb5de822e

cmake_minimum_required(VERSION 3.6)
find_package(Git)

project(yourgame VERSION 0.0.1)
# enable this option to clone yourgamelib and checkout the commit, defined
# as YOURGAME_GIT_COMMIT_REQUESTED. otherwise, the original path, where
# this project has been initialized from, is used.
set(YOURGAME_GIT_CLONE ON)

# if YOURGAME_GIT_CLONE == ON, this is the git remote url, yourgamelib is cloned from.
set(YOURGAME_GIT_REMOTE https://github.com/duddel/yourgamelib)

# the initial value of YOURGAME_GIT_COMMIT_REQUESTED is the commit of yourgamelib
# during initialization of this project.
# it should be adjusted if another (newer) version of yourgamelib is supported.
set(YOURGAME_GIT_COMMIT_REQUESTED 891e9275cc1f79d5b5a085fa57f9c2edb5de822e)

# enforce C++11 and disable extensions
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# get git commit sha and test it against the requested commit of the project:
# git describe usually returns the name of an annotated tag, but with --match="",
# no tag names match, falling back (--always) to 40 digit sha (--abbrev=40),
# appended by -dirty, if the working copy has modifications (--dirty).
execute_process(COMMAND
  "${GIT_EXECUTABLE}" describe --match=\"\" --always --abbrev=40 --dirty
  WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
  OUTPUT_VARIABLE MYGAME_GIT_COMMIT
  OUTPUT_STRIP_TRAILING_WHITESPACE)

# get the date of the git commit
execute_process(COMMAND
  "${GIT_EXECUTABLE}" log -1 --format=%ad --date=iso8601
  WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
  OUTPUT_VARIABLE MYGAME_GIT_DATE
  OUTPUT_STRIP_TRAILING_WHITESPACE)

# generate source file with version information
configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/version/mygame_version.cpp.in"
  "${CMAKE_CURRENT_BINARY_DIR}/mygame_version.cpp" @ONLY
)

# external projects
list(APPEND YOURGAME_EXT_PROJ_LIST
  "lua"
  "miniaudio"
  "bullet")

# determine the source location of the yourgame library code
if(YOURGAME_GIT_CLONE)
  if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/yourgamelib)
    message("${CMAKE_CURRENT_SOURCE_DIR}/yourgamelib exists, leaving unchanged")
  else()
    # clone yourgame library
    execute_process(COMMAND "${GIT_EXECUTABLE}" clone "${YOURGAME_GIT_REMOTE}"
      WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    )
    # checkout the requested yourgamelib commit
    execute_process(COMMAND "${GIT_EXECUTABLE}" checkout "${YOURGAME_GIT_COMMIT_REQUESTED}"
      WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/yourgamelib"
    )
  endif()
  # use the newly cloned yourgame library path
  set(YOURGAME_LIBRARY_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/yourgamelib)
else()
  # use the original yourgame library path from initialization of this project
  set(YOURGAME_LIBRARY_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/../yourgamelib)
endif()

# add the actual yourgame library as a subdirectory
add_subdirectory(
  ${YOURGAME_LIBRARY_ROOT}
  ${CMAKE_CURRENT_BINARY_DIR}/libyourgame
)

# sources
list(APPEND MYGAME_SRC_FILES
  ${CMAKE_CURRENT_BINARY_DIR}/mygame_version.cpp # generated above
)
list(APPEND MYGAME_SRC_FILES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/mygame.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/ygif_camera.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/ygif_glue.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/ygif_motion.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/ygif_trafo.cpp)

# inc dirs (internal)
list(APPEND MYGAME_INC_DIRS_PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/src
  ${CMAKE_CURRENT_SOURCE_DIR}/version
)

if(YOURGAME_PLATFORM STREQUAL "android")
  add_library(${CMAKE_PROJECT_NAME} SHARED
    ${MYGAME_SRC_FILES}
  )
  set(CMAKE_SHARED_LINKER_FLAGS
    "${CMAKE_SHARED_LINKER_FLAGS} -u ANativeActivity_onCreate"
  )
  # make sure assets/ gets copied into the android app
  # todo: convincing the Android Studio project to use ${CMAKE_CURRENT_SOURCE_DIR}/assets
  #       as the assets directory for the app is preferred, but unsolved.
  add_custom_command(
    TARGET ${CMAKE_PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/assets"
    "${CMAKE_CURRENT_SOURCE_DIR}/build/android/app/src/main/assets"
  )
endif()

if(YOURGAME_PLATFORM STREQUAL "web" OR YOURGAME_PLATFORM STREQUAL "desktop")
  # main (core) executable target
  add_executable(${CMAKE_PROJECT_NAME}
    ${MYGAME_SRC_FILES}
  ) 
  # a 2nd executable target ("_demo") is defined and configured to allow CPack to
  # generate additional archives with demo assets for desktop and web (see below).
  # the compilation is identical. for _demo, the demo assets are copied into the archive
  add_executable("${CMAKE_PROJECT_NAME}_demo" EXCLUDE_FROM_ALL
    ${MYGAME_SRC_FILES}
  )
  set_target_properties("${CMAKE_PROJECT_NAME}_demo" PROPERTIES OUTPUT_NAME "yourgame")

  # include dirs for demo project
  target_include_directories("${CMAKE_PROJECT_NAME}_demo" PRIVATE ${MYGAME_INC_DIRS_PRIVATE})

  # link libraries for demo project
  target_link_libraries("${CMAKE_PROJECT_NAME}_demo" PRIVATE yrgame)
endif()

# include dirs for core project
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${MYGAME_INC_DIRS_PRIVATE})

# link libraries for core project
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE yrgame)

# configure "components" for CPack, corresponding to the executable targets defined above
if(CPACK_GENERATOR)
  set(CPACK_COMPONENTS_ALL core demo)
  set(CPACK_ARCHIVE_COMPONENT_INSTALL ON)
  set(CPACK_INCLUDE_TOPLEVEL_DIRECTORY 0)
  include(CPack)
  cpack_add_component(core)
  cpack_add_component(demo)
endif()

  # retrieve asset files to copy
  file(GLOB CORE_ASSETS ${CMAKE_CURRENT_SOURCE_DIR}/assets/*)
  # this matches only the core assets starting with yg_, not the stub main.lua.
  # used for demo project, which provides an own main.lua:
  file(GLOB CORE_ASSETS_YG_ONLY ${CMAKE_CURRENT_SOURCE_DIR}/assets/*yg_*)
  file(GLOB DEMO_ASSETS ${CMAKE_CURRENT_SOURCE_DIR}/demo/assets/*)

if(YOURGAME_PLATFORM STREQUAL "desktop")
  # create savefiles/ beside the executable
  add_custom_command(
    TARGET ${CMAKE_PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory
    "$<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>/savefiles"
  )

  add_custom_command(
    TARGET "${CMAKE_PROJECT_NAME}_demo"
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory
    "$<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>/savefiles"
  )

  if(CPACK_GENERATOR)
    # core: yourgame
    install(TARGETS "${CMAKE_PROJECT_NAME}" DESTINATION . COMPONENT core)
    install(FILES ${CORE_ASSETS} DESTINATION ./assets COMPONENT core)
    # create empty savefiles/ 
    install(DIRECTORY DESTINATION ./savefiles COMPONENT core)

    # demo: yourgame with demo assets
    install(TARGETS "${CMAKE_PROJECT_NAME}_demo" DESTINATION . COMPONENT demo)
    install(FILES ${CORE_ASSETS_YG_ONLY} ${DEMO_ASSETS} DESTINATION ./assets COMPONENT demo)
    # create empty savefiles/ 
    install(DIRECTORY DESTINATION ./savefiles COMPONENT demo)
  endif()
endif()

if(YOURGAME_PLATFORM STREQUAL "web")
  # setting the output file extension to .html lets emscripten
  # generate an additional .html file along the .js and .wasm
  set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES SUFFIX ".html")
  # enforce GLFW v3 API (default is v2)
  # enforce WEB GL v2 (default is v1)
  # ASYNCIFY is required for emscripten_wget_data() etc.
  set(C_CXX_FLAGS_FOR_EM
    "-s USE_GLFW=3 \
    -s USE_WEBGL2=1 \
    -s ALLOW_MEMORY_GROWTH=1 \
    -s ASYNCIFY \
    --shell-file ${CMAKE_CURRENT_SOURCE_DIR}/build/shell.html")
    
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${C_CXX_FLAGS_FOR_EM}")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${C_CXX_FLAGS_FOR_EM}")

  if(CPACK_GENERATOR)
    # core: yourgame
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}.html DESTINATION . RENAME index.html COMPONENT core)
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}.js DESTINATION . COMPONENT core)
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}.wasm DESTINATION . COMPONENT core)
    install(FILES ${CORE_ASSETS} DESTINATION ./assets COMPONENT core)

    # demo: yourgame with demo assets
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}.html DESTINATION . RENAME index.html COMPONENT demo)
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}.js DESTINATION . COMPONENT demo)
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}.wasm DESTINATION . COMPONENT demo)
    install(FILES ${CORE_ASSETS_YG_ONLY} ${DEMO_ASSETS} DESTINATION ./assets COMPONENT demo)
  endif()
endif()

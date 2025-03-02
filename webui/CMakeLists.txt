option(USE_MBEDTLS ON)

set(TARGET libwebui)
set(SRC "")

add_library(${TARGET} STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/StartHandler.cpp
    ${SRC}
)

target_link_libraries(${TARGET}
    PUBLIC
        Threads::Threads
        Boost::json
        libcore
        webui
)
target_include_directories(${TARGET}
    PUBLIC
        ${CMAKE_SOURCE_DIR}/core/include
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${WebUILibrary_SOURCE_DIR}/include
        ${Boost_INCLUDE_DIR}
)

target_precompile_headers(${TARGET} PRIVATE pch.h)


find_program(NPM_CMD npm REQUIRED)

set(FRONTEND_DIR ${CMAKE_CURRENT_SOURCE_DIR}/frontend)
set(FRONTEND_BUILD_DIR ${CMAKE_BINARY_DIR}/dist)
file(MAKE_DIRECTORY ${FRONTEND_BUILD_DIR})

add_custom_target(install-frontend-deps
    COMMAND ${NPM_CMD} install
    WORKING_DIRECTORY ${FRONTEND_DIR}
    COMMENT "Installing frontend dependencies..."
    VERBATIM
)

add_custom_target(build-frontend
    COMMAND ${NPM_CMD} run build
    WORKING_DIRECTORY ${FRONTEND_DIR}
    COMMENT "Building frontend..."
    VERBATIM
)

# Copy the files from the npm build folder into the target
add_custom_command(
  TARGET build-frontend
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${FRONTEND_DIR}/dist ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}
  WORKING_DIRECTORY ${FRONTEND_DIR}/dist
)

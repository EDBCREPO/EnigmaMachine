cmake_minimum_required(VERSION 3.16)
project( 2D_SVG_RENDERER CXX) 

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
	nodepp
	GIT_REPOSITORY   https://github.com/NodeppOfficial/nodepp-wasm
	GIT_TAG          origin/main
	GIT_PROGRESS     ON
)
FetchContent_MakeAvailable(nodepp)

set(EMCC_LINK_FLAGS
    "-sEXPORTED_RUNTIME_METHODS=['HEAPF32']"
    "-sNO_DISABLE_EXCEPTION_CATCHING"
    "-lwebsocket.js"
    "-lembind"
    "--bind"
    "-sWASM=1"
    "-sFETCH=1"
    "-sUSE_GLFW=3"
    "-sASYNCIFY=1"
    "-sMODULARIZE=1"
    "-sASSERTIONS=0"
    "-sFORCE_FILESYSTEM=1"
    "-sEXPORT_NAME='Module'"
)

add_executable( main ./main.cpp )
set_target_properties(main PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/www/wasm"
)
target_link_libraries( main PUBLIC nodepp )
target_link_options( main PRIVATE ${EMCC_LINK_FLAGS})

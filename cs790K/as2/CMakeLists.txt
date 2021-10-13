PROJECT(ga)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

SET(CXX11_FLAGS -std=gnu++11)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CXX11_FLAGS}")

INCLUDE_DIRECTORIES(
  "${PROJECT_SOURCE_DIR}/include"
)

# Set Includes
SET(INCLUDES ${PROJECT_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES(${INCLUDES})

# Set sources
FILE(GLOB_RECURSE SOURCES "src/*.cpp" "packages/*.cpp")
ADD_EXECUTABLE(${PROJECT_NAME} ${SOURCES})

add_custom_target("${PROJECT_NAME}_SUCCESSFUL" ALL
                  DEPENDS ${PROJECT_NAME}
                  COMMAND ${CMAKE_COMMAND} -E echo ""
                  COMMAND ${CMAKE_COMMAND} -E echo "====================="
                  COMMAND ${CMAKE_COMMAND} -E echo "  Compile complete!"
                  COMMAND ${CMAKE_COMMAND} -E echo "====================="
                  COMMAND ${CMAKE_COMMAND} -E echo ""
                  COMMAND ${CMAKE_COMMAND} -E echo "Binaries location: ${CMAKE_CURRENT_BINARY_DIR}"
                  COMMAND ${CMAKE_COMMAND} -E echo ""
                  COMMAND ${CMAKE_COMMAND} -E echo "To run the app:"
                  COMMAND ${CMAKE_COMMAND} -E echo "./${PROJECT_NAME}"
                  COMMAND ${CMAKE_COMMAND} -E echo ""
                 )

TARGET_LINK_LIBRARIES(${PROJECT_NAME})

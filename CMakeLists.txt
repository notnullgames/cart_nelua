cmake_minimum_required(VERSION 3.16)
project(mygame)

# this pulls the current cart-header from remote
file(DOWNLOAD
	"https://raw.githubusercontent.com/notnullgames/null0/refs/heads/main/carts/c/null0.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/null0.h"
)

# this creates a main.wasm and zips it into a cart in project-root
function (BUILD_CART_C name cart_dir)
  set(CART_TEMP "${CMAKE_CURRENT_BINARY_DIR}/${name}_c_temp/")
  add_executable(${name}_c_wasm "${cart_dir}/main.c")
  target_include_directories(${name}_c_wasm PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/c")
  add_custom_target(${name} ALL
		COMMAND ${CMAKE_COMMAND} -E make_directory "${CART_TEMP}"
		COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_CURRENT_SOURCE_DIR}/webroot/"
		COMMAND ${CMAKE_COMMAND} -E copy "$<TARGET_FILE:${name}_c_wasm>" "${CART_TEMP}/main.wasm"
		COMMAND ${CMAKE_COMMAND} -E copy_directory "${cart_dir}" "${CART_TEMP}"
		COMMAND ${CMAKE_COMMAND} -E rm -f "${CART_TEMP}/*.c"
		COMMAND ${CMAKE_COMMAND} -E rm -f "${CART_TEMP}/*.h"
		COMMAND ${CMAKE_COMMAND} -E chdir "${CART_TEMP}" ${CMAKE_COMMAND} -E tar "cf" "${CMAKE_CURRENT_BINARY_DIR}/${name}.null0" --format=zip .
		COMMAND ${CMAKE_COMMAND} -E rm -rf "${CART_TEMP}"
		COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${name}.null0" "${CMAKE_CURRENT_SOURCE_DIR}/webroot/"
		DEPENDS ${name}_c_wasm
		COMMENT "Creating cart ${name}.null0"
  )
endfunction()

# build your cart
BUILD_CART_C("${PROJECT_NAME}" "${CMAKE_CURRENT_SOURCE_DIR}/src")

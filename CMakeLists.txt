cmake_minimum_required(VERSION 3.16)
project(mygame)

# this pulls the current cart-headers from remote
file(DOWNLOAD
	"https://raw.githubusercontent.com/notnullgames/null0/refs/heads/main/carts/nelua/null0.nelua"
	"${CMAKE_CURRENT_SOURCE_DIR}/null0.nelua"
)
file(DOWNLOAD
	"https://raw.githubusercontent.com/notnullgames/null0/refs/heads/main/carts/c/null0.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/null0.h"
)

# this creates a main.wasm and zips it into a cart in project-root
function (BUILD_CART_NELUA name cart_dir)
  set(CART_TEMP "${CMAKE_CURRENT_BINARY_DIR}/${name}_nelua_temp/")
  add_custom_target(cart_nelua_${name} ALL
    COMMAND ${CMAKE_COMMAND} -E make_directory "${CART_TEMP}"
    COMMAND nelua --cflags=\""-I ${CMAKE_CURRENT_SOURCE_DIR}"\" -L "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/src/main.nelua" -r --cc "${CMAKE_C_COMPILER}" -o "${CART_TEMP}/main.wasm"
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${cart_dir}" "${CART_TEMP}"
    COMMAND ${CMAKE_COMMAND} -E rm -f "${CART_TEMP}/*.nelua"
    COMMAND ${CMAKE_COMMAND} -E chdir "${CART_TEMP}" ${CMAKE_COMMAND} -E tar "cf" "../${name}.null0" --format=zip .
    COMMAND ${CMAKE_COMMAND} -E rm -rf "${CART_TEMP}"
    COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${name}.null0" "${CMAKE_CURRENT_SOURCE_DIR}/webroot/"
  )
endfunction()

# build your cart
BUILD_CART_NELUA("${PROJECT_NAME}" "${CMAKE_CURRENT_SOURCE_DIR}/src")

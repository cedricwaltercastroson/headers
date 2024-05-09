cmake_minimum_required(VERSION 3.0)

set(ARCH "arm-vita-eabi" CACHE STRING "Target architecture")
set(CMAKE_INSTALL_PREFIX "$ENV{VITASDK}/" CACHE PATH "Install prefix")

if(DEFINED ENV{VITASDK})
  set(LIBS_GEN "$ENV{VITASDK}/bin/vita-libs-gen" CACHE STRING "libs-gen command")
else()
  set(LIBS_GEN "vita-libs-gen" CACHE STRING "libs-gen command")
endif()

project(vitasdk-target-headers LANGUAGES NONE)

set(STUBS_DIR stubs)
set(DB_FILE "${CMAKE_SOURCE_DIR}/db.yml")
set(DB_365_FILE "${CMAKE_SOURCE_DIR}/db_365.yml")

add_custom_command(OUTPUT "${STUBS_DIR}"
  DEPENDS "${DB_FILE}" "${DB_365_FILE}"
  COMMAND ${CMAKE_COMMAND} -E make_directory "${STUBS_DIR}"
  COMMAND "${LIBS_GEN}" "${DB_FILE}" "${STUBS_DIR}/cex-3600"
  COMMAND "${LIBS_GEN}" "${DB_365_FILE}" "${STUBS_DIR}/cex-3650"
)

add_custom_target(prepare-stubs ALL
  DEPENDS "${STUBS_DIR}"
)

install(DIRECTORY include/ DESTINATION "${ARCH}/include")
install(FILES db.yml db_365.yml DESTINATION share)

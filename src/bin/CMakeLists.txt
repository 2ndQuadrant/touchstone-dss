SET(DATAGEN_FILES ../common.c ../datagen/datagen.c ../datagen/product.c
		../datagen/sales.c ../datagen/store.c ../datagen/time.c)
SET(QUERYGEN_FILES ../common.c ../querygen/querygen.c)
set_source_files_properties(
    ${DATAGEN_FILES}
    COMPILE_FLAGS
    "-I${CMAKE_HOME_DIRECTORY}/src/include"
)
set_source_files_properties(
    ${QUERYGEN_FILES}
    COMPILE_FLAGS
    "-I${CMAKE_HOME_DIRECTORY}/src/include"
)
ADD_EXECUTABLE(${PROJECT_NAME}-datagen ${DATAGEN_FILES})
ADD_EXECUTABLE(${PROJECT_NAME}-querygen ${QUERYGEN_FILES})
SET_TARGET_PROPERTIES(${PROJECT_NAME}-datagen PROPERTIES LINK_FLAGS
		"-ltouchstone")
SET_TARGET_PROPERTIES(${PROJECT_NAME}-querygen PROPERTIES LINK_FLAGS
		"-ltouchstone")

set(BIN_DIR ${CMAKE_BINARY_DIR}/src/bin)
set(
    BIN_PROGRAMS
    ${BIN_DIR}/${PROJECT_NAME}-datagen
    ${BIN_DIR}/${PROJECT_NAME}-querygen
)
install(PROGRAMS ${BIN_PROGRAMS} DESTINATION "bin")

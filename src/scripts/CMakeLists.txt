ADD_SUBDIRECTORY(pgsql)

set(SCRIPTS_DIR ${CMAKE_SOURCE_DIR}/src/scripts)
set(
    SCRIPTS_PROGRAMS
    ${SCRIPTS_DIR}/tsdss-generate-report
    ${SCRIPTS_DIR}/tsdss-load-test
    ${SCRIPTS_DIR}/tsdss-post-process
    ${SCRIPTS_DIR}/tsdss-power-test
    ${SCRIPTS_DIR}/tsdss-run-workload
)
install(PROGRAMS ${SCRIPTS_PROGRAMS} DESTINATION "bin")

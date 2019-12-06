set(SCRIPTS_PGSQL_DIR ${CMAKE_SOURCE_DIR}/src/scripts/pgsql)
set(
    SCRIPTS_PGSQL_PROGRAMS
    ${SCRIPTS_PGSQL_DIR}/tsdss-pgsql-create-database
    ${SCRIPTS_PGSQL_DIR}/tsdss-pgsql-create-tables
    ${SCRIPTS_PGSQL_DIR}/tsdss-pgsql-drop-tables
    ${SCRIPTS_PGSQL_DIR}/tsdss-pgsql-load-data
    ${SCRIPTS_PGSQL_DIR}/tsdss-pgsql-start
    ${SCRIPTS_PGSQL_DIR}/tsdss-pgsql-stop
)
install(PROGRAMS ${SCRIPTS_PGSQL_PROGRAMS} DESTINATION "bin")

##############################################################
# MODULE: LEARN C THE HARD WAY
##############################################################
# Define directories
set( PREAD_DIR    ${SRC}/pread         )
set( PREAD_INC    ${PREAD_DIR}/include )
set( PREAD_SRC    ${PREAD_DIR}/src     )

##############################################################
# TESTS: pread
##############################################################
set( EXE_PREAD pread )

add_executable( ${EXE_PREAD}
  ${PREAD_SRC}/pread_main.c
)

target_include_directories( ${EXE_PREAD} PUBLIC
  $<BUILD_INTERFACE:${PREAD_INC}>
)

target_link_libraries( ${EXE_PREAD}
  lcthw
)

# Install executables
install( TARGETS ${EXE_PREAD} RUNTIME DESTINATION ${BIN} )




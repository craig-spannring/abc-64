
#
# Help with initializing GDB
#

message("configure_file(${CMAKE_CURRENT_LIST_DIR}/.gdbinit ${CMAKE_BINARY_DIR}/.gdbinit)")

configure_file(${CMAKE_CURRENT_LIST_DIR}/.gdbinit ${CMAKE_BINARY_DIR}/.gdbinit)



message("PROJECT_SOURCE_DIR is ${PROJECT_SOURCE_DIR}")

enable_testing()

include(GoogleTest)

function(add_test name)
  add_executable(${name} ${name}.cpp)
  target_sources(${name} PRIVATE ${abc_srcs})

  foreach(Def HAVE_TERM_H HAVE_TERMIO_H HAVE_TERMIOS_H HAS_FTIME HAS_GETTIMEOFDAY HAS_MKDIR HAS_RMDIR HAS_RENAME HAS_SELECT HAS_READDIR)
    if ( "${${Def}}" )
      target_compile_definitions(${name} PRIVATE ${Def}=1)
    endif()
  endforeach()
  
  target_compile_options(${name} PRIVATE
    ${CMAKE_C_FLAGS}
    # ${abc_c_only_flags}
    ${abc_c_cxx_flags}
    )
  _add_compiler_def(${name} "${os_defs}")
  target_include_directories(${name}
    PRIVATE
    ${mach_inc_dir}

    ${PROJECT_SOURCE_DIR}/hdrs
    ${PROJECT_SOURCE_DIR}/bhdrs
    ${PROJECT_SOURCE_DIR}/ehdrs
    ${PROJECT_SOURCE_DIR}/ihdrs
    
    ${PROJECT_SOURCE_DIR}/btr
    ${PROJECT_SOURCE_DIR}/bint1
    
    ${CUSTOM_AUTOGENED_FILES}/inc
    )
  target_link_libraries(${name} PUBLIC
    gtest
    gmock
    gtest_main
    m
    # ${CURSES_LIBRARIES}
    -lncurses
    )
  gtest_discover_tests(${name})
endfunction()

message("inc dir ${CUSTOM_AUTOGENED_FILES}/inc")
add_test(uncategorized)
add_test(expr_test01)


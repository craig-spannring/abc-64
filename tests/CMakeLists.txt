
message("PROJECT_SOURCE_DIR is ${PROJECT_SOURCE_DIR}")

enable_testing()

include(GoogleTest)

function(add_test name)
  add_executable(${name} ${name}.cpp)
  target_sources(${name} PRIVATE ${abc_srcs})
  add_dependencies(${name} mach_h_AutoGened file_h_AutoGened)
  target_compile_options(${name} PRIVATE
    ${CMAKE_C_FLAGS}
    # ${abc_c_only_flags}
    ${abc_c_cxx_flags}
    )
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


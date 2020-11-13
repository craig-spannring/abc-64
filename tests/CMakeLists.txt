
message("PROJECT_SOURCE_DIR is ${PROJECT_SOURCE_DIR}")

enable_testing()

include(GoogleTest)

function(add_test name)
  add_executable(${name} ${name}.cpp)
  target_sources(${name} PRIVATE ${abc_srcs})
  target_include_directories(${name}
    PRIVATE
    ${mach_inc_dir}
    ${PROJECT_SOURCE_DIR}/hdrs
    ${PROJECT_SOURCE_DIR}/bhdrs
    ${PROJECT_SOURCE_DIR}/ehdrs
    ${PROJECT_SOURCE_DIR}/ihdrs
    ${PROJECT_SOURCE_DIR}/btr
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


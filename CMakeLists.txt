cmake_minimum_required(VERSION 3.10)

project(abc)

enable_testing()
include(GoogleTest)

find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
  set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
  set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
endif(CCACHE_FOUND)

# find_package(Curses REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_C_STANDARD 90)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

message("in CMakeLists.txt.  CMAKE_C_FLAGS are ${CMAKE_C_FLAGS}")

if (UNIX)
  set(mach_inc_dir ${PROJECT_SOURCE_DIR}/unix)
  set(src_main unix/main.c)
elseif (WIN32)
  set(mach_inc_dir ${PROJECT_SOURCE_DIR}/msdos)  # is this correct?
  set(src_main msdoc/main.c)
endif()

set(CUSTOM_AUTOGENED_FILES ${CMAKE_CURRENT_BINARY_DIR}/custom_autogened_files)
file(MAKE_DIRECTORY ${CUSTOM_AUTOGENED_FILES})
file(MAKE_DIRECTORY ${CUSTOM_AUTOGENED_FILES}/inc)


set(MKMACH ${CMAKE_CURRENT_BINARY_DIR}/mkmach)
add_executable(mkmach mkmach.c)
target_include_directories(mkmach
  PRIVATE ${mach_inc_dir}
  )
target_link_libraries(mkmach
  PRIVATE
  )

add_executable(abc ${src_main})
set_property(TARGET abc PROPERTY C_STANDARD 11)

add_dependencies(abc mach_h_AutoGened file_h_AutoGened)
target_compile_options(abc PRIVATE
  ${CMAKE_C_FLAGS}
  
  -Wall
  -Wint-to-pointer-cast

  
  #-Wno-implicit-int
  
  # -Wout-of-line-declaration
  -Werror=old-style-definition
  # -Wold-style-declaration
  -Wstrict-prototypes
  -Wold-style-definition
  -Wstrict-prototypes
  -Wimplicit-function-declaration
  
  -Wreturn-type
  
  # -Wno-parentheses
  -Wno-deprecated-declarations
  -Wno-unused-value
  
  # -Wno-char-subscripts
  #-Wno-sometimes-unitialized
  
  # -Wno-incompatible-pointer-types
  # -Wno-int-to-pointer-cast
  # -Wint-to-pointer-cast
  # -Werror=int-to-pointer-cast
  )
target_link_libraries(abc
  PRIVATE
  m
  # ${CURSES_LIBRARIES}
  -lncurses
  )
target_include_directories(abc
  PRIVATE
  ${mach_inc_dir}
  hdrs
  bhdrs
  ehdrs
  ihdrs
  btr
  ${CUSTOM_AUTOGENED_FILES}/inc
  ${CURSES_INCLUDE_DIR}  
  )
set(abc_srcs 
  ${CMAKE_CURRENT_LIST_DIR}/bint2/i2gen.c
  ${CMAKE_CURRENT_LIST_DIR}/bint2/i2syn.c
  ${CMAKE_CURRENT_LIST_DIR}/bint2/i2tar.c
  ${CMAKE_CURRENT_LIST_DIR}/bint2/i2uni.c
  ${CMAKE_CURRENT_LIST_DIR}/bint2/i2tes.c
  ${CMAKE_CURRENT_LIST_DIR}/bint2/i2exp.c
  ${CMAKE_CURRENT_LIST_DIR}/bint2/i2dis.c
  ${CMAKE_CURRENT_LIST_DIR}/bint2/i2fix.c
  ${CMAKE_CURRENT_LIST_DIR}/bint2/i2ana.c
  ${CMAKE_CURRENT_LIST_DIR}/bint2/i2cmd.c
  ${CMAKE_CURRENT_LIST_DIR}/bint1/i1nuq.c
  ${CMAKE_CURRENT_LIST_DIR}/bint1/i1nur.c
  ${CMAKE_CURRENT_LIST_DIR}/bint1/i1fun.c
  ${CMAKE_CURRENT_LIST_DIR}/bint1/i1nui.c
  ${CMAKE_CURRENT_LIST_DIR}/bint1/i1nua.c
  ${CMAKE_CURRENT_LIST_DIR}/bint1/i1nug.c
  ${CMAKE_CURRENT_LIST_DIR}/bint1/i1nut.c
  ${CMAKE_CURRENT_LIST_DIR}/bint1/i1com.c
  ${CMAKE_CURRENT_LIST_DIR}/bint1/i1tra.c
  ${CMAKE_CURRENT_LIST_DIR}/bint1/i1num.c
  ${CMAKE_CURRENT_LIST_DIR}/bint1/i1nuc.c
  ${CMAKE_CURRENT_LIST_DIR}/stc/i2tcu.c
  ${CMAKE_CURRENT_LIST_DIR}/stc/i2tca.c
  ${CMAKE_CURRENT_LIST_DIR}/stc/i2tce.c
  ${CMAKE_CURRENT_LIST_DIR}/stc/i2tcp.c
  ${CMAKE_CURRENT_LIST_DIR}/bint3/i3scr.c
  ${CMAKE_CURRENT_LIST_DIR}/bint3/i3sta.c
  ${CMAKE_CURRENT_LIST_DIR}/bint3/i3ini.c
  ${CMAKE_CURRENT_LIST_DIR}/bint3/i3typ.c
  ${CMAKE_CURRENT_LIST_DIR}/bint3/i3fpr.c
  ${CMAKE_CURRENT_LIST_DIR}/bint3/i3cen.c
  ${CMAKE_CURRENT_LIST_DIR}/bint3/i3com.c
  ${CMAKE_CURRENT_LIST_DIR}/bint3/i3fil.c
  ${CMAKE_CURRENT_LIST_DIR}/bint3/i3loc.c
  ${CMAKE_CURRENT_LIST_DIR}/bint3/i3int.c
  ${CMAKE_CURRENT_LIST_DIR}/bint3/i3in2.c
  ${CMAKE_CURRENT_LIST_DIR}/bint3/i3imm.c
  ${CMAKE_CURRENT_LIST_DIR}/bint3/i3gfx.c
  ${CMAKE_CURRENT_LIST_DIR}/bint3/i3sou.c
  ${CMAKE_CURRENT_LIST_DIR}/bint3/i3bws.c
  ${CMAKE_CURRENT_LIST_DIR}/bint3/i3env.c
  ${CMAKE_CURRENT_LIST_DIR}/bint3/i3err.c
  ${CMAKE_CURRENT_LIST_DIR}/bio/i4out.c
  ${CMAKE_CURRENT_LIST_DIR}/bio/i4inp.c
  ${CMAKE_CURRENT_LIST_DIR}/bio/i4rec.c
  ${CMAKE_CURRENT_LIST_DIR}/bio/i4lis.c
  ${CMAKE_CURRENT_LIST_DIR}/bio/i4bio.c
  ${CMAKE_CURRENT_LIST_DIR}/bio/i4grp.c
  ${CMAKE_CURRENT_LIST_DIR}/bio/i4fil.c
  ${CMAKE_CURRENT_LIST_DIR}/bio/i4pack.c
  ${CMAKE_CURRENT_LIST_DIR}/unix/edit.c
  ${CMAKE_CURRENT_LIST_DIR}/unix/dir.c
  ${CMAKE_CURRENT_LIST_DIR}/unix/trm.c
  ${CMAKE_CURRENT_LIST_DIR}/unix/usage.c
  ${CMAKE_CURRENT_LIST_DIR}/unix/os.c
  ${CMAKE_CURRENT_LIST_DIR}/unix/sig.c
  ${CMAKE_CURRENT_LIST_DIR}/unix/keys.c
  ${CMAKE_CURRENT_LIST_DIR}/unix/file.c
  ${CMAKE_CURRENT_LIST_DIR}/b/b1mess.c
  ${CMAKE_CURRENT_LIST_DIR}/b/b1file.c
  ${CMAKE_CURRENT_LIST_DIR}/b/getopt.c
  ${CMAKE_CURRENT_LIST_DIR}/b/b1outp.c
  ${CMAKE_CURRENT_LIST_DIR}/b/b1memo.c
  ${CMAKE_CURRENT_LIST_DIR}/b/b1grab.c
  ${CMAKE_CURRENT_LIST_DIR}/bed/e1deco.c
  ${CMAKE_CURRENT_LIST_DIR}/bed/e1que2.c
  ${CMAKE_CURRENT_LIST_DIR}/bed/e1edoc.c
  ${CMAKE_CURRENT_LIST_DIR}/bed/e1inse.c
  ${CMAKE_CURRENT_LIST_DIR}/bed/e1line.c
  ${CMAKE_CURRENT_LIST_DIR}/bed/e1erro.c
  ${CMAKE_CURRENT_LIST_DIR}/bed/e1getc.c
  ${CMAKE_CURRENT_LIST_DIR}/bed/e1help.c
  ${CMAKE_CURRENT_LIST_DIR}/bed/e1cell.c
  ${CMAKE_CURRENT_LIST_DIR}/bed/e1code.c
  ${CMAKE_CURRENT_LIST_DIR}/bed/e1node.c
  ${CMAKE_CURRENT_LIST_DIR}/bed/e1goto.c
  ${CMAKE_CURRENT_LIST_DIR}/bed/e1tabl.c
  ${CMAKE_CURRENT_LIST_DIR}/bed/e1save.c
  ${CMAKE_CURRENT_LIST_DIR}/bed/e1scrn.c
  ${CMAKE_CURRENT_LIST_DIR}/bed/e1que1.c
  ${CMAKE_CURRENT_LIST_DIR}/bed/e1spos.c
  ${CMAKE_CURRENT_LIST_DIR}/bed/e1gram.c
  ${CMAKE_CURRENT_LIST_DIR}/bed/e1comm.c
  ${CMAKE_CURRENT_LIST_DIR}/bed/e1ins2.c
  ${CMAKE_CURRENT_LIST_DIR}/bed/e1eval.c
  ${CMAKE_CURRENT_LIST_DIR}/bed/e1lexi.c
  ${CMAKE_CURRENT_LIST_DIR}/bed/e1supr.c
  ${CMAKE_CURRENT_LIST_DIR}/bed/e1move.c
  ${CMAKE_CURRENT_LIST_DIR}/bed/e1outp.c
  ${CMAKE_CURRENT_LIST_DIR}/bed/e1sugg.c
  ${CMAKE_CURRENT_LIST_DIR}/bed/e1edit.c
  ${CMAKE_CURRENT_LIST_DIR}/bed/e1wide.c
  ${CMAKE_CURRENT_LIST_DIR}/btr/e1etex.c
  ${CMAKE_CURRENT_LIST_DIR}/btr/i1tex.c
  ${CMAKE_CURRENT_LIST_DIR}/btr/i1lta.c
  ${CMAKE_CURRENT_LIST_DIR}/btr/i1tlt.c
  ${CMAKE_CURRENT_LIST_DIR}/btr/i1btr.c
  ${CMAKE_CURRENT_LIST_DIR}/btr/i1obj.c
)
target_sources(abc PRIVATE ${abc_srcs})



add_custom_command(OUTPUT ${CUSTOM_AUTOGENED_FILES}/inc/file.h
  COMMAND ${CMAKE_CURRENT_LIST_DIR}/mk_file_h > ${CUSTOM_AUTOGENED_FILES}/inc/file.h.tmp_
  COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CUSTOM_AUTOGENED_FILES}/inc/file.h.tmp_ ${CUSTOM_AUTOGENED_FILES}/inc/file.h

  DEPENDS ${CMAKE_CURRENT_LIST_DIR}/mk_file_h
  )
add_custom_target(file_h_AutoGened
  DEPENDS ${CUSTOM_AUTOGENED_FILES}/inc/file.h)

add_custom_command(OUTPUT ${CUSTOM_AUTOGENED_FILES}/inc/mach.h
  COMMAND date > /tmp/making_mach_h.out
  COMMAND ${MKMACH} > ${CUSTOM_AUTOGENED_FILES}/inc/mach.h.tmp_
  COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CUSTOM_AUTOGENED_FILES}/inc/mach.h.tmp_ ${CUSTOM_AUTOGENED_FILES}/inc/mach.h
  DEPENDS mkmach
  DEPENDS ${CMAKE_CURRENT_LIST_FILE}
  )
add_custom_target(mach_h_AutoGened
  DEPENDS ${CUSTOM_AUTOGENED_FILES}/inc/mach.h)


set(GOOGLE_TEST_INSTALLATION_SYMLINK ${CMAKE_CURRENT_LIST_DIR}/googletest-release-1.8.1)
if(EXISTS ${GOOGLE_TEST_INSTALLATION_SYMLINK})
  add_subdirectory(${GOOGLE_TEST_INSTALLATION_SYMLINK}/.)
  add_subdirectory(tests)
endif()

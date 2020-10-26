cmake_minimum_required(VERSION 3.10)


find_package(Curses REQUIRED)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (UNIX)
  set(mach_inc_dir unix)
  set(src_main unix/main.c)
elseif (WIN32)
  set(mach_inc_dir msdos)  # is this correct?
  set(src_main msdoc/main.c)
endif()

add_executable(mkmach mkmach.c)
target_include_directories(mkmach
  PRIVATE ${mach_inc_dir}
  )
target_link_libraries(mkmach
  PRIVATE
  )

#cc -Wno-implicit-int -Wno-return-type    -I../bhdrs -I../ehdrs -I../ihdrs -I../unix   -c -o main.o main.c
add_executable(abc ${src_main})
target_compile_options(abc PRIVATE -Wno-implicit-int -Wno-return-type)
target_link_libraries(abc
  PRIVATE
  m
  ${CURSES_LIBRARIES}
  )
target_include_directories(abc
  PRIVATE
  ${mach_inc_dir}
  bhdrs
  ehdrs
  ihdrs
  btr
  ${CURSES_INCLUDE_DIR}  
  )
target_sources(abc PRIVATE
  bint2/i2gen.c
  bint2/i2syn.c
  bint2/i2tar.c
  bint2/i2uni.c
  bint2/i2tes.c
  bint2/i2exp.c
  bint2/i2dis.c
  bint2/i2fix.c
  bint2/i2ana.c
  bint2/i2cmd.c
  bint1/i1nuq.c
  bint1/i1nur.c
  bint1/i1fun.c
  bint1/i1nui.c
  bint1/i1nua.c
  bint1/i1nug.c
  bint1/i1nut.c
  bint1/i1com.c
  bint1/i1tra.c
  bint1/i1num.c
  bint1/i1nuc.c
  stc/i2tcu.c
  stc/i2tca.c
  stc/i2tce.c
  stc/i2tcp.c
  bint3/i3scr.c
  bint3/i3sta.c
  bint3/i3ini.c
  bint3/i3typ.c
  bint3/i3fpr.c
  bint3/i3cen.c
  bint3/i3com.c
  bint3/i3fil.c
  bint3/i3loc.c
  bint3/i3int.c
  bint3/i3in2.c
  bint3/i3imm.c
  bint3/i3gfx.c
  bint3/i3sou.c
  bint3/i3bws.c
  bint3/i3env.c
  bint3/i3err.c
  bio/i4out.c
  bio/i4inp.c
  bio/i4rec.c
  bio/i4lis.c
  bio/i4bio.c
  bio/i4grp.c
  bio/i4fil.c
  bio/i4pack.c
  unix/edit.c
  unix/dir.c
  unix/trm.c
  unix/main.c
  unix/usage.c
  unix/os.c
  unix/sig.c
  unix/keys.c
  unix/file.c
  b/b1mess.c
  b/b1file.c
  b/getopt.c
  b/b1outp.c
  b/b1memo.c
  b/b1grab.c
  bed/e1deco.c
  bed/e1que2.c
  bed/e1edoc.c
  bed/e1inse.c
  bed/e1line.c
  bed/e1erro.c
  bed/e1getc.c
  bed/e1help.c
  bed/e1cell.c
  bed/e1code.c
  bed/e1node.c
  bed/e1goto.c
  bed/e1tabl.c
  bed/e1save.c
  bed/e1scrn.c
  bed/e1que1.c
  bed/e1spos.c
  bed/e1gram.c
  bed/e1comm.c
  bed/e1ins2.c
  bed/e1eval.c
  bed/e1lexi.c
  bed/e1supr.c
  bed/e1move.c
  bed/e1outp.c
  bed/e1sugg.c
  bed/e1edit.c
  bed/e1wide.c
  btr/e1etex.c
  btr/i1tex.c
  btr/i1lta.c
  btr/i1tlt.c
  btr/i1btr.c
  btr/i1obj.c
)



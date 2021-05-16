#
# The original code had 4 auto-gen'd source files for Unix.
#   1) unix/comp.h
#   2) unix/os.h    (finished)
#   3) file.h       (finished)
#   4) mach.h       (finished)
# 

include(CheckTypeSize)
include(CheckIncludeFile)
include(CheckSymbolExists)

set(CMAKE_REQUIRED_DEFINITIONS "")
list(APPEND CMAKE_REQUIRED_DEFINITIONS "-D_POSIX_SOURCE=200809L")
list(APPEND CMAKE_REQUIRED_DEFINITIONS "-D_POSIX_C_SOURCE=200809L")
list(APPEND CMAKE_REQUIRED_DEFINITIONS -D_DEFAULT_SOURCE=1)

  
check_include_file(term.h    HAVE_TERM_H)
check_include_file(termio.h  HAVE_TERMIO_H)
check_include_file(termios.h HAVE_TERMIOS_H)

check_symbol_exists(ftime        sys/timeb.h   	   	  HAS_FTIME)
check_symbol_exists(gettimeofday sys/time.h    	   	  HAS_GETTIMEOFDAY)
check_symbol_exists(mkdir        "sys/stat.h;sys/types.h" HAS_MKDIR)
check_symbol_exists(rmdir        unistd.h      	   	  HAS_RMDIR)
check_symbol_exists(rename       stdio.h       	   	  HAS_RENAME)
check_symbol_exists(select       sys/select.h  	   	  HAS_SELECT)
check_symbol_exists(readdir      dirent.h          	  HAS_READDIR)

set(HAS_READDIR 1) # cmake isn't picking up on this function.  Not sure why

function(os_specific_defs os_defs)
  set(defs "")
  foreach(Def HAVE_TERM_H HAVE_TERMIO_H HAVE_TERMIOS_H HAS_FTIME HAS_GETTIMEOFDAY HAS_MKDIR HAS_RMDIR HAS_RENAME HAS_SELECT HAS_READDIR)
    if ( "${${Def}}" )
      list(APPEND defs "${Def}=1")
    endif()
  endforeach()

  if(HAVE_TERM_H OR HAVE_TERMIO_H OR HAVE_TERMIOS_H)
    list(APPEND defs "TERM=1")
    list(APPEND defs "TERMIOS=1")
  endif()

  foreach(Def "${CMAKE_REQUIRED_DEFINITIONS}")
    list(APPEND defs "${Def}")
  endforeach()

  set(${os_defs} ${defs} PARENT_SCOPE)
endfunction()

function(_add_compiler_def target defs)
  foreach(Def ${defs})
    target_compile_definitions(${target} PRIVATE ${Def})
  endforeach()
endfunction()

function(_calc_abcbase b)
  check_type_size(int size_of_int)
  check_type_size(long size_of_long)

  math(EXPR tmp "1<<(${size_of_long}*4)")
  string(LENGTH "${tmp}" tmplen)
  string(SUBSTRING "10000000000000000000000000000000000000"  0  ${tmplen} abc1)

  math(EXPR tmp "(1<<(${size_of_int}*8)) / 2")
  string(LENGTH "${tmp}" tmplen)
  string(SUBSTRING "10000000000000000000000000000000000000"  0  ${tmplen} abc2)

  if(${abc1} LESS ${abc2})
    set(${b} ${abc1} PARENT_SCOPE)
  else()
    set(${b} ${abc2} PARENT_SCOPE)
  endif()
endfunction()

function(make_mach_h)
  check_type_size(int    size_of_int)
  check_type_size(long   size_of_long)
  check_type_size(double size_of_double)

  math(EXPR bits_in_long   "${size_of_long}*8")
  math(EXPR bits_in_int    "${size_of_int}*8")
  math(EXPR bits_in_double "${size_of_double}*8")

  math(EXPR max_long   "1<<(${bits_in_long}-1)")
  math(EXPR max_int    "1<<(${bits_in_int}-1)")

  math(EXPR ABC_LONGBITS      "${size_of_long}*8-1")
  math(EXPR ABC_2to_LONGBITS  "1<<${ABC_LONGBITS}")
  set(ABC_2to_LONGBITS "${ABC_2to_LONGBITS}.0")
  
  set(ABC_DBL_EXP_BITS 53) # TODO pragmatically find instead of hard-coding

  math(EXPR ABC_BIG "(1<<${ABC_DBL_EXP_BITS})-1")
  string(LENGTH "${ABC_BIG}" ABC_MAXNUMDIG)
  set(ABC_BIG "${ABC_BIG}.0")

  _calc_abcbase(ABC_ABCBASE)
  string(LENGTH "${ABC_ABCBASE}" tmp)
  math(EXPR ABC_tenlogBASE "${tmp}-1")
  math(EXPR tmp "2*${max_int}+1")

  # TODO this isn't exactly what the orginal code did.
  if(${bits_in_long} EQUAL 64)
    set(ABC_digit_type "int")
  else()
    set(ABC_digit_type "short")
  endif()
  
  configure_file(
    ${CMAKE_SOURCE_DIR}/unix/mach.h.in
    ${CUSTOM_AUTOGENED_FILES}/inc/mach.h
    )
endfunction()



#
# The original code had 4 auto-gen'd source files for Unix.
#   1) unix/comp.h
#   2) unix/os.h
#   3) file.h
#   4) mach.h
# 

include(CheckTypeSize)

function(os_specific_defs defs)
  set(${defs} MySpecialDef PARENT_SCOPE)
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

  #if (2*intpower + 1 <= longpower) {
  #  printf("typedef int digit; /*here*/\n");
  #  maxdigit= maxint;
  #}
  #else {
  #  printf("typedef short digit;\n");
  #  maxdigit= maxshort;
  #}
  math(EXPR tmp "2*${max_int}+1")

  # TODO this isn't exactly what the orginal code did.
  if(${bits_in_long} EQUAL 64)
    set(ABC_digit_type "int")
  else()
    set(ABC_digit_type "short")
  endif()
  
  message("long:          ${size_of_long}")
  message("BIG:           ${ABC_BIG}")
  message("ABC_ABCBASE:   ${ABC_ABCBASE}")
  message("ABC_MAXNUMDIG: ${ABC_MAXNUMDIG}")
  
  configure_file(
    ${CMAKE_SOURCE_DIR}/unix/mach.h.in
    ${CUSTOM_AUTOGENED_FILES}/inc/mach.h
    )


endfunction()

function(create_comp_h)
  check_include_file(termio.h  HAVE_TERMIO_H)
  check_include_file(termios.h HAVE_TERMIOS_H)  

  configure_file(
    ${CMAKE_SOURCE_DIR}/unix/comp.h.in
    ${CUSTOM_AUTOGENED_FILES}/inc/comp.h
    )

  message("CUSTOM_AUTOGENED_FILES ${CUSTOM_AUTOGENED_FILES}")
endfunction()

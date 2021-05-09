

function(os_specific_defs)
  set(MyFoo "myfoo")
  check_include_file(termio.h  HAVE_TERMIO_H)
  check_include_file(termios.h HAVE_TERMIOS_H)
  message("leaving")
endfunction()

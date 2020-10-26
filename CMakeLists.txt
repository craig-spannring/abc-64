
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (UNIX)
  set(mach_inc_dir unix)
elseif (WIN32)
  set(mach_inc_dir msdos)  # is this correct?
endif()

add_executable(mkmach mkmach.c)
target_include_directories(mkmach
  PRIVATE ${mach_inc_dir}
  )
target_link_libraries(mkmach
  PRIVATE
  )

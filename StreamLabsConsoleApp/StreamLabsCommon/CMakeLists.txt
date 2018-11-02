cmake_minimum_required(VERSION 3.12.2)

project(StreamLabsCommon)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release"
    CACHE STRING "Configuration types" FORCE)

add_executable(StreamLabsCommon
  include/Constants.h
  include/DummyClass.h
  include/Request.h
  include/Response.h
  include/StreamLabsExeption.h
  Request.cpp
  Response.cpp
)
# Preprocessor definitions
target_compile_definitions(StreamLabsCommon PRIVATE
  $<$<CONFIG:Debug>:_UNICODE;_DEBUG;_CONSOLE>
  $<$<CONFIG:Release>:_UNICODE;NDEBUG;_CONSOLE>
)

# SDL check
target_compile_options(StreamLabsCommon PRIVATE
  "$<$<CONFIG:Debug>:/sdl>"
  "$<$<CONFIG:Release>:/sdl>"
)

# Minimal rebuild
if (MSVC)
  target_compile_options(StreamLabsCommon PRIVATE
    "$<$<CONFIG:Debug>:/Gm->"
    "$<$<CONFIG:Release>:/Gm->"
  )
endif ()

# Precompiled header files
if (MSVC)
  target_compile_options(StreamLabsCommon PRIVATE
    "$<$<CONFIG:Debug>:/Yu"pch.h">"
    "$<$<CONFIG:Release>:/Yu"pch.h">"
  )
endif ()

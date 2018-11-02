cmake_minimum_required(VERSION 3.12.2)

project(StreamLabsServer)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release"
    CACHE STRING "Configuration types" FORCE)

add_executable(StreamLabsServer
  DummyClassServerImpl.cpp
  DummyClassServerImpl.h
  StreamLabsServer.cpp
  StreamLabsServer.h
)
# Preprocessor definitions
target_compile_definitions(StreamLabsServer PRIVATE
  $<$<CONFIG:Debug>:_UNICODE;_DEBUG;_CONSOLE>
  $<$<CONFIG:Release>:_UNICODE;NDEBUG;_CONSOLE>
)

# SDL check
target_compile_options(StreamLabsServer PRIVATE
  "$<$<CONFIG:Debug>:/sdl>"
  "$<$<CONFIG:Release>:/sdl>"
)

# Minimal rebuild
if (MSVC)
  target_compile_options(StreamLabsServer PRIVATE
    "$<$<CONFIG:Debug>:/Gm->"
    "$<$<CONFIG:Release>:/Gm->"
  )
endif ()

# Precompiled header files
if (MSVC)
  target_compile_options(StreamLabsServer PRIVATE
    "$<$<CONFIG:Debug>:/Yu"pch.h">"
    "$<$<CONFIG:Release>:/Yu"pch.h">"
  )
endif ()

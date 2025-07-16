### lua
add_library(lua
  lua/lapi.c
  lua/lauxlib.c
  lua/lbaselib.c
  lua/lcode.c
  lua/lcorolib.c
  lua/lctype.c
  lua/ldblib.c
  lua/ldebug.c
  lua/ldo.c
  lua/ldump.c
  lua/lfunc.c
  lua/lgc.c
  lua/linit.c
  lua/liolib.c
  lua/llex.c
  lua/lmathlib.c
  lua/lmem.c
  lua/loadlib.c
  lua/lobject.c
  lua/lopcodes.c
  lua/loslib.c
  lua/lparser.c
  lua/lstate.c
  lua/lstring.c
  lua/lstrlib.c
  lua/ltable.c
  lua/ltablib.c
  lua/ltests.c
  lua/ltm.c
  lua/lua.c
  lua/lundump.c
  lua/lutf8lib.c
  lua/lvm.c
  lua/lzio.c
)
add_library(lua::lua ALIAS lua)

if (WIN32)
  target_compile_definitions(lua PRIVATE LUA_USE_WINDOWS)
endif()

target_include_directories(lua PUBLIC lua)
if (UNIX)
  target_compile_definitions(lua PRIVATE LUA_USE_LINUX)
  target_link_libraries(lua PRIVATE dl)
endif()

### sol2
set(SOL2_LUA_VERSION "5.4.4" CACHE STRING "The version of Lua used")
# we build Lua manually
set(SOL2_BUILD_LUA FALSE CACHE BOOL "Always build Lua, do not search for it in the system")
add_subdirectory(sol2)


### ocgcore
include_directories(
    ygopro/ocgcore
    lua
)
file(GLOB OCGCORE_SOURCES
  "ygopro/ocgcore/*.c"
  "ygopro/ocgcore/*.cpp"
)

add_library(ocgcore STATIC ${OCGCORE_SOURCES})


target_link_libraries(ocgcore
    PRIVATE
    lua
)

add_library(ocgcore::ocgcore ALIAS ocgcore)


### irrlicht

include_directories(
    irrlicht/include
    irrlicht/source/Irrlicht
    irrlicht/source/Irrlicht/zlib
    irrlicht/source/Irrlicht/bzip2
    irrlicht/source/Irrlicht/libpng
    irrlicht/source/Irrlicht/jpeglib
)
file(GLOB IRRLICHT_SOURCES
  irrlicht/source/Irrlicht/*.cpp
  irrlicht/source/Irrlicht/zlib/*.c
  irrlicht/source/Irrlicht/bzip2/blocksort.c
  irrlicht/source/Irrlicht/bzip2/bzlib.c
  irrlicht/source/Irrlicht/bzip2/crctable.c
  irrlicht/source/Irrlicht/bzip2/huffman.c
  irrlicht/source/Irrlicht/bzip2/randtable.c
  irrlicht/source/Irrlicht/bzip2/compress.c
  irrlicht/source/Irrlicht/bzip2/decompress.c
  irrlicht/source/Irrlicht/bzip2/bzcompress.c
  irrlicht/source/Irrlicht/libpng/*.c
  irrlicht/source/Irrlicht/jpeglib/*.c
)

add_library(irrlicht STATIC ${IRRLICHT_SOURCES})
add_library(irrlicht::irrlicht ALIAS irrlicht)


### ygopro

include_directories(
    ygopro/gframe
    ygopro/gframe/lzma
    ygopro/gframe/spmemvfs
)

file(GLOB YGO_SOURCES
  "ygopro/gframe/*.cpp"
  "ygopro/gframe/lzma/*.cpp"
  "ygopro/gframe/spmemvfs/*.cpp"
  "ygopro/gframe/*.c"
  "ygopro/gframe/lzma/*.c"
  "ygopro/gframe/spmemvfs/*.c"
)


find_package(Freetype REQUIRED)

add_executable(ygopro
  ${YGO_SOURCES}
)

target_include_directories(ygopro PRIVATE ${FREETYPE_INCLUDE_DIRS})
target_link_libraries(ygopro PRIVATE ${FREETYPE_LIBRARIES} irrlicht ocgcore)
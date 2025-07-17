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
    irrlicht/source/Irrlicht/libpng
    irrlicht/source/Irrlicht/jpeglib
)


file(GLOB IRRLICHT_SOURCES
        irrlicht/include/*.h
        irrlicht/source/Irrlicht/*.cpp
        irrlicht/source/Irrlicht/zlib/zlib.h
        irrlicht/source/Irrlicht/zlib/adler32.c
        irrlicht/source/Irrlicht/zlib/compress.c
        irrlicht/source/Irrlicht/zlib/crc32.h
        irrlicht/source/Irrlicht/zlib/crc32.c
        irrlicht/source/Irrlicht/zlib/deflate.h
        irrlicht/source/Irrlicht/zlib/deflate.c
        irrlicht/source/Irrlicht/zlib/inffast.h
        irrlicht/source/Irrlicht/zlib/inffast.c
        irrlicht/source/Irrlicht/zlib/inflate.h
        irrlicht/source/Irrlicht/zlib/inflate.c
        irrlicht/source/Irrlicht/zlib/inftrees.h
        irrlicht/source/Irrlicht/zlib/inftrees.c
        irrlicht/source/Irrlicht/zlib/trees.h
        irrlicht/source/Irrlicht/zlib/trees.c
        irrlicht/source/Irrlicht/zlib/uncompr.c
        irrlicht/source/Irrlicht/zlib/zutil.h
        irrlicht/source/Irrlicht/zlib/zutil.c
        irrlicht/source/Irrlicht/jpeglib/jaricom.c
        irrlicht/source/Irrlicht/jpeglib/jcapimin.c
        irrlicht/source/Irrlicht/jpeglib/jcapistd.c
        irrlicht/source/Irrlicht/jpeglib/jcarith.c
        irrlicht/source/Irrlicht/jpeglib/jccoefct.c
        irrlicht/source/Irrlicht/jpeglib/jccolor.c
        irrlicht/source/Irrlicht/jpeglib/jcdctmgr.c
        irrlicht/source/Irrlicht/jpeglib/jchuff.c
        irrlicht/source/Irrlicht/jpeglib/jcinit.c
        irrlicht/source/Irrlicht/jpeglib/jcmainct.c
        irrlicht/source/Irrlicht/jpeglib/jcmarker.c
        irrlicht/source/Irrlicht/jpeglib/jcmaster.c
        irrlicht/source/Irrlicht/jpeglib/jcomapi.c
        irrlicht/source/Irrlicht/jpeglib/jcparam.c
        irrlicht/source/Irrlicht/jpeglib/jcprepct.c
        irrlicht/source/Irrlicht/jpeglib/jcsample.c
        irrlicht/source/Irrlicht/jpeglib/jctrans.c
        irrlicht/source/Irrlicht/jpeglib/jdapimin.c
        irrlicht/source/Irrlicht/jpeglib/jdapistd.c
        irrlicht/source/Irrlicht/jpeglib/jdarith.c
        irrlicht/source/Irrlicht/jpeglib/jdatadst.c
        irrlicht/source/Irrlicht/jpeglib/jdatasrc.c
        irrlicht/source/Irrlicht/jpeglib/jdcoefct.c
        irrlicht/source/Irrlicht/jpeglib/jdcolor.c
        irrlicht/source/Irrlicht/jpeglib/jddctmgr.c
        irrlicht/source/Irrlicht/jpeglib/jdhuff.c
        irrlicht/source/Irrlicht/jpeglib/jdinput.c
        irrlicht/source/Irrlicht/jpeglib/jdmainct.c
        irrlicht/source/Irrlicht/jpeglib/jdmarker.c
        irrlicht/source/Irrlicht/jpeglib/jdmaster.c
        irrlicht/source/Irrlicht/jpeglib/jdmerge.c
        irrlicht/source/Irrlicht/jpeglib/jdpostct.c
        irrlicht/source/Irrlicht/jpeglib/jdsample.c
        irrlicht/source/Irrlicht/jpeglib/jdtrans.c
        irrlicht/source/Irrlicht/jpeglib/jerror.c
        irrlicht/source/Irrlicht/jpeglib/jfdctflt.c
        irrlicht/source/Irrlicht/jpeglib/jfdctfst.c
        irrlicht/source/Irrlicht/jpeglib/jfdctint.c
        irrlicht/source/Irrlicht/jpeglib/jidctflt.c
        irrlicht/source/Irrlicht/jpeglib/jidctfst.c
        irrlicht/source/Irrlicht/jpeglib/jidctint.c
        irrlicht/source/Irrlicht/jpeglib/jmemmgr.c
        irrlicht/source/Irrlicht/jpeglib/jmemnobs.c
        irrlicht/source/Irrlicht/jpeglib/jquant1.c
        irrlicht/source/Irrlicht/jpeglib/jquant2.c
        irrlicht/source/Irrlicht/jpeglib/jutils.c
        irrlicht/source/Irrlicht/libpng/png.c
        irrlicht/source/Irrlicht/libpng/pngerror.c
        irrlicht/source/Irrlicht/libpng/pngget.c
        irrlicht/source/Irrlicht/libpng/pngmem.c
        irrlicht/source/Irrlicht/libpng/pngpread.c
        irrlicht/source/Irrlicht/libpng/pngread.c
        irrlicht/source/Irrlicht/libpng/pngrio.c
        irrlicht/source/Irrlicht/libpng/pngrtran.c
        irrlicht/source/Irrlicht/libpng/pngrutil.c
        irrlicht/source/Irrlicht/libpng/pngset.c
        irrlicht/source/Irrlicht/libpng/pngtrans.c
        irrlicht/source/Irrlicht/libpng/pngwio.c
        irrlicht/source/Irrlicht/libpng/pngwrite.c
        irrlicht/source/Irrlicht/libpng/pngwtran.c
        irrlicht/source/Irrlicht/libpng/pngwutil.c
        irrlicht/source/Irrlicht/libpng/intel/intel_init.c
        irrlicht/source/Irrlicht/libpng/intel/filter_sse2_intrinsics.c
)

add_library(irrlicht STATIC ${IRRLICHT_SOURCES})
add_library(irrlicht::irrlicht ALIAS irrlicht)


target_compile_definitions(irrlicht PRIVATE 
        _IRR_STATIC_LIB_
        NO_IRR_USE_NON_SYSTEM_BZLIB_
        NO_IRR_COMPILE_WITH_BZIP2_
        NO_IRR_COMPILE_WITH_LZMA_
        NO_IRR_COMPILE_WITH_CONSOLE_DEVICE_
        NO_IRR_COMPILE_WITH_DIRECT3D_8_
        NO_IRR_COMPILE_WITH_DIRECTINPUT_JOYSTICK_
        NO_IRR_COMPILE_WITH_JOYSTICK_EVENTS_
        NO_IRR_COMPILE_WITH_SOFTWARE_
        NO_IRR_COMPILE_WITH_BURNINGSVIDEO_
        NO_IRR_COMPILE_WITH_IRR_SCENE_LOADER_
        NO_IRR_COMPILE_WITH_SKINNED_MESH_SUPPORT_
        NO_IRR_COMPILE_WITH_IRR_MESH_LOADER_
        NO_IRR_COMPILE_WITH_HALFLIFE_LOADER_
        NO_IRR_COMPILE_WITH_MD2_LOADER_
        NO_IRR_COMPILE_WITH_MD3_LOADER_
        NO_IRR_COMPILE_WITH_3DS_LOADER_
        NO_IRR_COMPILE_WITH_COLLADA_LOADER_
        NO_IRR_COMPILE_WITH_CSM_LOADER_
        NO_IRR_COMPILE_WITH_BSP_LOADER_
        NO_IRR_COMPILE_WITH_DMF_LOADER_
        NO_IRR_COMPILE_WITH_LMTS_LOADER_
        NO_IRR_COMPILE_WITH_MY3D_LOADER_
        NO_IRR_COMPILE_WITH_OBJ_LOADER_
        NO_IRR_COMPILE_WITH_OCT_LOADER_
        NO_IRR_COMPILE_WITH_LWO_LOADER_
        NO_IRR_COMPILE_WITH_STL_LOADER_
        NO_IRR_COMPILE_WITH_PLY_LOADER_
        NO_IRR_COMPILE_WITH_SMF_LOADER_
        NO_IRR_COMPILE_WITH_IRR_WRITER_
        NO_IRR_COMPILE_WITH_COLLADA_WRITER_
        NO_IRR_COMPILE_WITH_STL_WRITER_
        NO_IRR_COMPILE_WITH_OBJ_WRITER_
        NO_IRR_COMPILE_WITH_PLY_WRITER_
        NO_IRR_COMPILE_WITH_PCX_LOADER_
        NO_IRR_COMPILE_WITH_PPM_LOADER_
        NO_IRR_COMPILE_WITH_PSD_LOADER_
        NO_IRR_COMPILE_WITH_TGA_LOADER_
        NO_IRR_COMPILE_WITH_WAL_LOADER_
        NO_IRR_COMPILE_WITH_LMP_LOADER_
        NO_IRR_COMPILE_WITH_RGB_LOADER_
        NO_IRR_COMPILE_WITH_PCX_WRITER_
        NO_IRR_COMPILE_WITH_PPM_WRITER_
        NO_IRR_COMPILE_WITH_PSD_WRITER_
        NO_IRR_COMPILE_WITH_TGA_WRITER_
        NO__IRR_COMPILE_WITH_PAK_ARCHIVE_LOADER_
        NO__IRR_COMPILE_WITH_NPK_ARCHIVE_LOADER_
        NO__IRR_COMPILE_WITH_WAD_ARCHIVE_LOADER_
        NO_IRR_COMPILE_WITH_ZIP_ENCRYPTION_
        PNG_INTEL_SSE
        PNG_ARM_NEON_OPT=0
        PNG_ARM_NEON_IMPLEMENTATION=0
)


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
find_package(X11 REQUIRED) # REQUIRED 表示如果找不到 X11 则报错
find_package(OpenGL REQUIRED)

find_package(SQLite3 REQUIRED QUIET)


find_library(LIBEVENT_LIB NAMES event HINTS /usr/lib /usr/local/lib)
find_library(LIBEVENT_PTHREAD_LIB NAMES event_pthreads HINTS /usr/lib /usr/local/lib)
find_path(LIBEVENT_INCLUDE_DIR event2/event.h HINTS /usr/include /usr/local/include)


add_executable(ygopro
  ${YGO_SOURCES}
)

target_include_directories(ygopro PRIVATE ${FREETYPE_INCLUDE_DIRS} ${X11_LIBRARIES})
target_link_libraries(ygopro  
${FREETYPE_LIBRARIES} ${X11_LIBRARIES} ${SQLite3_LIBRARIES} ${OPENGL_LIBRARIES} 
${LIBEVENT_LIB} ${LIBEVENT_PTHREAD_LIB} OpenGL::GL
irrlicht X11 Xxf86vm  ocgcore)

# 定义源目录 (resources 文件夹)
set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/res")
 
# 定义目标目录 (build/third 文件夹)
set(TARGET_DIR "${CMAKE_BINARY_DIR}/third_party")
 
# 把 resources 文件夹的内容递归复制到 build/third
file(COPY ${SOURCE_DIR}/ DESTINATION ${TARGET_DIR})
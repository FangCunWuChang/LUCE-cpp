cmake_minimum_required (VERSION 3.15)
project (LUCE-cpp VERSION 0.0.1 LANGUAGES CXX C ASM)

if (NOT DEFINED CMAKE_BUILD_TYPE)
    set (CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build." FORCE)
endif (NOT DEFINED CMAKE_BUILD_TYPE)

set (CMAKE_CXX_STANDARD 20)#使用C++20
set (CMAKE_CXX_EXTENSIONS OFF)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_C_STANDARD 17)#使用C17
set (CMAKE_C_EXTENSIONS OFF)
set (CMAKE_C_STANDARD_REQUIRED ON)

set (CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")#MSVC下使用/MD和/MDd

if (NOT DEFINED JUCE_DISPLAY_SPLASH_SCREEN)
    set (JUCE_DISPLAY_SPLASH_SCREEN OFF)
endif (NOT DEFINED JUCE_DISPLAY_SPLASH_SCREEN)
if (NOT DEFINED JUCE_USE_DARK_SPLASH_SCREEN)
    set (JUCE_USE_DARK_SPLASH_SCREEN ON)
endif (NOT DEFINED JUCE_USE_DARK_SPLASH_SCREEN)
if (NOT DEFINED JucePlugin_Build_VST)
    set (JucePlugin_Build_VST OFF)
endif (NOT DEFINED JucePlugin_Build_VST)
if (NOT DEFINED JucePlugin_Build_VST3)
    set (JucePlugin_Build_VST3 OFF)
endif (NOT DEFINED JucePlugin_Build_VST3)
if (NOT DEFINED JucePlugin_Build_AU)
    set (JucePlugin_Build_AU OFF)
endif (NOT DEFINED JucePlugin_Build_AU)
if (NOT DEFINED JucePlugin_Build_AUv3)
    set (JucePlugin_Build_AUv3 OFF)
endif (NOT DEFINED JucePlugin_Build_AUv3)
if (NOT DEFINED JucePlugin_Build_RTAS)
    set (JucePlugin_Build_RTAS OFF)
endif (NOT DEFINED JucePlugin_Build_RTAS)
if (NOT DEFINED JucePlugin_Build_AAX)
    set (JucePlugin_Build_AAX OFF)
endif (NOT DEFINED JucePlugin_Build_AAX)
if (NOT DEFINED JucePlugin_Build_Standalone)
    set (JucePlugin_Build_Standalone OFF)
endif (NOT DEFINED JucePlugin_Build_Standalone)
if (NOT DEFINED JucePlugin_Build_Unity)
    set (JucePlugin_Build_Unity OFF)
endif (NOT DEFINED JucePlugin_Build_Unity)

option (LUAJIT_DISABLE_FFI "Disable FFI." ON)
option (LUAJIT_ENABLE_LUA52COMPAT "Enable Lua 5.2 compatibility." ON)
option (LUAJIT_DISABLE_JIT "Disable JIT." OFF)
option (LUAJIT_DISABLE_GC64 "Disable LJ_GC64 mode for x64." OFF)
option (LUAJIT_DISABLE_BUFFER "Disable Buffer." OFF)

option (LUAJIT_USE_SYSMALLOC "Use the system provided memory allocator (realloc)." OFF)
option (LUAJIT_USE_VALGRIND "This define is required to run LuaJIT under Valgrind." OFF)
option (LUAJIT_USE_GDBJIT "This is the client for the GDB JIT API." OFF)
option (LUA_USE_APICHECK "Turn on assertions for the Lua/C API to debug problems with lua_* calls." OFF)
option (LUA_USE_ASSERT "Turn on assertions for the whole LuaJIT VM." ON)
mark_as_advanced (LUAJIT_DISABLE_FFI LUAJIT_ENABLE_LUA52COMPAT LUAJIT_DISABLE_JIT LUAJIT_DISABLE_GC64 LUAJIT_DISABLE_BUFFER
  LUAJIT_USE_SYSMALLOC LUAJIT_USE_VALGRIND LUAJIT_USE_GDBJIT LUA_USE_APICHECK LUA_USE_ASSERT)

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/app)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/app)
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/app)



#=============================================================================================================================
#JUCE
#=============================================================================================================================
set (JUCE_INC "JuceLibraryCode" "JUCE/modules")
if (UNIX AND NOT APPLE)
    find_package (PkgConfig REQUIRED)
    pkg_search_module (ALSA REQUIRED alsa)
    pkg_search_module (FREETYPE2 REQUIRED freetype2)
    pkg_search_module (LIBCURL REQUIRED libcurl)
    pkg_search_module (WEBKIT2GTK-4.0 REQUIRED webkit2gtk-4.0)
    pkg_search_module (GTK+-X11-3.0 REQUIRED gtk+-x11-3.0)

    set (JUCE_INC ${JUCE_INC}
        ${ALSA_INCLUDE_DIRS}
        ${FREETYPE2_INCLUDE_DIRS}
        ${LIBCURL_INCLUDE_DIRS}
        ${WEBKIT2GTK-4.0_INCLUDE_DIRS}
        ${GTK+-X11-3.0_INCLUDE_DIRS}
    )

    find_library (RT rt)
    find_library (DL dl)
    find_library (PTHREAD pthread)
    find_library (GL GL)
endif (UNIX AND NOT APPLE)

file (GLOB_RECURSE JUCE_SRC "JuceLibraryCode/*.cpp" "JuceLibraryCode/*.h")
add_library (libJUCE SHARED ${JUCE_SRC})
set_target_properties (libJUCE PROPERTIES
  PREFIX "lib" IMPORT_PREFIX "lib" OUTPUT_NAME "JUCE")
set_source_files_properties ("JuceLibraryCode/JuceHeader.h" PROPERTIES HEADER_FILE_ONLY TRUE)
target_include_directories (libJUCE PUBLIC ${JUCE_INC})

set (JUCE_DEBUG_DEF "DEBUG=1" "_DEBUG=1")
set (JUCE_NDEBUG_DEF "NDEBUG=1")
set (JUCE_LINUX_DEF "LINUX=1")
set (JUCE_WIN_DEF "")
set (JUCE_OSX_DEF "")

set (JUCE_MODULE_DEF 
    "JUCE_DISPLAY_SPLASH_SCREEN=$<IF:$<BOOL:${JUCE_DISPLAY_SPLASH_SCREEN}>,1,0>"
    "JUCE_USE_DARK_SPLASH_SCREEN=$<IF:$<BOOL:${JUCE_USE_DARK_SPLASH_SCREEN}>,1,0>"
    "JUCE_MODULE_AVAILABLE_juce_analytics=1"
    "JUCE_MODULE_AVAILABLE_juce_audio_basics=1"
    "JUCE_MODULE_AVAILABLE_juce_audio_devices=1"
    "JUCE_MODULE_AVAILABLE_juce_audio_formats=1"
    "JUCE_MODULE_AVAILABLE_juce_audio_processors=1"
    "JUCE_MODULE_AVAILABLE_juce_audio_utils=1"
    "JUCE_MODULE_AVAILABLE_juce_box2d=1"
    "JUCE_MODULE_AVAILABLE_juce_core=1"
    "JUCE_MODULE_AVAILABLE_juce_cryptography=1"
    "JUCE_MODULE_AVAILABLE_juce_data_structures=1"
    "JUCE_MODULE_AVAILABLE_juce_dsp=1"
    "JUCE_MODULE_AVAILABLE_juce_events=1"
    "JUCE_MODULE_AVAILABLE_juce_graphics=1"
    "JUCE_MODULE_AVAILABLE_juce_gui_basics=1"
    "JUCE_MODULE_AVAILABLE_juce_gui_extra=1"
    "JUCE_MODULE_AVAILABLE_juce_opengl=1"
    "JUCE_MODULE_AVAILABLE_juce_osc=1"
    "JUCE_MODULE_AVAILABLE_juce_product_unlocking=1"
    "JUCE_MODULE_AVAILABLE_juce_video=1"
    "JUCE_GLOBAL_MODULE_SETTINGS_INCLUDED=1"
    "JUCE_STRICT_REFCOUNTEDPOINTER=1"
    "JUCE_STANDALONE_APPLICATION=0"
    "JucePlugin_Build_VST=$<IF:$<BOOL:${JucePlugin_Build_VST}>,1,0>"
    "JucePlugin_Build_VST3=$<IF:$<BOOL:${JucePlugin_Build_VST3}>,1,0>"
    "JucePlugin_Build_AU=$<IF:$<BOOL:${JucePlugin_Build_AU}>,1,0>"
    "JucePlugin_Build_AUv3=$<IF:$<BOOL:${JucePlugin_Build_AUv3}>,1,0>"
    "JucePlugin_Build_RTAS=$<IF:$<BOOL:${JucePlugin_Build_RTAS}>,1,0>"
    "JucePlugin_Build_AAX=$<IF:$<BOOL:${JucePlugin_Build_AAX}>,1,0>"
    "JucePlugin_Build_Standalone=$<IF:$<BOOL:${JucePlugin_Build_Standalone}>,1,0>"
    "JucePlugin_Build_Unity=$<IF:$<BOOL:${JucePlugin_Build_Unity}>,1,0>"
)

if (CMAKE_BUILD_TYPE STREQUAL Debug)
    target_compile_definitions (libJUCE PUBLIC ${JUCE_DEBUG_DEF})
else (CMAKE_BUILD_TYPE STREQUAL Debug)
    target_compile_definitions (libJUCE PUBLIC ${JUCE_NDEBUG_DEF})
endif (CMAKE_BUILD_TYPE STREQUAL Debug)

if (WIN32)
    target_compile_definitions (libJUCE PUBLIC ${JUCE_WIN_DEF})
elseif (UNIX AND NOT APPLE)
    target_compile_definitions (libJUCE PUBLIC ${JUCE_LINUX_DEF})
elseif (APPLE)
    target_compile_definitions (libJUCE PUBLIC ${JUCE_OSX_DEF})
endif ()

target_compile_definitions (libJUCE PUBLIC ${JUCE_MODULE_DEF})

if (MSVC)
    target_compile_definitions (libJUCE PRIVATE "JUCE_DLL_BUILD=1")
    target_compile_definitions (libJUCE PRIVATE "JUCE_DISABLE_DLL_ALLOCATORS=1")
endif (MSVC)

target_compile_definitions (libJUCE PUBLIC "JUCE_MODAL_LOOPS_PERMITTED=1" "JUCE_CATCH_UNHANDLED_EXCEPTIONS=1")

if (NOT MSVC)
    target_compile_options (libJUCE PRIVATE
    -fPIC
    -fvisibility=default
    )

    if (WIN32)
        target_link_libraries (libJUCE PRIVATE
            -m64
            -s
            -lgdi32
            -luser32
            -lkernel32
            -lcomctl32
            -lwinmm
            -luuid
            -lwsock32
            -lwininet
            -lversion
            -lole32
            -lws2_32
            -loleaut32
            -limm32
            -lcomdlg32
            -lshlwapi
            -lrpcrt4
            -lopengl32
        )
    elseif (UNIX AND NOT APPLE)
        target_link_libraries (libJUCE PRIVATE
            -shared
            -fvisibility=default
            ${RT}
            ${DL}
            ${PTHREAD}
            ${GL}
            ${ALSA_LIBRARIES}
            ${FREETYPE2_LIBRARIES}
            ${LIBCURL_LIBRARIES}
        )
    elseif (APPLE)
        target_link_libraries (libJUCE PRIVATE
            "-framework Accelerate"
            "-framework AudioToolbox"
            "-framework AVFoundation"
            "-framework AVKit"
            "-framework Carbon"
            "-framework Cocoa"
            "-framework CoreAudio"
            "-framework CoreAudioKit"
            "-framework CoreMedia"
            "-framework CoreMIDI"
            "-framework DiscRecording"
            "-framework Foundation"
            "-framework IOKit"
            "-framework OpenGL"
            "-framework QuartzCore"
            "-framework WebKit"
        )
    endif ()
    
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS}  -pthread -fPIC")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_C_FLAGS}" )
else (NOT MSVC)
    if (CMAKE_BUILD_TYPE STREQUAL Debug)
        target_compile_options (libJUCE PUBLIC
            /permissive-#符合模式:是
	        /GS#安全检查:启用安全检查
	        /Zc:wchar_t#将WChar_t视为内置类型:是
	        /Gm-#启用最小重新生成:否
	        /sdl#SDL检查:是
	        /fp:precise#浮点模型:精度
	        /Zc:forScope#强制For循环范围中的合规性:是
	        /Gd#调用约定:__cdecl
	        /nologo#取消显示启动版权标志:是
	        /bigobj#较大生成对象:是
        )
        target_link_options (libJUCE PUBLIC
	        /MANIFEST#生成清单:是
	        /NXCOMPAT#数据执行保护(DEP):是
	        /DYNAMICBASE#随机基址:是
	        /LARGEADDRESSAWARE#启用大地址:是
	        /SUBSYSTEM:WINDOWS#子系统:窗口
	        /MANIFESTUAC:NO#启用用户账户控制:否
	        /NOLOGO#取消显示启动版权标志:是
        )
    else (CMAKE_BUILD_TYPE STREQUAL Debug)
        target_compile_options (${DYNAMIC_LIBRARY} PUBLIC
            /permissive-#符合模式:是
	        /GS#安全检查:启用安全检查
	        /GL#全程序优化:是
	        /Gy#启用函数级链接:是
	        /Zc:wchar_t#将WChar_t视为内置类型:是
	        /Gm-#启用最小重新生成:否
	        /sdl#SDL检查:是
	        /fp:precise#浮点模型:精度
	        /Zc:forScope#强制For循环范围中的合规性:是
	        /Gd#调用约定:__cdecl
	        /Oi#启用内部函数:是
	        /nologo#取消显示启动版权标志:是
	        /bigobj#较大生成对象:是
        )
        target_link_options (libJUCE PUBLIC
	        /MANIFEST#生成清单:是
	        /LTCG:incremental#链接时间代码生成:使用快速链接时间代码生成
	        /NXCOMPAT#数据执行保护(DEP):是
	        /DYNAMICBASE#随机基址:是
	        /LARGEADDRESSAWARE#启用大地址:是
	        /OPT:REF#引用:是
	        /SUBSYSTEM:WINDOWS#子系统:窗口
	        /MANIFESTUAC:NO#启用用户账户控制:否
	        /OPT:ICF#启用COMDAT折叠:是
	        /NOLOGO#取消显示启动版权标志:是
        )
    endif (CMAKE_BUILD_TYPE STREQUAL Debug)
endif (NOT MSVC)




#=============================================================================================================================
#LuaJIT
#=============================================================================================================================
set (CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

INCLUDE(CheckLibraryExists)
INCLUDE(CheckFunctionExists)
INCLUDE(CheckCSourceCompiles)
INCLUDE(CheckTypeSize)
INCLUDE(CheckCCompilerFlag)

if (NOT WIN32)
  find_library (DL_LIBRARY "dl")
  if (DL_LIBRARY)
    set (CMAKE_REQUIRED_LIBRARIES ${DL_LIBRARY})
    list (APPEND LIBS ${DL_LIBRARY})
  endif (DL_LIBRARY)
  CHECK_FUNCTION_EXISTS (dlopen LUA_USE_DLOPEN)
  if (NOT LUA_USE_DLOPEN)
    message (FATAL_ERROR "Cannot compile a useful lua.
Function dlopen() seems not to be supported on your platform.
Apparently you are not on a Windows platform as well.
So lua has no way to deal with shared libraries!")
  endif (NOT LUA_USE_DLOPEN)
endif (NOT WIN32)

CHECK_LIBRARY_EXISTS (m sin "" LUA_USE_LIBM)
if (LUA_USE_LIBM)
  list (APPEND LIBS m)
endif ()

find_package (Readline)
if (READLINE_FOUND)
  include_directories (${READLINE_INCLUDE_DIR})
  list (APPEND LIBS ${READLINE_LIBRARIES})
  set (LUAJIT_USE_READLINE 1)
endif (READLINE_FOUND)

macro (LJ_TEST_ARCH stuff)
  CHECK_C_SOURCE_COMPILES ("
#undef ${stuff}
#include \"lj_arch.h\"
#if ${stuff}
int main() { return 0; }
#else
#error \"not defined\"
#endif
" ${stuff})
endmacro (LJ_TEST_ARCH stuff)

macro (LJ_TEST_ARCH_VALUE stuff value)
  CHECK_C_SOURCE_COMPILES("
#undef ${stuff}
#include \"lj_arch.h\"
#if ${stuff} == ${value}
int main() { return 0; }
#else
#error \"not defined\"
#endif
" ${stuff}_${value})
endmacro (LJ_TEST_ARCH_VALUE stuff value)

set (CMAKE_REQUIRED_INCLUDES ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/LuaJIT/src)
foreach (arch X64 X86 ARM ARM64 PPC PPCSPE MIPS MIPS64 S390X)
  LJ_TEST_ARCH (LJ_TARGET_${arch})
  if (LJ_TARGET_${arch})
    STRING(TOLOWER ${arch} TARGET_LJARCH)
    MESSAGE(STATUS "LuaJIT Target ${TARGET_LJARCH}")
    break ()
  endif (LJ_TARGET_${arch})
endforeach (arch X64 X86 ARM ARM64 PPC PPCSPE MIPS MIPS64 S390X)

if (NOT TARGET_LJARCH)
  message (FATAL_ERROR "architecture not supported")
endif ()

set (DASM_ARCH ${TARGET_LJARCH})
set (DASM_FLAGS)
set (TARGET_ARCH)
list (APPEND TARGET_ARCH "LUAJIT_TARGET=LUAJIT_ARCH_${TARGET_LJARCH}")

LJ_TEST_ARCH (LJ_TARGET_ARM64)
if (LJ_TARGET_ARM64)
  LJ_TEST_ARCH (__AARCH64EB__)
  if (__AARCH64EB__)
    list (APPEND TARGET_ARCH "__AARCH64EB__=1")
  endif (__AARCH64EB__)
endif (LJ_TARGET_ARM64)

LJ_TEST_ARCH (LJ_TARGET_PPC)
if (LJ_TARGET_PPC)
  LJ_TEST_ARCH_VALUE (LJ_LE 1)
  if (LJ_LE_1)
    list (APPEND TARGET_ARCH "LJ_ARCH_ENDIAN=LUAJIT_LE")
  else (LJ_LE_1)
    list (APPEND TARGET_ARCH "LJ_ARCH_ENDIAN=LUAJIT_BE")
  endif (LJ_LE_1)
endif (LJ_TARGET_PPC)

LJ_TEST_ARCH (LJ_TARGET_MIPS)
if (LJ_TARGET_MIPS)
  LJ_TEST_ARCH (MIPSEL)
  if (NOT MIPSEL)
    list (APPEND TARGET_ARCH "__MIPSEL__=1")
  endif (NOT MIPSEL)
endif (LJ_TARGET_MIPS)

LJ_TEST_ARCH (LJ_TARGET_PS3)
if (LJ_TARGET_PS3)
  list (APPEND TARGET_ARCH "__CELLOS_LV2__=1")
  set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DLUAJIT_USE_SYSMALLOC")
endif (LJ_TARGET_PS3)

LJ_TEST_ARCH_VALUE (LJ_LE 1)
if (LJ_LE_1)
  set (DASM_FLAGS ${DASM_FLAGS} -D ENDIAN_LE)
else (LJ_LE_1)
  set (DASM_FLAGS ${DASM_FLAGS} -D ENDIAN_BE)
endif (LJ_LE_1)
LJ_TEST_ARCH_VALUE (LJ_ARCH_BITS 64)
if (LJ_ARCH_BITS_64)
  set (DASM_FLAGS ${DASM_FLAGS} -D P64)
endif (LJ_ARCH_BITS_64)
LJ_TEST_ARCH_VALUE (LJ_HASJIT 1)
if (LJ_HASJIT_1)
  set (DASM_FLAGS ${DASM_FLAGS} -D JIT)
endif (LJ_HASJIT_1)
LJ_TEST_ARCH_VALUE (LJ_HASFFI 1)
if (LJ_HASFFI_1)
  set (DASM_FLAGS ${DASM_FLAGS} -D FFI)
endif (LJ_HASFFI_1)
LJ_TEST_ARCH_VALUE (LJ_DUALNUM 1)
if (LJ_DUALNUM_1)
  set (DASM_FLAGS ${DASM_FLAGS} -D DUALNUM)
endif (LJ_DUALNUM_1)
LJ_TEST_ARCH_VALUE (LJ_ARCH_HASFPU 1)
if (LJ_ARCH_HASFPU_1)
  set (DASM_FLAGS ${DASM_FLAGS} -D HASFPU)
  list (APPEND TARGET_ARCH "LJ_ARCH_HASFPU=1")
else (LJ_ARCH_HASFPU_1)
  list (APPEND TARGET_ARCH "LJ_ARCH_HASFPU=0")
endif (LJ_ARCH_HASFPU_1)
LJ_TEST_ARCH_VALUE (LJ_ABI_SOFTFP 1)
if (NOT LJ_ABI_SOFTFP_1)
  set (DASM_FLAGS ${DASM_FLAGS} -D HFABI)
  list (APPEND TARGET_ARCH "LJ_ABI_SOFTFP=0")
else (NOT LJ_ABI_SOFTFP_1)
  list (APPEND TARGET_ARCH "LJ_ABI_SOFTFP=1")
endif (NOT LJ_ABI_SOFTFP_1)
LJ_TEST_ARCH_VALUE (LJ_NO_UNWIND 1)
if (LJ_NO_UNWIND_1)
  set (DASM_FLAGS ${DASM_FLAGS} -D NO_UNWIND)
  list (APPEND TARGET_ARCH "LUAJIT_NO_UNWIND=1")
endif (LJ_NO_UNWIND_1)
if (WIN32)
  set (DASM_FLAGS ${DASM_FLAGS} -D WIN)
endif (WIN32)

#if (TARGET_LJARCH STREQUAL "x86")
#  LJ_TEST_ARCH_VALUE (__SSE2__ 1)
#  if (__SSE2__1)
#    set (DASM_FLAGS ${DASM_FLAGS} -D SSE)
#  endif (__SSE2__1)
#endif (TARGET_LJARCH STREQUAL "x86")
if (TARGET_LJARCH STREQUAL "x64")
  LJ_TEST_ARCH_VALUE (LJ_FR2 1)
  if (NOT LJ_FR2_1)
    set (DASM_ARCH "x86")
  endif (NOT LJ_FR2_1)
endif (TARGET_LJARCH STREQUAL "x64")
if (TARGET_LJARCH STREQUAL "arm")
  if (${CMAKE_SYSTEM_NAME} MATCHES "iOS")
    set (DASM_AFLAGS ${DASM_AFLAGS} -D IOS)
  endif (${CMAKE_SYSTEM_NAME} MATCHES "iOS")
endif (TARGET_LJARCH STREQUAL "arm")
LJ_TEST_ARCH_VALUE (LJ_TARGET_MIPSR6 1)
if (LJ_TARGET_MIPSR6_1)
  set (DASM_AFLAGS ${DASM_AFLAGS} -D MIPSR6)
endif (LJ_TARGET_MIPSR6_1)
if (TARGET_LJARCH STREQUAL "ppc")
  LJ_TEST_ARCH_VALUE (LJ_ARCH_SQRT 1)
  if (LJ_ARCH_SQRT_1)
    set (DASM_FLAGS ${DASM_FLAGS} -D SQRT)
  endif (LJ_ARCH_SQRT_1)
  LJ_TEST_ARCH_VALUE (LJ_ARCH_ROUND 1)
  if (LJ_ARCH_ROUND_1)
    set (DASM_FLAGS ${DASM_FLAGS} -D ROUND)
  endif (LJ_ARCH_ROUND_1)
  LJ_TEST_ARCH_VALUE (LJ_ARCH_PPC32ON64 1)
  if (LJ_ARCH_PPC32ON64_1)
    set (DASM_FLAGS ${DASM_FLAGS} -D GPR64)
  endif (LJ_ARCH_PPC32ON64_1)
  if (LJ_TARGET_PS3)
    set (DASM_FLAGS ${DASM_FLAGS} -D PPE)
  endif (LJ_TARGET_PS3)
  LJ_TEST_ARCH_VALUE (LJ_ARCH_PPC_OPD 1)
  if (LJ_ARCH_PPC_OPD_1)
    set (DASM_FLAGS ${DASM_FLAGS} -D OPD)
  endif (LJ_ARCH_PPC_OPD_1)
  LJ_TEST_ARCH_VALUE (LJ_ARCH_PPC_OPDENV 1)
  if (LJ_ARCH_PPC_OPDENV_1)
    set (DASM_FLAGS ${DASM_FLAGS} -D OPDENV)
  endif (LJ_ARCH_PPC_OPDENV_1)
  LJ_TEST_ARCH_VALUE (LJ_ARCH_PPC_ELFV2 1)
  if (LJ_ARCH_PPC_ELFV2_1)
    set (DASM_FLAGS ${DASM_FLAGS} -D ELFV2)
  endif (LJ_ARCH_PPC_ELFV2_1)
endif (TARGET_LJARCH STREQUAL "ppc")
if (TARGET_LJARCH STREQUAL "s390x")  # untested
  set (DASM_ARCH "s390x")
endif (TARGET_LJARCH STREQUAL "s390x")

if (WIN32)
  set (LJVM_MODE peobj)
elseif (APPLE)
  set (LJVM_MODE machasm)
else ()
  if (${CMAKE_SYSTEM_NAME} MATCHES "SunOS")
    set (LJVM_MODE static)
  elseif (LJ_TARGET_PS3)
    set (LJVM_MODE static)
  else()
    set (LJVM_MODE elfasm)
  endif()
endif ()

# lj_str_hash requirement
LJ_TEST_ARCH_VALUE (LJ_HAS_OPTIMISED_HASH 1)
if (TARGET_LJARCH STREQUAL "x64" AND LJ_HAS_OPTIMISED_HASH_1)
  set_target_properties (libLuaJIT minilua PROPERTIES CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -msse4.2")
endif (TARGET_LJARCH STREQUAL "x64" AND LJ_HAS_OPTIMISED_HASH_1)

add_executable (minilua LuaJIT/src/host/minilua.c)
set_target_properties (minilua PROPERTIES COMPILE_DEFINITIONS "${TARGET_ARCH}")
CHECK_LIBRARY_EXISTS (m pow "" MINILUA_USE_LIBM)
if (MINILUA_USE_LIBM)
  message (STATUS "Use libm to build minilua")
  target_link_libraries (minilua m)
endif (MINILUA_USE_LIBM)

add_custom_command (OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/LuaJIT/buildvm_arch.h
  COMMAND minilua ${CMAKE_CURRENT_SOURCE_DIR}/LuaJIT/dynasm/dynasm.lua ${DASM_FLAGS} -o ${CMAKE_CURRENT_BINARY_DIR}/LuaJIT/buildvm_arch.h ${CMAKE_CURRENT_SOURCE_DIR}/LuaJIT/src/vm_${DASM_ARCH}.dasc
  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/LuaJIT/dynasm/dynasm.lua minilua
)

set (SRC_LJLIB LuaJIT/src/lib_base.c LuaJIT/src/lib_math.c LuaJIT/src/lib_bit.c LuaJIT/src/lib_string.c LuaJIT/src/lib_table.c
  LuaJIT/src/lib_io.c LuaJIT/src/lib_os.c LuaJIT/src/lib_package.c LuaJIT/src/lib_debug.c LuaJIT/src/lib_jit.c LuaJIT/src/lib_ffi.c
  LuaJIT/src/lib_buffer.c LuaJIT/src/lib_init.c)

set (SRC_LJCORE LuaJIT/src/lj_gc.c LuaJIT/src/lj_err.c LuaJIT/src/lj_char.c LuaJIT/src/lj_bc.c LuaJIT/src/lj_obj.c LuaJIT/src/lj_buf.c
  LuaJIT/src/lj_str.c LuaJIT/src/lj_tab.c LuaJIT/src/lj_func.c LuaJIT/src/lj_udata.c LuaJIT/src/lj_meta.c LuaJIT/src/lj_debug.c
  LuaJIT/src/lj_state.c LuaJIT/src/lj_dispatch.c LuaJIT/src/lj_vmevent.c LuaJIT/src/lj_vmmath.c LuaJIT/src/lj_strscan.c LuaJIT/src/lj_strfmt.c LuaJIT/src/lj_strfmt_num.c
  LuaJIT/src/lj_api.c LuaJIT/src/lj_profile.c LuaJIT/src/lj_lex.c LuaJIT/src/lj_parse.c LuaJIT/src/lj_bcread.c LuaJIT/src/lj_bcwrite.c LuaJIT/src/lj_load.c
  LuaJIT/src/lj_ir.c LuaJIT/src/lj_opt_mem.c LuaJIT/src/lj_opt_fold.c LuaJIT/src/lj_opt_narrow.c
  LuaJIT/src/lj_opt_dce.c LuaJIT/src/lj_opt_loop.c LuaJIT/src/lj_opt_split.c LuaJIT/src/lj_opt_sink.c
  LuaJIT/src/lj_mcode.c LuaJIT/src/lj_snap.c LuaJIT/src/lj_record.c LuaJIT/src/lj_crecord.c LuaJIT/src/lj_ffrecord.c
  LuaJIT/src/lj_asm.c LuaJIT/src/lj_trace.c LuaJIT/src/lj_gdbjit.c
  LuaJIT/src/lj_ctype.c LuaJIT/src/lj_cdata.c LuaJIT/src/lj_cconv.c LuaJIT/src/lj_ccall.c LuaJIT/src/lj_ccallback.c
  LuaJIT/src/lj_carith.c LuaJIT/src/lj_clib.c LuaJIT/src/lj_cparse.c
  LuaJIT/src/lj_lib.c LuaJIT/src/lj_alloc.c LuaJIT/src/lib_aux.c
  LuaJIT/src/lj_prng.c LuaJIT/src/lj_serialize.c
  ${SRC_LJLIB})# LuaJIT/src/lib_init.c LuaJIT/src/lj_str_hash.c

set (SRC_BUILDVM LuaJIT/src/host/buildvm.c LuaJIT/src/host/buildvm_asm.c
LuaJIT/src/host/buildvm_peobj.c LuaJIT/src/host/buildvm_lib.c LuaJIT/src/host/buildvm_fold.c
${CMAKE_CURRENT_BINARY_DIR}/LuaJIT/buildvm_arch.h)

## GENERATE
add_executable (buildvm ${SRC_BUILDVM})
set_target_properties (buildvm PROPERTIES COMPILE_DEFINITIONS "${TARGET_ARCH}")
target_include_directories (buildvm BEFORE PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/LuaJIT dynasm LuaJIT/src)

macro (add_buildvm_target _target _mode)
  add_custom_command (OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/LuaJIT/${_target}
    COMMAND buildvm ARGS -m ${_mode} -o ${CMAKE_CURRENT_BINARY_DIR}/LuaJIT/${_target} ${ARGN}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    DEPENDS buildvm ${ARGN}
  )
endmacro (add_buildvm_target)

if (MSVC)
  add_buildvm_target (lj_vm.obj peobj)
  set (LJ_VM_SRC ${CMAKE_CURRENT_BINARY_DIR}/LuaJIT/lj_vm.obj)
else (MSVC)
  add_buildvm_target (lj_vm.s ${LJVM_MODE})
  set (LJ_VM_SRC ${CMAKE_CURRENT_BINARY_DIR}/LuaJIT/lj_vm.s)
endif (MSVC)
add_buildvm_target (lj_ffdef.h ffdef ${SRC_LJLIB})
add_buildvm_target (lj_bcdef.h bcdef ${SRC_LJLIB})
add_buildvm_target (lj_folddef.h folddef LuaJIT/src/lj_opt_fold.c)
add_buildvm_target (lj_recdef.h recdef ${SRC_LJLIB})
add_buildvm_target (lj_libdef.h libdef ${SRC_LJLIB})
add_buildvm_target (vmdef.lua vmdef ${SRC_LJLIB})

set (DEPS
  ${LJ_VM_SRC}
  ${CMAKE_CURRENT_BINARY_DIR}/LuaJIT/lj_ffdef.h
  ${CMAKE_CURRENT_BINARY_DIR}/LuaJIT/lj_bcdef.h
  ${CMAKE_CURRENT_BINARY_DIR}/LuaJIT/lj_libdef.h
  ${CMAKE_CURRENT_BINARY_DIR}/LuaJIT/lj_recdef.h
  ${CMAKE_CURRENT_BINARY_DIR}/LuaJIT/lj_folddef.h
  ${CMAKE_CURRENT_BINARY_DIR}/LuaJIT/vmdef.lua
  )

## COMPILE
add_library (libLuaJIT SHARED ${SRC_LJCORE} ${DEPS})
target_link_libraries (libLuaJIT ${LIBS})
target_include_directories (libLuaJIT BEFORE PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/LuaJIT dynasm LuaJIT/src)
target_include_directories (libLuaJIT PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/LuaJIT/src)
set_target_properties (libLuaJIT PROPERTIES
  PREFIX "lib" IMPORT_PREFIX "lib" OUTPUT_NAME "LuaJIT")
if (WIN32 AND NOT CYGWIN)
  target_compile_definitions (libLuaJIT PRIVATE "LUA_BUILD_AS_DLL")
endif (WIN32 AND NOT CYGWIN)

if (LUAJIT_DISABLE_FFI)
  target_compile_definitions (libLuaJIT PUBLIC "LUAJIT_DISABLE_FFI")
  target_compile_definitions (minilua PUBLIC "LUAJIT_DISABLE_FFI")
  target_compile_definitions (buildvm PUBLIC "LUAJIT_DISABLE_FFI")
endif (LUAJIT_DISABLE_FFI)
if (LUAJIT_ENABLE_LUA52COMPAT)
  target_compile_definitions (libLuaJIT PUBLIC "LUAJIT_ENABLE_LUA52COMPAT")
  target_compile_definitions (minilua PUBLIC "LUAJIT_ENABLE_LUA52COMPAT")
  target_compile_definitions (buildvm PUBLIC "LUAJIT_ENABLE_LUA52COMPAT")
endif (LUAJIT_ENABLE_LUA52COMPAT)
if (LUAJIT_DISABLE_JIT)
  target_compile_definitions (libLuaJIT PUBLIC "LUAJIT_DISABLE_JIT")
  target_compile_definitions (minilua PUBLIC "LUAJIT_DISABLE_JIT")
  target_compile_definitions (buildvm PUBLIC "LUAJIT_DISABLE_JIT")
endif (LUAJIT_DISABLE_JIT)
if (LUAJIT_DISABLE_GC64)
  target_compile_definitions (libLuaJIT PUBLIC "LUAJIT_DISABLE_GC64")
  target_compile_definitions (minilua PUBLIC "LUAJIT_DISABLE_GC64")
  target_compile_definitions (buildvm PUBLIC "LUAJIT_DISABLE_GC64")
endif (LUAJIT_DISABLE_GC64)
if (LUAJIT_DISABLE_BUFFER)
  target_compile_definitions (libLuaJIT PUBLIC "LUAJIT_DISABLE_BUFFER")
  target_compile_definitions (minilua PUBLIC "LUAJIT_DISABLE_BUFFER")
  target_compile_definitions (buildvm PUBLIC "LUAJIT_DISABLE_BUFFER")
endif (LUAJIT_DISABLE_BUFFER)
if (LUAJIT_USE_SYSMALLOC)
  target_compile_definitions (libLuaJIT PUBLIC "LUAJIT_USE_SYSMALLOC")
  target_compile_definitions (minilua PUBLIC "LUAJIT_USE_SYSMALLOC")
  target_compile_definitions (buildvm PUBLIC "LUAJIT_USE_SYSMALLOC")
endif (LUAJIT_USE_SYSMALLOC)
if (LUAJIT_USE_VALGRIND)
  target_compile_definitions (libLuaJIT PUBLIC "LUAJIT_USE_VALGRIND")
  target_compile_definitions (minilua PUBLIC "LUAJIT_USE_VALGRIND")
  target_compile_definitions (buildvm PUBLIC "LUAJIT_USE_VALGRIND")
endif (LUAJIT_USE_VALGRIND)
if (LUAJIT_USE_GDBJIT)
  target_compile_definitions (libLuaJIT PUBLIC "LUAJIT_USE_GDBJIT")
  target_compile_definitions (minilua PUBLIC "LUAJIT_USE_GDBJIT")
  target_compile_definitions (buildvm PUBLIC "LUAJIT_USE_GDBJIT")
endif (LUAJIT_USE_GDBJIT)
if (LUAJIT_USE_APICHECK)
  target_compile_definitions (libLuaJIT PUBLIC "LUAJIT_USE_APICHECK")
  target_compile_definitions (minilua PUBLIC "LUAJIT_USE_APICHECK")
  target_compile_definitions (buildvm PUBLIC "LUAJIT_USE_APICHECK")
endif (LUAJIT_USE_APICHECK)
if (LUAJIT_USE_ASSERT)
  target_compile_definitions (libLuaJIT PUBLIC "LUAJIT_USE_ASSERT")
  target_compile_definitions (minilua PUBLIC "LUAJIT_USE_ASSERT")
  target_compile_definitions (buildvm PUBLIC "LUAJIT_USE_ASSERT")
endif (LUAJIT_USE_ASSERT)

CHECK_TYPE_SIZE ("void*" SIZEOF_VOID_P)
if (SIZEOF_VOID_P EQUAL 8)
  target_compile_definitions (libLuaJIT PUBLIC "_FILE_OFFSET_BITS=64" "_LARGEFILE_SOURCE")
  target_compile_definitions (minilua PUBLIC "_FILE_OFFSET_BITS=64" "_LARGEFILE_SOURCE")
  target_compile_definitions (buildvm PUBLIC "_FILE_OFFSET_BITS=64" "_LARGEFILE_SOURCE")
endif (SIZEOF_VOID_P EQUAL 8)

check_c_compiler_flag ("-fno-stack-protector" HAS_NO_STACK_PROTECTOR)
if (HAS_NO_STACK_PROTECTOR)
  set_target_properties (libLuaJIT minilua buildvm PROPERTIES CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fno-stack-protector")
endif (HAS_NO_STACK_PROTECTOR)

check_c_compiler_flag ("-fomit-frame-pointer" HAS_OMIT_FRAME_POINTER)
if (HAS_NO_STACK_PROTECTOR)
  set_target_properties (libLuaJIT minilua buildvm PROPERTIES CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fomit-frame-pointer")
endif (HAS_NO_STACK_PROTECTOR)

if (WIN32)
  target_compile_definitions (libLuaJIT PUBLIC "LUAJIT_OS=LUAJIT_OS_WINDOWS")
  target_compile_definitions (minilua PUBLIC "LUAJIT_OS=LUAJIT_OS_WINDOWS")
  target_compile_definitions (buildvm PUBLIC "LUAJIT_OS=LUAJIT_OS_WINDOWS")
  if (NOT MSVC)
    set_target_properties (libLuaJIT minilua buildvm PROPERTIES CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -malign-double" )
  endif (NOT MSVC)
elseif (APPLE)
  target_compile_definitions (libLuaJIT PUBLIC "LUAJIT_OS=LUAJIT_OS_OSX")
  target_compile_definitions (minilua PUBLIC "LUAJIT_OS=LUAJIT_OS_OSX")
  target_compile_definitions (buildvm PUBLIC "LUAJIT_OS=LUAJIT_OS_OSX")
  if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    target_compile_definitions (libLuaJIT PUBLIC "LUAJIT_UNWIND_EXTERNAL")
    target_compile_definitions (minilua PUBLIC "LUAJIT_UNWIND_EXTERNAL")
    target_compile_definitions (buildvm PUBLIC "LUAJIT_UNWIND_EXTERNAL")
  endif (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  if (${CMAKE_SYSTEM_NAME} MATCHES "iOS")  # untested
    target_compile_definitions (libLuaJIT PUBLIC "TARGET_OS_IPHONE=1")
    target_compile_definitions (minilua PUBLIC "TARGET_OS_IPHONE=1")
    target_compile_definitions (buildvm PUBLIC "TARGET_OS_IPHONE=1")
    if (TARGET_LJARCH STREQUAL "arm64")
      set_target_properties (libLuaJIT minilua buildvm PROPERTIES CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fno-omit-frame-pointer")
    endif (TARGET_LJARCH STREQUAL "arm64")
  else (${CMAKE_SYSTEM_NAME} MATCHES "iOS")
    target_compile_definitions (libLuaJIT PUBLIC "TARGET_OS_IPHONE=0")
    target_compile_definitions (minilua PUBLIC "TARGET_OS_IPHONE=0")
    target_compile_definitions (buildvm PUBLIC "TARGET_OS_IPHONE=0")
  endif (${CMAKE_SYSTEM_NAME} MATCHES "iOS")
else ()
  if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    target_compile_definitions (libLuaJIT PUBLIC "LUAJIT_OS=LUAJIT_OS_LINUX")
    target_compile_definitions (minilua PUBLIC "LUAJIT_OS=LUAJIT_OS_LINUX")
    target_compile_definitions (buildvm PUBLIC "LUAJIT_OS=LUAJIT_OS_LINUX")
  else(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    target_compile_definitions (libLuaJIT PUBLIC "LUAJIT_OS=LUAJIT_OS_OTHER")
    target_compile_definitions (minilua PUBLIC "LUAJIT_OS=LUAJIT_OS_OTHER")
    target_compile_definitions (buildvm PUBLIC "LUAJIT_OS=LUAJIT_OS_OTHER")
  endif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")

  if (NOT LJ_NO_UNWIND_1)
    # Find out whether the target toolchain always generates unwind tables.
    execute_process (COMMAND bash "-c"
      "exec 2>/dev/null; echo 'extern void b(void);int a(void){b();return 0;}' | ${CMAKE_C_COMPILER} -c -x c - -o tmpunwind.o && { grep -qa -e eh_frame -e __unwind_info tmpunwind.o || grep -qU -e eh_frame -e __unwind_info tmpunwind.o; } && echo E"
      OUTPUT_VARIABLE TARGET_TESTUNWIND)
    if (${TARGET_TESTUNWIND} MATCHES "E")
      message (STATUS "Use -DLUAJIT_UNWIND_EXTERNAL")
      target_compile_definitions (libLuaJIT PUBLIC "LUAJIT_UNWIND_EXTERNAL")
      target_compile_definitions (minilua PUBLIC "LUAJIT_UNWIND_EXTERNAL")
      target_compile_definitions (buildvm PUBLIC "LUAJIT_UNWIND_EXTERNAL")
    endif (${TARGET_TESTUNWIND} MATCHES "E")
  endif (NOT LJ_NO_UNWIND_1)
endif ()

# lj_str_hash requirement
LJ_TEST_ARCH_VALUE (LJ_HAS_OPTIMISED_HASH 1)
if (TARGET_LJARCH STREQUAL "x64" AND LJ_HAS_OPTIMISED_HASH_1)
  set_target_properties (libLuaJIT minilua buildvm PROPERTIES CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -msse4.2")
endif (TARGET_LJARCH STREQUAL "x64" AND LJ_HAS_OPTIMISED_HASH_1)

if (MSVC)
  target_compile_definitions (libLuaJIT PRIVATE "_CRT_SECURE_NO_WARNINGS")
  target_compile_definitions (minilua PRIVATE "_CRT_SECURE_NO_WARNINGS")
  target_compile_definitions (buildvm PRIVATE "_CRT_SECURE_NO_WARNINGS")
endif (MSVC)




#=============================================================================================================================
#LUCE
#=============================================================================================================================
file (GLOB LUCE_SRC "*.cpp" "*.h")
file (GLOB_RECURSE LUCE_MODULE_SRC "adapters/*.cpp" "adapters/*.h")
add_library (libLUCE SHARED ${LUCE_SRC} ${LUCE_MODULE_SRC})

if (MSVC)
    target_compile_definitions (libLUCE PUBLIC "JUCE_DLL=1" "JUCE_DISABLE_DLL_ALLOCATORS=1")
endif (MSVC)
target_compile_definitions (libLUCE PRIVATE "LUCE_DLL_BUILD=1")
target_link_libraries (libLUCE PUBLIC libLuaJIT libJUCE)

if (MSVC)
    if (MSVC_VERSION GREATER_EQUAL 1925)
        target_compile_options (libJUCE PUBLIC "/Zc:preprocessor")
    elseif (MSVC_VERSION GREATER_EQUAL 1915)
        target_compile_options (libJUCE PUBLIC "/experimental:preprocessor")
    else ()
        message (FATAL_ERROR "MSVC can't support C++20 __VA_OPT__")
    endif ()
endif (MSVC)




#=============================================================================================================================
#LUCE Demo
#=============================================================================================================================
file (GLOB_RECURSE LUCE_DEMO1_SRC "extras/demo1/*.cpp")
add_executable (LUCE-demo1 ${LUCE_DEMO1_SRC})
target_compile_definitions (LUCE-demo1 PRIVATE "LUCE_DLL=1")
target_link_libraries (LUCE-demo1 PRIVATE libLUCE)

#set (LUA_SCRIPT_DIR "${CMAKE_CURRENT_BINARY_DIR}/lua/")
#if (NOT (EXISTS "${LUA_SCRIPT_DIR}" AND IS_DIRECTORY "${LUA_SCRIPT_DIR}"))
#        file (MAKE_DIRECTORY ${LUA_SCRIPT_DIR})
#endif (NOT (EXISTS "${LUA_SCRIPT_DIR}" AND IS_DIRECTORY "${LUA_SCRIPT_DIR}"))

#file (GLOB LUA_SCRIPT_LIST "${CMAKE_CURRENT_SOURCE_DIR}/extras/demo1/lua/*.lua")
#foreach (SCRIPT ${LUA_SCRIPT_LIST})
#    add_custom_command (TARGET LUCE-demo1 POST_BUILD
#    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${SCRIPT}" "${LUA_SCRIPT_DIR}"
#)
#endforeach (SCRIPT ${LUA_SCRIPT_LIST})

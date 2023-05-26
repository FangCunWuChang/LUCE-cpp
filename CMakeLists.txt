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
if (NOT DEFINED JUCE_USE_WINRT_MIDI)
    set (JUCE_USE_WINRT_MIDI OFF)
endif (NOT DEFINED JUCE_USE_WINRT_MIDI)
if (NOT DEFINED JUCE_ASIO)
    set (JUCE_ASIO OFF)
endif (NOT DEFINED JUCE_ASIO)
if (NOT DEFINED JUCE_JACK)
    set (JUCE_JACK OFF)
endif (NOT DEFINED JUCE_JACK)
if (NOT DEFINED JUCE_BELA)
    set (JUCE_BELA OFF)
endif (NOT DEFINED JUCE_BELA)
if (NOT DEFINED JUCE_USE_ANDROID_OPENSLES)
    set (JUCE_USE_ANDROID_OPENSLES OFF)
endif (NOT DEFINED JUCE_USE_ANDROID_OPENSLES)
if (NOT DEFINED JUCE_ASIO_DEBUGGING)
    set (JUCE_ASIO_DEBUGGING OFF)
endif (NOT DEFINED JUCE_ASIO_DEBUGGING)
if (NOT DEFINED JUCE_WINRT_MIDI_LOGGING)
    set (JUCE_WINRT_MIDI_LOGGING OFF)
endif (NOT DEFINED JUCE_WINRT_MIDI_LOGGING)
if (NOT DEFINED JUCE_PLUGINHOST_VST)
    set (JUCE_PLUGINHOST_VST OFF)
endif (NOT DEFINED JUCE_PLUGINHOST_VST)
if (NOT DEFINED JUCE_PLUGINHOST_VST3)
    set (JUCE_PLUGINHOST_VST3 OFF)
endif (NOT DEFINED JUCE_PLUGINHOST_VST3)
if (NOT DEFINED JUCE_PLUGINHOST_AU)
    set (JUCE_PLUGINHOST_AU OFF)
endif (NOT DEFINED JUCE_PLUGINHOST_AU)
if (NOT DEFINED JUCE_PLUGINHOST_LADSPA)
    set (JUCE_PLUGINHOST_LADSPA OFF)
endif (NOT DEFINED JUCE_PLUGINHOST_LADSPA)
if (NOT DEFINED JUCE_PLUGINHOST_LV2)
    set (JUCE_PLUGINHOST_LV2 OFF)
endif (NOT DEFINED JUCE_PLUGINHOST_LV2)
if (NOT DEFINED JUCE_PLUGINHOST_ARA)
    set (JUCE_PLUGINHOST_ARA OFF)
endif (NOT DEFINED JUCE_PLUGINHOST_ARA)
if (NOT DEFINED JUCE_CUSTOM_VST3_SDK)
    set (JUCE_CUSTOM_VST3_SDK OFF)
endif (NOT DEFINED JUCE_CUSTOM_VST3_SDK)
if (NOT DEFINED JUCE_USE_MP3AUDIOFORMAT)
    set (JUCE_USE_MP3AUDIOFORMAT OFF)
endif (NOT DEFINED JUCE_USE_MP3AUDIOFORMAT)
if (NOT DEFINED JUCE_USE_LAME_AUDIO_FORMAT)
    set (JUCE_USE_LAME_AUDIO_FORMAT OFF)
endif (NOT DEFINED JUCE_USE_LAME_AUDIO_FORMAT)

set (LUCE_APP_DIR ${CMAKE_CURRENT_SOURCE_DIR}/app CACHE STRING INTERNAL)

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

if (JUCE_ASIO)
    if (DEFINED ASIO_SRC_PATH)
        set (JUCE_ASIO_INC_PATH ${ASIO_SRC_PATH})
    else (DEFINED ASIO_SRC_PATH)
        message (SEND_ERROR "ASIO SDK notfound!")
    endif (DEFINED ASIO_SRC_PATH)
endif (JUCE_ASIO)
if (JUCE_PLUGINHOST_VST)
    if (DEFINED VST_SRC_PATH)
        set (JUCE_VST_INC_PATH ${VST_SRC_PATH})
    else (DEFINED VST_SRC_PATH)
        message (SEND_ERROR "VST SDK notfound!")
    endif (DEFINED VST_SRC_PATH)
endif (JUCE_PLUGINHOST_VST)
if (JUCE_PLUGINHOST_VST3 AND JUCE_CUSTOM_VST3_SDK)
    if (DEFINED VST3_SRC_PATH)
        set (JUCE_VST3_INC_PATH ${VST3_SRC_PATH})
        
        #StringConvert Method For VST3 SDK Version 3.7.3 Or Later
        set (JUCE_VST3_SRC_FIX
            "${JUCE_VST3_INC_PATH}/public.sdk/source/vst/utility/stringconvert.cpp"
        )
    else (DEFINED VST3_SRC_PATH)
        message (SEND_ERROR "VST3 SDK notfound!")
    endif (DEFINED VST3_SRC_PATH)
endif (JUCE_PLUGINHOST_VST3 AND JUCE_CUSTOM_VST3_SDK)
if (JUCE_PLUGINHOST_LV2)
    if (DEFINED LV2_SRC_PATH)
        set (JUCE_LV2_INC_PATH ${LV2_SRC_PATH})
    else (DEFINED LV2_SRC_PATH)
        #LV2 SDK Path
        set (JUCE_LV2_INC_PATH
            "${CMAKE_CURRENT_SOURCE_DIR}/JUCE/modules/juce_audio_processors/format_types/LV2_SDK"
            "${CMAKE_CURRENT_SOURCE_DIR}/JUCE/modules/juce_audio_processors/format_types/LV2_SDK/lv2"
            "${CMAKE_CURRENT_SOURCE_DIR}/JUCE/modules/juce_audio_processors/format_types/LV2_SDK/lilv"
            "${CMAKE_CURRENT_SOURCE_DIR}/JUCE/modules/juce_audio_processors/format_types/LV2_SDK/lilv/src"
            "${CMAKE_CURRENT_SOURCE_DIR}/JUCE/modules/juce_audio_processors/format_types/LV2_SDK/serd"
            "${CMAKE_CURRENT_SOURCE_DIR}/JUCE/modules/juce_audio_processors/format_types/LV2_SDK/sord"
            "${CMAKE_CURRENT_SOURCE_DIR}/JUCE/modules/juce_audio_processors/format_types/LV2_SDK/sratom"
        )
    endif (DEFINED LV2_SRC_PATH)

    #LV2 SDK Src
    set (JUCE_LV2_SRC_FIX
        "${CMAKE_CURRENT_SOURCE_DIR}/JUCE/modules/juce_audio_processors/juce_audio_processors_lv2_libs.cpp"
    )
endif (JUCE_PLUGINHOST_LV2)
if (JUCE_PLUGINHOST_ARA)
    if (DEFINED ARA_SRC_PATH)
        set (JUCE_ARA_INC_PATH ${ARA_SRC_PATH})
    else (DEFINED ARA_SRC_PATH)
        message (SEND_ERROR "ARA SDK notfound!")
    endif (DEFINED ARA_SRC_PATH)

    #ARA SDK Src
    set (JUCE_ARA_SRC_FIX
        "${CMAKE_CURRENT_SOURCE_DIR}/JUCE/modules/juce_audio_processors/juce_audio_processors_ara.cpp"
    )
endif (JUCE_PLUGINHOST_ARA)

file (GLOB_RECURSE JUCE_SRC "JuceLibraryCode/*.cpp" "JuceLibraryCode/*.h")
add_library (libJUCE SHARED ${JUCE_SRC} ${JUCE_VST3_SRC_FIX} ${JUCE_LV2_SRC_FIX} ${JUCE_ARA_SRC_FIX})
set_target_properties (libJUCE PROPERTIES
  PREFIX "lib" IMPORT_PREFIX "lib" OUTPUT_NAME "JUCE")
set_source_files_properties ("JuceLibraryCode/JuceHeader.h" PROPERTIES HEADER_FILE_ONLY TRUE)
target_include_directories (libJUCE PUBLIC
    ${JUCE_INC}
    ${JUCE_ASIO_INC_PATH}
    ${JUCE_VST_INC_PATH}
    ${JUCE_VST3_INC_PATH}
    ${JUCE_LV2_INC_PATH}
    ${JUCE_ARA_INC_PATH}
)

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
    "JUCE_USE_WINRT_MIDI=$<IF:$<BOOL:${JUCE_USE_WINRT_MIDI}>,1,0>"
    "JUCE_ASIO=$<IF:$<BOOL:${JUCE_ASIO}>,1,0>"
    "JUCE_JACK=$<IF:$<BOOL:${JUCE_JACK}>,1,0>"
    "JUCE_BELA=$<IF:$<BOOL:${JUCE_BELA}>,1,0>"
    "JUCE_USE_ANDROID_OPENSLES=$<IF:$<BOOL:${JUCE_USE_ANDROID_OPENSLES}>,1,0>"
    "JUCE_ASIO_DEBUGGING=$<IF:$<BOOL:${JUCE_ASIO_DEBUGGING}>,1,0>"
    "JUCE_WINRT_MIDI_LOGGING=$<IF:$<BOOL:${JUCE_WINRT_MIDI_LOGGING}>,1,0>"
    "JUCE_PLUGINHOST_VST=$<IF:$<BOOL:${JUCE_PLUGINHOST_VST}>,1,0>"
    "JUCE_PLUGINHOST_VST3=$<IF:$<BOOL:${JUCE_PLUGINHOST_VST3}>,1,0>"
    "JUCE_PLUGINHOST_AU=$<IF:$<BOOL:${JUCE_PLUGINHOST_AU}>,1,0>"
    "JUCE_PLUGINHOST_LADSPA=$<IF:$<BOOL:${JUCE_PLUGINHOST_LADSPA}>,1,0>"
    "JUCE_PLUGINHOST_LV2=$<IF:$<BOOL:${JUCE_PLUGINHOST_LV2}>,1,0>"
    "JUCE_PLUGINHOST_ARA=$<IF:$<BOOL:${JUCE_PLUGINHOST_ARA}>,1,0>"
    "JUCE_CUSTOM_VST3_SDK=$<IF:$<BOOL:${JUCE_CUSTOM_VST3_SDK}>,1,0>"
    "JUCE_USE_MP3AUDIOFORMAT=$<IF:$<BOOL:${JUCE_USE_MP3AUDIOFORMAT}>,1,0>"
    "JUCE_USE_LAME_AUDIO_FORMAT=$<IF:$<BOOL:${JUCE_USE_LAME_AUDIO_FORMAT}>,1,0>"
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
        target_compile_options (libJUCE PUBLIC
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
#Lua
#=============================================================================================================================
add_library (libLua SHARED lua/onelua.c)
target_compile_definitions (libLua PUBLIC "LUA_BUILD_AS_DLL=1")
target_include_directories (libLua PUBLIC "lua")


#=============================================================================================================================
#LUCE
#=============================================================================================================================
file (GLOB LUCE_SRC "*.cpp" "*.h")
file (GLOB_RECURSE LUCE_MODULE_SRC 
    "adapters/*.cpp"
    "adapters/*.h"
    "quickUI/*.cpp"
    "quickUI/*.h"
    "flowUI/*.cpp"
    "flowUI/*.h"
)
add_library (libLUCE SHARED ${LUCE_SRC} ${LUCE_MODULE_SRC})
add_dependencies (libLUCE libJUCE libLua)
target_include_directories (libLUCE PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

if (MSVC)
    target_compile_definitions (libLUCE PUBLIC "JUCE_DLL=1" "JUCE_DISABLE_DLL_ALLOCATORS=1")
endif (MSVC)
target_compile_definitions (libLUCE PRIVATE "LUCE_DLL_BUILD=1")
target_link_libraries (libLUCE PUBLIC libLua libJUCE)

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
#LUCE Demo 1
#=============================================================================================================================
file (GLOB_RECURSE LUCE_DEMO1_SRC "extras/demo1/*.cpp")
add_executable (LUCE-demo1 ${LUCE_DEMO1_SRC})
target_compile_definitions (LUCE-demo1 PRIVATE "LUCE_DLL=1")
target_link_libraries (LUCE-demo1 PRIVATE libLUCE)
add_dependencies (LUCE-demo1 libLUCE)

set_target_properties (LUCE-demo1 PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${LUCE_APP_DIR})

add_custom_command (TARGET LUCE-demo1 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    $<TARGET_FILE:libJUCE> $<TARGET_FILE_DIR:LUCE-demo1>
)
add_custom_command (TARGET LUCE-demo1 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    $<TARGET_FILE:libLua> $<TARGET_FILE_DIR:LUCE-demo1>
)
add_custom_command (TARGET LUCE-demo1 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    $<TARGET_FILE:libLUCE> $<TARGET_FILE_DIR:LUCE-demo1>
)



#=============================================================================================================================
#LUCE Demo 2
#=============================================================================================================================
file (GLOB_RECURSE LUCE_DEMO2_SRC "extras/demo2/*.cpp")
add_executable (LUCE-demo2 ${LUCE_DEMO2_SRC})
target_compile_definitions (LUCE-demo2 PRIVATE "LUCE_DLL=1")
target_link_libraries (LUCE-demo2 PRIVATE libLUCE)
add_dependencies (LUCE-demo2 libLUCE)

set_target_properties (LUCE-demo2 PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${LUCE_APP_DIR})

add_custom_command (TARGET LUCE-demo2 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    $<TARGET_FILE:libJUCE> $<TARGET_FILE_DIR:LUCE-demo2>
)
add_custom_command (TARGET LUCE-demo2 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    $<TARGET_FILE:libLua> $<TARGET_FILE_DIR:LUCE-demo2>
)
add_custom_command (TARGET LUCE-demo2 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    $<TARGET_FILE:libLUCE> $<TARGET_FILE_DIR:LUCE-demo2>
)

#=============================================================================================================================
#LUCE Demo 3
#=============================================================================================================================
file (GLOB_RECURSE LUCE_DEMO3_SRC "extras/demo3/*.cpp")
add_executable (LUCE-demo3 ${LUCE_DEMO3_SRC})
target_compile_definitions (LUCE-demo3 PRIVATE "LUCE_DLL=1")
target_link_libraries (LUCE-demo3 PRIVATE libLUCE)
add_dependencies (LUCE-demo3 libLUCE)

set_target_properties (LUCE-demo3 PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${LUCE_APP_DIR})

add_custom_command (TARGET LUCE-demo3 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    $<TARGET_FILE:libJUCE> $<TARGET_FILE_DIR:LUCE-demo3>
)
add_custom_command (TARGET LUCE-demo3 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    $<TARGET_FILE:libLua> $<TARGET_FILE_DIR:LUCE-demo3>
)
add_custom_command (TARGET LUCE-demo3 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    $<TARGET_FILE:libLUCE> $<TARGET_FILE_DIR:LUCE-demo3>
)
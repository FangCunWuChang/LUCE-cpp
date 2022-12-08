cmake_minimum_required (VERSION 3.15)
project (LUCE-cpp VERSION 0.0.1 LANGUAGES CXX C)

if (NOT DEFINED CMAKE_BUILD_TYPE)
    set (CMAKE_BUILD_TYPE "Release"  CACHE STRING "Choose the type of build." FORCE)
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

#JUCE库
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
set_source_files_properties ("JuceLibraryCode/JuceHeader.h" PROPERTIES HEADER_FILE_ONLY TRUE)
target_include_directories (libJUCE PRIVATE ${JUCE_INC})

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
    target_compile_definitions (libJUCE PRIVATE ${JUCE_DEBUG_DEF})
else (CMAKE_BUILD_TYPE STREQUAL Debug)
    target_compile_definitions (libJUCE PRIVATE ${JUCE_NDEBUG_DEF})
endif (CMAKE_BUILD_TYPE STREQUAL Debug)

if (WIN32)
    target_compile_definitions (libJUCE PRIVATE ${JUCE_WIN_DEF})
elseif (UNIX AND NOT APPLE)
    target_compile_definitions (libJUCE PRIVATE ${JUCE_LINUX_DEF})
elseif (APPLE)
    target_compile_definitions (libJUCE PRIVATE ${JUCE_OSX_DEF})
endif ()

target_compile_definitions (libJUCE PRIVATE ${JUCE_MODULE_DEF})

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
        target_compile_options (libJUCE PRIVATE
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
        target_link_options (libJUCE PRIVATE
	        /MANIFEST#生成清单:是
	        /NXCOMPAT#数据执行保护(DEP):是
	        /DYNAMICBASE#随机基址:是
	        /LARGEADDRESSAWARE#启用大地址:是
	        /SUBSYSTEM:WINDOWS#子系统:窗口
	        /MANIFESTUAC:NO#启用用户账户控制:否
	        /NOLOGO#取消显示启动版权标志:是
        )
    else (CMAKE_BUILD_TYPE STREQUAL Debug)
        target_compile_options (${DYNAMIC_LIBRARY} PRIVATE
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
        target_link_options (libJUCE PRIVATE
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
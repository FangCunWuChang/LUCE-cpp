#pragma once

#if defined (_WIN32) || defined (_WIN64)
#define       LUCE_WINDOWS 1
#elif defined (LUCE_ANDROID)
#undef        LUCE_ANDROID
#define       LUCE_ANDROID 1
#elif defined (__FreeBSD__) || (__OpenBSD__)
#define       LUCE_BSD 1
#elif defined (LINUX) || defined (__linux__)
#define       LUCE_LINUX 1
#elif defined (__APPLE_CPP__) || defined (__APPLE_CC__)
#define CF_EXCLUDE_CSTD_HEADERS 1
#include <TargetConditionals.h> // (needed to find out what platform we're using)
#include <AvailabilityMacros.h>

#if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
#define     LUCE_IPHONE 1
#define     LUCE_IOS 1
#else
#define     LUCE_MAC 1
#endif
#elif defined (__wasm__)
#define       LUCE_WASM 1
#else
#error "Unknown platform!"
#endif

#if LUCE_WINDOWS
#ifdef _MSC_VER
#ifdef _WIN64
#define LUCE_64BIT 1
#else
#define LUCE_32BIT 1
#endif
#endif

#ifdef _DEBUG
#define LUCE_DEBUG 1
#endif

#ifdef __MINGW32__
#define LUCE_MINGW 1
#ifdef __MINGW64__
#define LUCE_64BIT 1
#else
#define LUCE_32BIT 1
#endif
#endif

/** If defined, this indicates that the processor is little-endian. */
#define LUCE_LITTLE_ENDIAN 1

#if defined (_M_ARM) || defined (_M_ARM64) || defined (__arm__) || defined (__aarch64__)
#define LUCE_ARM 1
#else
#define LUCE_INTEL 1
#endif
#endif

//==============================================================================
#if LUCE_MAC || LUCE_IOS

#if defined (DEBUG) || defined (_DEBUG) || ! (defined (NDEBUG) || defined (_NDEBUG))
#define LUCE_DEBUG 1
#endif

#if ! (defined (DEBUG) || defined (_DEBUG) || defined (NDEBUG) || defined (_NDEBUG))
#warning "Neither NDEBUG or DEBUG has been defined - you should set one of these to make it clear whether this is a release build,"
#endif

#ifdef __LITTLE_ENDIAN__
#define LUCE_LITTLE_ENDIAN 1
#else
#define LUCE_BIG_ENDIAN 1
#endif

#ifdef __LP64__
#define LUCE_64BIT 1
#else
#define LUCE_32BIT 1
#endif

#if defined (__ppc__) || defined (__ppc64__)
#error "PowerPC is no longer supported by LUCE!"
#elif defined (__arm__) || defined (__arm64__)
#define LUCE_ARM 1
#else
#define LUCE_INTEL 1
#endif

#if LUCE_MAC
#if ! defined (MAC_OS_X_VERSION_10_14)
#error "The 10.14 SDK (Xcode 10.1+) is required to build LUCE apps. You can create apps that run on macOS 10.9+ by changing the deployment target."
#elif MAC_OS_X_VERSION_MIN_REQUIRED < MAC_OS_X_VERSION_10_9
#error "Building for OSX 10.8 and earlier is no longer supported!"
#endif
#endif
#endif

//==============================================================================
#if LUCE_LINUX || LUCE_ANDROID || LUCE_BSD

#ifdef _DEBUG
#define LUCE_DEBUG 1
#endif

// Allow override for big-endian Linux platforms
#if defined (__LITTLE_ENDIAN__) || ! defined (LUCE_BIG_ENDIAN)
#define LUCE_LITTLE_ENDIAN 1
#undef LUCE_BIG_ENDIAN
#else
#undef LUCE_LITTLE_ENDIAN
#define LUCE_BIG_ENDIAN 1
#endif

#if defined (__LP64__) || defined (_LP64) || defined (__arm64__)
#define LUCE_64BIT 1
#else
#define LUCE_32BIT 1
#endif

#if defined (__arm__) || defined (__arm64__) || defined (__aarch64__)
#define LUCE_ARM 1
#elif __MMX__ || __SSE__ || __amd64__
#define LUCE_INTEL 1
#endif
#endif

//==============================================================================
// Compiler type macros.

#if defined (__clang__)
#define LUCE_CLANG 1

#elif defined (__GNUC__)
#define LUCE_GCC 1

#elif defined (_MSC_VER)
#define LUCE_MSVC 1

#else
#error unknown compiler
#endif

//==============================================================================
#if LUCE_IOS || LUCE_LINUX || LUCE_BSD
/** This will try to break into the debugger if the app is currently being debugged.
    If called by an app that's not being debugged, the behaviour isn't defined - it may
    crash or not, depending on the platform.
    @see jassert()
*/
#define LUCE_BREAK_IN_DEBUGGER        { ::kill (0, SIGTRAP); }
#elif LUCE_MSVC
#ifndef __INTEL_COMPILER
#pragma intrinsic (__debugbreak)
#endif
#define LUCE_BREAK_IN_DEBUGGER        { __debugbreak(); }
#elif LUCE_INTEL && (LUCE_GCC || LUCE_CLANG || LUCE_MAC)
#if LUCE_NO_INLINE_ASM
#define LUCE_BREAK_IN_DEBUGGER       { }
#else
#define LUCE_BREAK_IN_DEBUGGER       { asm ("int $3"); }
#endif
#elif LUCE_ARM && LUCE_MAC
#define LUCE_BREAK_IN_DEBUGGER        { __builtin_debugtrap(); }
#elif LUCE_ANDROID
#define LUCE_BREAK_IN_DEBUGGER        { __builtin_trap(); }
#else
#define LUCE_BREAK_IN_DEBUGGER        { __asm int 3 }
#endif

//==============================================================================
#if LUCE_MSVC
#define LUCE_Export __declspec(dllexport)
#define LUCE_Import __declspec(dllimport)
#define LUCE_Call _cdecl
#endif

#if LUCE_CLANG
#define LUCE_Export __attribute__((visibility("default")))
#define LUCE_Import __attribute__((visibility("default")))
#define LUCE_Call
#endif

#if LUCE_GCC
#define LUCE_Export __attribute__((visibility("default")))
#define LUCE_Import __attribute__((visibility("default")))
#define LUCE_Call
#endif

#if !(LUCE_MSVC || LUCE_CLANG || LUCE_GCC)
#define LUCE_Export 
#define LUCE_Import 
#define LUCE_Call
#endif

#ifdef LUCE_API
#undef LUCE_API
#endif // LUCE_API

#if LUCE_DLL_BUILD
#define LUCE_API LUCE_Export
#else
#define LUCE_API LUCE_Import
#endif // LUCE_DLL_BUILD

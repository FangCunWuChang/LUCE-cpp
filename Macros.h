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

#ifdef _MSC_VER
#define LUCE_Export __declspec(dllexport)
#define LUCE_Import __declspec(dllimport)
#define LUCE_Call _cdecl
#endif

#ifdef __clang__
#define LUCE_Export __attribute__((visibility("default")))
#define LUCE_Import __attribute__((visibility("default")))
#define LUCE_Call
#endif

#ifdef __GNUC__
#define LUCE_Export __attribute__((visibility("default")))
#define LUCE_Import __attribute__((visibility("default")))
#define LUCE_Call
#endif

#if ! (defined (_MSC_VER) || defined (__clang__) || defined (__GNUC__))
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

#pragma once

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

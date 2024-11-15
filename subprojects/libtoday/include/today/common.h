#pragma once

#if defined _WIN32 || defined __CYGWIN__
#ifdef BUILDING_TODAY
#define TODAY_PUBLIC __declspec(dllexport)
#else
#define TODAY_PUBLIC __declspec(dllimport)
#endif
#else
#ifdef BUILDING_TODAY
#define TODAY_PUBLIC __attribute__((visibility("default")))
#else
#define TODAY_PUBLIC
#endif
#endif
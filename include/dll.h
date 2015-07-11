#ifndef DLL_H
#define DLL_H

#include "Nooskewl_Engine/map.h"
#include "Nooskewl_Engine/map_logic.h"

#ifdef _MSC_VER
#define MONSTERRPG3_EXPORT __declspec(dllexport)
#else
#define MONSTERRPG3_EXPORT __attribute__((visibility("default")))
#endif

using namespace Nooskewl_Engine;

extern "C" {
	MONSTERRPG3_EXPORT Map_Logic *get_map_logic(Map *map);
}

#endif // DLL_H

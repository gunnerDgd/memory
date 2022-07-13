#pragma once
#ifdef synapse_memory_export_mode
#define synapse_memory_dll _declspec(dllexport)
#else
#define synapse_memory_dll _declspec(dllimport)
#endif
/* 
 * File:   Globals.h
 * Author: John
 *
 * Created on 1 février 2015, 17:42
 */

#ifndef GLOBALS_H
#define	GLOBALS_H
#include "UI.h"
#include <random>
#include <memory>

extern float g_delta_t;
extern std::random_device g_random_device;
extern std::mt19937 g_mt19937;
extern UI g_UI;

#endif	/* GLOBALS_H */


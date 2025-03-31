// HEADER for "ARCH" used in "PROFILING" for specific module ""

/*
*
*
*
*
*/

#pragma once

//------------------------
//  	DEPENDANCY
//------------------------ 
// dependancy on "ARCH_PROFILE" for 1
#if !defined(ARCH_PROFILE)
	#error "ARCH_PROFILE should be included, please include it then continue"
#endif


//------------------------
//  PRE-DELCARATIONS
//------------------------ 
// func_declare
// cexp_declare


// header definition
#ifndef _ARCH_PROFILING__H

#include "prof_dependancies.hpp"

//------------------------
//    HEADER DEFINITION
//------------------------ 

#include "timer/timer.hpp"

// declare_struct
// declare_casting


#define _ARCH_PROFILING__H 1

//------------------------
//  HEADER FUNCTIONALITY
//------------------------ 


#endif

void test_repetitive_calls( void func (void) = nullptr, unsigned reps = 1000000)
{
	if (func == nullptr) { return;}
	if (reps < 1) { return;}
	
	double collection = 0;
	for ( unsigned i =0 ; i < reps ; i++)
	{
		{
		timer_dump = 0;
		ut_timer timeit(true);
		func();
		}
		collection += static_cast<float>(timer_dump);
	}
	
	double avrg_time = collection/static_cast<double>(reps);
	collection /= static_cast<double>(reps)*static_cast<double>(TOTAL_CALLS);
	
	DISPLAY_CALLERS
	
	global_caller_time.initialization = static_cast<float>(global_caller.initialization)*collection;
	global_caller_time.casting = static_cast<float>(global_caller.casting)*collection;
	global_caller_time.operators = static_cast<float>(global_caller.operators)*collection;
	global_caller_time.functions = static_cast<float>(global_caller.functions)*collection;
	global_caller_time.methods = static_cast<float>(global_caller.methods)*collection;
	global_caller_time.misc = static_cast<float>(global_caller.misc)*collection;
	
	std::cout << "Average time per run \t" << avrg_time << " microseconds"<< std::endl;
	std::cout << "Average time per call \t" << collection << " microseconds"<< std::endl;
	std::cout << global_caller_time << std::endl;
}


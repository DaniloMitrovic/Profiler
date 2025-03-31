// HEADER for "ARCH" used in "PROFILING" for specific module ""

/*	Basic profiling tools for my own code. Expects few preprocessor macros to work.
*

*	Original import file expects 
		ARCH_DEBG - for debugging purposes , 
		ARCH_UTST - for unittesting purposes,
		ARCH_CLRS - for caller tracking purposes 
		ARCH_VERB - for verbosity purposes
		
		ARCH_PROFILE	(0 for none active, expects bitwise OR flag for different functionality)

*	Like so:
	#define ARCH_PROFILE 	0					// nothng active, any macro is considered as empty space
	#define ARCH_PROFILE 	ARCH_UTST				// only active unittests, 
	#define ARCH_PROFILE 	ARCH_DEBG				// only active debugging for hunting down stray code 
	#define ARCH_PROFILE 	ARCH_CLRS				// only active callers 
	#define ARCH_PROFILE 	(ARCH_DEBG | ARCH_UTST)			// debugging and unittests : for implementing small changes 
	#define ARCH_PROFILE 	(ARCH_UTST | ARCH_CLRS)			// callers and unittests   : for profiling unittests 
	#define ARCH_PROFILE 	(ARCH_DEBG | ARCH_CLRS)			// callers and debugging   : for profiling some functionality 
	#define ARCH_PROFILE 	(ARCH_DEBG | ARCH_UTST | ARCH_CLRS)	// all enabled 		   : for deep dives 
	// optional ARCH_VERB

*	in whatever file there should be some macro guard when to load up profiler:

	// like so
	#if (ARCH_PROFILE != 0)
		#include "profiling/profiling.hpp"
	#endif
	// with optional macro reseting for any unset stuff.

*	then you can trigger activation in specific file you wish to profile or benchmark, like:
	// dependancy on "_ARCH_PROFILING__H" for 1
	#if !defined(ARCH_PROFILE)	// chekcs if macro is defined , if not makes any global macro empty space 
	
		#define INITALISER_COUNTER 	
		#define CASTING_COUNTER 	
		#define OPERATOR_COUNTER 	
		#define FUNCTION_COUNTER 	
		#define METHOD_COUNTER 		
	#else	// if it does checks for specific attribute to initialise
	
		// in this case if callers are set, it will track callers, otherwise it will not.
		#if ( (ARCH_PROFILE & ARCH_CLRS) != ARCH_CLRS)
			#define INITALISER_COUNTER 	
			#define CASTING_COUNTER 	
			#define OPERATOR_COUNTER 	
			#define FUNCTION_COUNTER 	
			#define METHOD_COUNTER 	
		#endif
	#endif

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
// func_declare 	// dont mind this, my own tab triggers for functional predeclaration
// cexp_declare 	// dont mind this, my own tab triggers for constexpresion predeclaration

// profiler dependancies, basically list of headers and functions that are used after header definition.
#include "prof_dependancies.hpp"

// header definition
#ifndef _ARCH_PROFILING__H	// from here starts structure/class definitions 


//------------------------
//    HEADER DEFINITION
//------------------------ 

#include "timer/timer.hpp"

// declare_struct 	// dont mind this, my own tab triggers for structure template
// declare_casting 	// dont mind this, my own tab triggers for structural casting, moving and copy templates 


#define _ARCH_PROFILING__H 1

//------------------------
//  HEADER FUNCTIONALITY
//------------------------ 


#endif

/*
	tests repetitive calls,
		expects function pointer [ void, (void)] to test duration off 
		expects unsigned amount of repetitions it should perform.
	
	Basically due to how threads work, each thread can be interrupted anytime. 
	So more repetitions means more stable data.
	
	how to use it:
		test_repetitive_calls( somefunction, 100); 	// calls somefunction 100 times.
		test_repetitive_calls( somefunction); 		// calls somefunction million times.
	
	issues:
		1. Error percentage 
			it basically works on this principle:
				\frac{ \sum_i^n (f(x)) } { n} 
			
			which means that for any extreme, lets call it +-e
			main influence on it is basically 
				\frac{ e }{n} for every extreme in sum of f(x).
			
			To make it neglegable, one should put very large number for n so that
				+- \frac{e} {n} \to 0
			so for n above 1 mil, error is +- e*10^{-(6+x)}
		
		2. Function timer:
			Timer tracks function duration, and it wont influence any individual stuff.
			Best to be used when tracking and testing documentation examples or code functionality.
				input function should return nothing, and take nothing as argument.
			
			In my case I perform this test over identity operations that prove code functionality.
				For example : cos(theta)^2 + sin(theta)^2 = 1 (and so on)
				I make sure every test passes before runing this, so i can see if i need to 
				touch up on something.
			
		3. Varied data:
			Due to different processes interrupting threads (such as keys, switching tabs and so on)
			This function can vary in results. So be mindfull when using about what you are doing.
	
*/
void test_repetitive_calls( void func (void) = nullptr, unsigned reps = 1000000)
{
	// edge cases for self termination 
	if (func == nullptr) { return;}
	if (reps < 1) { return;}
	
	// 
	double collection = 0.0;
	double avrg_time = 0.0;
	for ( unsigned i =0 ; i < reps ; i++)
	{
		{
			timer_dump = 0;		// resets global timer dump 
			ut_timer timeit(true);	// starts timer 
			func();			// calls function 
						// ends timer and dumps its duration into timer dump  
		}
		// adds timer dump to collection and then again.
		collection += static_cast<double>(timer_dump);
	}
	
	// average time per repetition 
	avrg_time = collection/static_cast<double>(reps);
	// average time per repetition and calls
	collection /= static_cast<double>(reps)*static_cast<double>(TOTAL_CALLS);
	
	DISPLAY_CALLERS
	TRANSLATE_CALLERS(collection)
	
	std::cout << "Average time per run \t" << avrg_time << " microseconds"<< std::endl;
	std::cout << "Average time per call \t" << collection << " microseconds"<< std::endl;
	
	DISPLAY_CALLERS_TIME
}


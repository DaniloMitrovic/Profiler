// HEADER for "ARCH" used in "PROFILING" for specific module "DEPENDANCIES"

/*	This is where all different flag functionalities is implemented for ARCH_PROFILE

*	This header file will change its composition depending on what flag is active, Thus not usable for optimized code.
	If you are finished with coding you dont need it. 

*/

#pragma once

//------------------------
//  	DEPENDANCY
//------------------------ 
// dependancy on "ARCH_PROFILE"
#if !defined(ARCH_PROFILE)
	#error "ARCH_PROFILE should be included, please include it then continue"
#endif


//------------------------
//  PRE-DELCARATIONS
//------------------------ 
// func_declare
// cexp_declare


// header definition
#ifndef _ARCH_PROFILING_DEPENDANCIES_H

#include <chrono>	// std::chrono for ut_timer
#include <cmath>	// cos,tan,sqrt,pow .... 

// definition of caller structure.
#if ( (ARCH_PROFILE & ARCH_CLRS) == ARCH_CLRS)
	
	template <typename T>
	struct caller
	{
		// each field is determined by part of structures/classes lifespan.
		T initialization;	// intialisation of structure with brackets or attributes 
		T casting;		// copy, move and type punning operators, constructors  
		T operators;		// +-*/... operator overloading templates
		T functions;		// functions that use structure as argument 
		T methods;		// private,public,static methods 
		T misc;			// anything else one might need to measure.
		
		caller()		// defaults all to 0
		:initialization(T(0)),casting(T(0)),
		operators(T(0)),functions(T(0)),
		methods(T(0)),misc(T(0))
		{}
		~caller() = default;
		
		// if one would need to bit closer specification of manipulator callers  
		T manipulators() const
		{
			return this->functions + this->methods;
		}
		// if one would need to bit closer specification of initialisation callers 
		T initializers() const
		{
			return this->initialization + this->casting + this->operators;
		}
		
		//total count of calls during run.
		T total() const
		{
			return this->manipulators()+this->initializers() + this->misc;
		}
	};
	template <typename T>
	std::ostream &operator<<(std::ostream &os, const caller<T> & other)
	{
		os << "Initializer   Counter \t" << other.initialization << '\n';
		os << "Casting       Counter \t" << other.casting << '\n';
		os << "Operators     Counter \t" << other.operators << '\n';
		os << "Functions     Counter \t" << other.functions << '\n';
		os << "Method        Counter \t" << other.methods << '\n';
		os << "Miscelaneous  Counter \t" << other.misc << '\n';
		return os;
	}
	
	static caller<unsigned> global_caller;		// main diriving force for entire project 
	static caller<double>	global_caller_time;	// main driving force for time for entire project
	
	void caller_to_time(float avrg_time)
	{
		global_caller_time.initialization = static_cast<double>(global_caller.initialization)*avrg_time;
		global_caller_time.casting = static_cast<double>(global_caller.casting)*avrg_time;
		global_caller_time.operators = static_cast<double>(global_caller.operators)*avrg_time;
		global_caller_time.functions = static_cast<double>(global_caller.functions)*avrg_time;
		global_caller_time.methods = static_cast<double>(global_caller.methods)*avrg_time;
		global_caller_time.misc = static_cast<double>(global_caller.misc)*avrg_time;
	}
	
	// macros that are used to call for specific elements
	// don't use them with ';' so linker can remove ';' if they aren't triggered.
	#define INITALISER_COUNTER 	global_caller.initialization++;
	#define CASTING_COUNTER 	global_caller.casting++;
	#define OPERATOR_COUNTER 	global_caller.operators++;
	#define FUNCTION_COUNTER 	global_caller.functions++;
	#define METHOD_COUNTER 		global_caller.methods++;
	#define MISC_COUNTER 		global_caller.misc++;
	
	#define TRANSLATE_CALLERS(x)	caller_to_time(x);
	#define DISPLAY_CALLERS 	std::cout << global_caller<< std::endl;
	#define DISPLAY_CALLERS_TIME 	std::cout << global_caller_time<< std::endl;
	#define TOTAL_CALLS		global_caller.total()

#else
	// default functionality if ARCH_CLRS isn't triggered.
	#define INITALISER_COUNTER
	#define CASTING_COUNTER 
	#define OPERATOR_COUNTER 
	#define FUNCTION_COUNTER 
	#define METHOD_COUNTER 	
	#define MISC_COUNTER 	
	
	#define TRANSLATE_CALLERS(x)
	#define DISPLAY_CALLERS 	
	#define DISPLAY_CALLERS_TIME 	
	#define TOTAL_CALLS		1
#endif


// definition of unit test structure.
// I made this so i can quickly build identity tests
#if ( (ARCH_PROFILE & ARCH_UTST) == ARCH_UTST)

	// if verbose macros (not used outside of this delcaration)
	#if ( (ARCH_PROFILE & ARCH_VERB) == ARCH_VERB)
		#define V_GEN_IND	std::cout << "Testing     General    Identity\t\t";
		#define V_GEN_ADD	std::cout << "Testing    Additive    Identity\t\t";
		#define V_GEN_SUB	std::cout << "Testing   Subtractive  Identity\t\t";
		#define V_GEN_MUL	std::cout << "Testing Multiplicative Identity\t\t";
		#define V_GEN_DIV	std::cout << "Testing    Divisive    Identity\t\t";
		#define V_UT_PASS	std::cout<< "\33[48;2;0;255;0m\33[38;2;0;0;0mPASS\33[m\n";
		#define V_UT_FAIL	std::cout<< "\33[48;2;255;0;0m\33[38;2;0;0;0mFAIL\33[m\\n";
	
	#else
		#define V_GEN_IND
		#define V_GEN_ADD
		#define V_GEN_SUB
		#define V_GEN_MUL
		#define V_GEN_DIV
		#define V_UT_PASS	std::cout<<'\n';
		#define V_UT_FAIL	std::cout<<'\n';
	#endif

	// unit test structure 
	// on pass it shows one Green PASS (on linux, GNU)
	// on fail it shows one what it got, and what it expected 
	template <class T>
	struct UTEST
	{
		static constexpr bool IDENTITY( T lhs, T rhs)
		{
			V_GEN_IND
			if (lhs == rhs)
			{
				V_UT_PASS
				return true;
			}
			else
			{
				V_UT_FAIL
				#if ( (ARCH_PROFILE & ARCH_VERB) == ARCH_VERB)
					std::cout << "\n\t : "<< lhs << '\n';
					std::cout << "\t" << rhs << '\n';
				#endif
				return false;
			}
		} 
	
		static constexpr bool IDENTITY_ADDITIVE( T lhs, T rhs, T rslt)
		{
			V_GEN_ADD
			T res = lhs+rhs;
			if (res == rslt)
			{
				V_UT_PASS
				return true;
			}
			else
			{
				V_UT_FAIL
				#if ( (ARCH_PROFILE & ARCH_VERB) == ARCH_VERB)
					std::cout << "\n\t : "<< lhs << '\n';
					std::cout << "+\t" << rhs << '\n';
					std::cout << "\t------------------------\n";
					std::cout << "\t" << res << '\n';
					std::cout << "\t" << rslt << '\n';
				#endif
				return false;
			}
		} 
		
		static constexpr bool IDENTITY_SUBTRACTIVE( T lhs, T rhs, T rslt)
		{
			V_GEN_SUB
			T res = lhs-rhs;
			if (res == rslt)
			{
				V_UT_PASS
				return true;
			}
			else
			{
				V_UT_FAIL
				#if ( (ARCH_PROFILE & ARCH_VERB) == ARCH_VERB)
					std::cout << "\n\t : "<< lhs << '\n';
					std::cout << "-\t" << rhs << '\n';
					std::cout << "\t------------------------\n";
					std::cout << "\t" << res << '\n';
					std::cout << "\t" << rslt << '\n';
				#endif
				return false;
				
		
			}
		} 
		
		static constexpr bool IDENTITY_MULTIPLICATIVE( T lhs, T rhs, T rslt)
		{
			V_GEN_MUL
			T res = lhs*rhs;
			if (res == rslt)
			{
				V_UT_PASS
				return true;
			}
			else
			{
				V_UT_FAIL
				#if ( (ARCH_PROFILE & ARCH_VERB) == ARCH_VERB)
					std::cout << "\n\t : "<< lhs << '\n';
					std::cout << "*\t" << rhs << '\n';
					std::cout << "\t------------------------\n";
					std::cout << "\t" << res << '\n';
					std::cout << "\t" << rslt << '\n';
				#endif
				return false;

			}
		}
		
		static constexpr bool IDENTITY_DIVISIVE( T lhs, T rhs, T rslt)
		{
			V_GEN_DIV
			T res = lhs*rhs;
			if (res == rslt)
			{
				V_UT_PASS
				return true;
			}
			else
			{
				V_UT_FAIL
				#if ( (ARCH_PROFILE & ARCH_VERB) == ARCH_VERB)
					std::cout << "\n\t : "<< lhs << '\n';
					std::cout << "*\t" << rhs << '\n';
					std::cout << "\t------------------------\n";
					std::cout << "\t" << res << '\n';
					std::cout << "\t" << rslt << '\n';
				#endif
				return false;

			}
		}
	};
	
	// macros that are used to call for specific elements
	// don't use them with ';' so linker can remove ';' if they aren't triggered.
	#define UTEST_GEN_ID(t,x,y) UTEST<t>::IDENTITY(x,y);
	#define UTEST_ADD_ID(t,x,y,z) UTEST<t>::IDENTITY_ADDITIVE(x,y,z);
	#define UTEST_SUB_ID(t,x,y,z) UTEST<t>::IDENTITY_SUBTRACTIVE(x,y,z);
	#define UTEST_MUL_ID(t,x,y,z) UTEST<t>::IDENTITY_MULTIPLICATIVE(x,y,z);
	#define UTEST_DIV_ID(t,x,y,z) UTEST<t>::IDENTITY_DIVISIVE(x,y,z);
	
#else
	// default functionality if ARCH_UTST isn't triggered.
	#define UTEST_GEN_ID(t,x,y) 
	#define UTEST_ADD_ID(t,x,y,z) 
	#define UTEST_SUB_ID(t,x,y,z)
	#define UTEST_MUL_ID(t,x,y,z) 
	#define UTEST_DIV_ID(t,x,y,z)
#endif

//------------------------
//    HEADER DEFINITION
//------------------------ 
// declare_struct
// declare_casting


#define _ARCH_PROFILING_DEPENDANCIES_H 1

//------------------------
//  HEADER FUNCTIONALITY
//------------------------ 


#endif

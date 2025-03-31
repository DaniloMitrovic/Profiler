// HEADER for "ARCH" used in "PROFILING" for specific module "DEPENDANCIES"

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

#include <chrono>
#include <cmath>

#if ( (ARCH_PROFILE & ARCH_CLRS) == ARCH_CLRS)
	
	template <typename T>
	struct caller
	{
	
		T initialization;
		T casting;
		T operators;
		T functions;
		T methods;
		T misc;
		
		caller()
		:initialization(T(0)),casting(T(0)),
		operators(T(0)),functions(T(0)),
		methods(T(0)),misc(T(0))
		{}
		~caller() = default;
		
		T manipulators() const
		{
			return this->functions + this->methods;
		}
		T initializers() const
		{
			return this->initialization + this->casting + this->operators;
		}
		
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
	
	static caller<unsigned> global_caller;
	static caller<double>	global_caller_time;
	
	
	#define INITALISER_COUNTER 	global_caller.initialization++;
	#define CASTING_COUNTER 	global_caller.casting++;
	#define OPERATOR_COUNTER 	global_caller.operators++;
	#define FUNCTION_COUNTER 	global_caller.functions++;
	#define METHOD_COUNTER 		global_caller.methods++;
	#define MISC_COUNTER 		global_caller.misc++;
	
	
	#define DISPLAY_CALLERS 	std::cout << global_caller<< std::endl;
	#define TOTAL_CALLS		global_caller.total()

#else
	#define DISPLAY_CALLERS
	#define TOTAL_CALLS		1
#endif



#if ( (ARCH_PROFILE & ARCH_UTST) == ARCH_UTST)

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
	
	#define UTEST_GEN_ID(t,x,y) UTEST<t>::IDENTITY(x,y);
	#define UTEST_ADD_ID(t,x,y,z) UTEST<t>::IDENTITY_ADDITIVE(x,y,z);
	#define UTEST_SUB_ID(t,x,y,z) UTEST<t>::IDENTITY_SUBTRACTIVE(x,y,z);
	#define UTEST_MUL_ID(t,x,y,z) UTEST<t>::IDENTITY_MULTIPLICATIVE(x,y,z);
	#define UTEST_DIV_ID(t,x,y,z) UTEST<t>::IDENTITY_DIVISIVE(x,y,z);
	
#else
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

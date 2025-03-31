// type definition for TOOLS library of TIMER module 

#pragma once 

#ifndef TOOLS_TIMER


typedef long long ut_timer_us;
// assings 'id' to each timer, it increments every time its initialised, and decrements when its destroyed
static size_t timer_id = 0;
// when destroyed (unless its 'harvested') every <ut_timer> dumps their value here. 
static ut_timer_us timer_dump = 0;


struct ut_timer
{
	ut_timer(bool);	// constructor
	~ut_timer();	// deconstructor
	
	friend std::ostream &operator<<(std::ostream &, const ut_timer &);
	bool pause();	// empties init_begin, adds to duration_us
	bool start();
	bool is_started() const;
	long long get_current(void) const;
	bool is_of_id( size_t &) const;
	size_t get_id(void) const;
	
	operator bool() const { return (this->init_begin != 0) or (this->duration_us != 0);} // default boolean validity check
	
	// copy move <ut_timer> of <ut_timer>
	ut_timer( const ut_timer & );
	ut_timer( ut_timer && ); // resets 'other'
	ut_timer &operator=( const ut_timer & );
	ut_timer &operator=( ut_timer && ); // resets 'other' with its id
	
	// comparison operators for <ut_timer> object  : works with duration and age 
	bool operator==(const ut_timer &) const;
	bool operator!=(const ut_timer &) const;
	bool operator<(const ut_timer &) const;
	bool operator>(const ut_timer &) const;
	bool operator<=(const ut_timer &) const;
	bool operator>=(const ut_timer &) const;
	
	// arithmetic operator for <ut_timer> object and return <ut_timer> : works with duration and age 
	ut_timer operator+( const ut_timer &) const;	
	ut_timer operator-( const ut_timer &) const;
	ut_timer operator*( const ut_timer &) const;
	ut_timer operator/( const ut_timer &) const;
	ut_timer &operator+=( const ut_timer &);	
	ut_timer &operator-=( const ut_timer &);
	ut_timer &operator*=( const ut_timer &);
	ut_timer &operator/=( const ut_timer &);
		
	//	--------------------------------------------
	//			DURATION HANDLING
	//	--------------------------------------------
	// copy move <long long> of <ut_timer>
	ut_timer( const long long & );
	ut_timer( long long && );
	ut_timer &operator=( const long long & );
	ut_timer &operator=( long long && );
	operator long long() const 
	{
		return this->duration_us;
	}
	
	// comparison operators for <long long> object
	bool operator==(const long long &) const;
	bool operator!=(const long long &) const;
	bool operator<(const long long &) const;
	bool operator>(const long long &) const;
	bool operator<=(const long long &) const;
	bool operator>=(const long long &) const;
	
	// arithmetic operator for <long long> object and return <ut_timer>
	ut_timer operator+( const long long &) const;	
	ut_timer operator-( const long long &) const;
	ut_timer operator*( const long long &) const;
	ut_timer operator/( const long long &) const;
	ut_timer &operator+=( const long long &);	
	ut_timer &operator-=( const long long &);
	ut_timer &operator*=( const long long &);
	ut_timer &operator/=( const long long &);
	
	// casting blocks (decl_cast)
	// comparison block (decl_cmp)
	// arithmetic block (decl_math)
	
	
	
	protected:
		ut_timer_us init_begin = 0;
		ut_timer_us duration_us= 0;
		size_t identification = 0;
		
		void increment_id(void);
		void decrement_id(void);
		
		
};

//stream operators 
std::ostream &operator<<(std::ostream &os, const ut_timer &other)
{
	os  << other.identification << '\t';
	
	uint8_t flg = 0;
	flg ^= static_cast<bool>(other.init_begin)*0x1;
	flg ^= static_cast<bool>(other.duration_us)*0x2;
	
	if ( flg == 0)
	{
		return os << "uninitialised";
	}
	else if( flg == 1) // just started
	{
		os << "started at " << other.init_begin;
	}
	else if (flg == 2) // just ended 
	{
		os << "duration " << other.duration_us;
	}
	else
	{
		os << "duration : " << other.duration_us << " started at : " << other.init_begin;
	}
	
	return os << " us";
}

#include "tm_constructors.cpp"
#include "tm_methods.cpp"
#include "tm_operators.cpp"
#include "tm_functions.cpp"

//defined past this point
#define TOOLS_TIMER 1


//constant/static defintions

#endif



//copy move operators for ut_timer of <ut_timer>
ut_timer &ut_timer::operator=( const ut_timer & other)
{	
	this->duration_us = other.duration_us;
	this->init_begin = other.init_begin;
	if( this->identification == 0)
	{
		this->increment_id();
	}
	return *this;
}
ut_timer &ut_timer::operator=( ut_timer && other)
{
	this->duration_us = other.duration_us;
	this->init_begin = other.init_begin;
	this->identification = other.identification;
	other.identification = 0;
	other.duration_us=0;
	other.init_begin=0;
	return *this;
}

// member comparison operators of <ut_timer> for comparison with <ut_timer>
bool ut_timer::operator==(const ut_timer & other) const
{
	/*
		in general its duration stuff for comparison
		but also age. 
	*/
	ut_timer_us this_dur = this->duration_us;
	ut_timer_us other_dur = other.duration_us;
	if (this->is_started() or other.is_started())
	{
		ut_timer_us cur = this->get_current();
		if (this->is_started())
		{
			this_dur += cur - this->init_begin;
		}
		if (other.is_started())
		{
			other_dur += cur - other.init_begin;
		}
	}
	return this_dur == other_dur;
}
bool ut_timer::operator!=(const ut_timer & other) const
{
	/*
		in general its duration stuff for comparison
		but also age. 
	*/
	ut_timer_us this_dur = this->duration_us;
	ut_timer_us other_dur = other.duration_us;
	if (this->is_started() or other.is_started())
	{
		ut_timer_us cur = this->get_current();
		if (this->is_started())
		{
			this_dur += cur - this->init_begin;
		}
		if (other.is_started())
		{
			other_dur += cur - other.init_begin;
		}
	}
	return this_dur != other_dur;
}
bool ut_timer::operator<(const ut_timer & other) const
{
	/*
		in general its duration stuff for comparison
		but also age. 
	*/
	ut_timer_us this_dur = this->duration_us;
	ut_timer_us other_dur = other.duration_us;
	if (this->is_started() or other.is_started())
	{
		ut_timer_us cur = this->get_current();
		if (this->is_started())
		{
			this_dur += cur - this->init_begin;
		}
		if (other.is_started())
		{
			other_dur += cur - other.init_begin;
		}
	}
	return this_dur < other_dur;
}
bool ut_timer::operator>(const ut_timer & other) const
{
	/*
		in general its duration stuff for comparison
		but also age. 
	*/
	ut_timer_us this_dur = this->duration_us;
	ut_timer_us other_dur = other.duration_us;
	if (this->is_started() or other.is_started())
	{
		ut_timer_us cur = this->get_current();
		if (this->is_started())
		{
			this_dur += cur - this->init_begin;
		}
		if (other.is_started())
		{
			other_dur += cur - other.init_begin;
		}
	}
	return this_dur > other_dur;
}
bool ut_timer::operator<=(const ut_timer & other) const
{
	/*
		in general its duration stuff for comparison
		but also age. 
	*/
	ut_timer_us this_dur = this->duration_us;
	ut_timer_us other_dur = other.duration_us;
	if (this->is_started() or other.is_started())
	{
		ut_timer_us cur = this->get_current();
		if (this->is_started())
		{
			this_dur += cur - this->init_begin;
		}
		if (other.is_started())
		{
			other_dur += cur - other.init_begin;
		}
	}
	return this_dur <= other_dur;
}
bool ut_timer::operator>=(const ut_timer & other) const
{
	/*
		in general its duration stuff for comparison
		but also age. 
	*/
	ut_timer_us this_dur = this->duration_us;
	ut_timer_us other_dur = other.duration_us;
	if (this->is_started() or other.is_started())
	{
		ut_timer_us cur = this->get_current();
		if (this->is_started())
		{
			this_dur += cur - this->init_begin;
		}
		if (other.is_started())
		{
			other_dur += cur - other.init_begin;
		}
	}
	return this_dur >= other_dur;
}

// arithmetic operator for <ut_timer> object for <ut_timer> of <ut_timer>
ut_timer ut_timer::operator+( const ut_timer & other ) const
{
	ut_timer ret;
	ret.duration_us = this->duration_us + other.duration_us;
	if (this->is_started() or other.is_started())
	{
		ut_timer_us cur = this->get_current();
		ret.duration_us += 2*cur - ( this->init_begin + other.init_begin);
	}
	return ret;
}	
ut_timer ut_timer::operator-( const ut_timer & other ) const
{
	ut_timer ret;
	ret.duration_us = this->duration_us - other.duration_us;
	if (this->is_started() or other.is_started())
	{
		ret.duration_us += other.init_begin - this->init_begin;
	}
	return ret;
}	
ut_timer ut_timer::operator*( const ut_timer & other ) const
{
	ut_timer ret;
	ut_timer_us this_dur = this->duration_us;
	ut_timer_us other_dur = other.duration_us;
	if (this->is_started() or other.is_started())
	{
		ut_timer_us cur = this->get_current();
		if (this->is_started())
		{
			this_dur += cur - this->init_begin;
		}
		if (other.is_started())
		{
			other_dur += cur - other.init_begin;
		}
	}
	ret.duration_us = this_dur * other_dur;
	return ret;
}
ut_timer ut_timer::operator/( const ut_timer & other ) const
{
	ut_timer ret;
	ut_timer_us this_dur = this->duration_us;
	ut_timer_us other_dur = other.duration_us;
	if (this->is_started() or other.is_started())
	{
		ut_timer_us cur = this->get_current();
		if (this->is_started())
		{
			this_dur += cur - this->init_begin;
		}
		if (other.is_started())
		{
			other_dur += cur - other.init_begin;
		}
	}
	ret.duration_us = this_dur / other_dur;
	return ret;
}

ut_timer &ut_timer::operator+=( const ut_timer & other )
{
	ut_timer_us duration= this->duration_us + other.duration_us;
	if (this->is_started() or other.is_started())
	{
		ut_timer_us cur = this->get_current();
		duration += 2*cur - ( this->init_begin + other.init_begin);
	}
	// code 
	this->duration_us = duration;
	return *this;
}	
ut_timer &ut_timer::operator-=( const ut_timer & other )
{
	ut_timer_us duration= this->duration_us - other.duration_us;
	if (this->is_started() or other.is_started())
	{
		duration += other.init_begin - this->init_begin;
	}
	this->duration_us = duration;
	return *this;
}	
ut_timer &ut_timer::operator*=( const ut_timer & other )
{
	ut_timer_us this_dur = this->duration_us;
	ut_timer_us other_dur = other.duration_us;
	if (this->is_started() or other.is_started())
	{
		ut_timer_us cur = this->get_current();
		if (this->is_started())
		{
			this_dur += cur - this->init_begin;
		}
		if (other.is_started())
		{
			other_dur += cur - other.init_begin;
		}
	}
	this->duration_us = this_dur*other_dur;
	return *this;
}	
ut_timer &ut_timer::operator/=( const ut_timer & other )
{
	ut_timer_us this_dur = this->duration_us;
	ut_timer_us other_dur = other.duration_us;
	if (this->is_started() or other.is_started())
	{
		ut_timer_us cur = this->get_current();
		if (this->is_started())
		{
			this_dur += cur - this->init_begin;
		}
		if (other.is_started())
		{
			other_dur += cur - other.init_begin;
		}
	}
	this->duration_us = this_dur/other_dur;
	return *this;
}	

//	--------------------------------------------
//			LONG LONG OPERATORS
//	--------------------------------------------
//copy move operators for long long of <ut_timer>
ut_timer &ut_timer::operator=( const long long & other)
{
	this->duration_us = other;
	return *this;
}
ut_timer &ut_timer::operator=( long long && other)
{
	this->duration_us = other;
	other = 0;
	return *this;
}

// member comparison operators of <ut_timer> for comparison with <long long>
bool ut_timer::operator==(const long long & other) const
{
	if (this->is_started())
	{
		ut_timer_us cur = this->get_current();
		return (this->duration_us + cur - this->init_begin) == other;
	}
	return this->duration_us == other;
}
bool ut_timer::operator!=(const long long & other) const
{
	if (this->is_started())
	{
		ut_timer_us cur = this->get_current();
		return (this->duration_us + cur - this->init_begin) != other;
	}
	return this->duration_us != other;
}
bool ut_timer::operator<(const long long & other) const
{
	if (this->is_started())
	{
		ut_timer_us cur = this->get_current();
		return (this->duration_us + cur - this->init_begin) < other;
	}
	return this->duration_us < other;
}
bool ut_timer::operator>(const long long & other) const
{
	if (this->is_started())
	{
		ut_timer_us cur = this->get_current();
		return (this->duration_us + cur - this->init_begin) > other;
	}
	return this->duration_us > other;
}
bool ut_timer::operator<=(const long long & other) const
{
	if (this->is_started())
	{
		ut_timer_us cur = this->get_current();
		return (this->duration_us + cur - this->init_begin) <= other;
	}
	return this->duration_us <= other;
}
bool ut_timer::operator>=(const long long & other) const
{
	if (this->is_started())
	{
		ut_timer_us cur = this->get_current();
		return (this->duration_us + cur - this->init_begin) >= other;
	}
	return this->duration_us >= other;
}

// arithmetic operator for <long long> object for <ut_timer> of <ut_timer>
ut_timer ut_timer::operator+( const long long & other ) const
{
	ut_timer ret = (*this);
	ret.duration_us += other;
	return ret;
}	
ut_timer ut_timer::operator-( const long long & other ) const
{
	ut_timer ret = (*this);
	ret.duration_us -= other;
	return ret;
}
ut_timer ut_timer::operator*( const long long & other ) const
{
	ut_timer ret = (*this);
	ret.duration_us *= other;
	return ret;
}
ut_timer ut_timer::operator/( const long long & other ) const
{
	ut_timer ret = (*this);
	ret.duration_us /= other;
	return ret;
}

ut_timer &ut_timer::operator+=( const long long & other )
{
	this->duration_us += other;
	return *this;
}	
ut_timer &ut_timer::operator-=( const long long & other )
{
	this->duration_us -= other;
	return *this;
}	
ut_timer &ut_timer::operator*=( const long long & other )
{
	this->duration_us *= other;
	return *this;
}	
ut_timer &ut_timer::operator/=( const long long & other )
{
	this->duration_us /= other;
	return *this;
}	


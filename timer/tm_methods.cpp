void 		ut_timer::increment_id(void)
{
	timer_id++;
	this->identification = timer_id;
}
void 		ut_timer::decrement_id(void)
{
	if (this->identification != 0)
	{
		timer_id--;
	}
}

//	--------------------------------------------
//			PUBLIC METHODS
//	--------------------------------------------
ut_timer_us 	ut_timer::get_current(void) const
{
	auto current = std::chrono::high_resolution_clock::now();
	return std::chrono::time_point_cast<std::chrono::microseconds>(current).time_since_epoch().count();

}
bool 		ut_timer::pause()
{
	if( this->init_begin == 0)
	{
		return false;
	}
	
	ut_timer_us cur_time = this->get_current();
	this->duration_us += (cur_time - this->init_begin);
	this->init_begin = 0;
	return true;
}
bool 		ut_timer::start()
{
	if (this->init_begin != 0)
	{
		if ( !this->pause() )
		{
			throw "Error Pausing Started Timing";
		}
	}
	this->init_begin = this->get_current();
	return true;
}

bool 		ut_timer::is_started() const
{
	return (this->init_begin != 0);
}
bool 		ut_timer::is_of_id( size_t & id) const
{
	return (this->identification == id);
}
size_t	 	ut_timer::get_id(void) const
{
	return this->identification;
}

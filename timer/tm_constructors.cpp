
ut_timer::ut_timer(bool autostart = false)
{
	this->increment_id();
	if (autostart)
	{
		this->start();
	}
}
ut_timer::~ut_timer()
{
	this->decrement_id();
	if (this->pause())
	{
		timer_dump = this->duration_us;
	}
}

//copy move constructors for ut_timer of object <ut_timer>
ut_timer::ut_timer( const ut_timer & other)
{
	this->duration_us = other.duration_us;
	this->init_begin = other.init_begin;
	if( this->identification == 0)
	{
		this->increment_id();
	}
}
ut_timer::ut_timer( ut_timer && other)
{
	this->duration_us =other.duration_us;
	this->init_begin = other.init_begin;
	this->identification = other.identification;
	other.identification = 0;
	other.duration_us=0;
	other.init_begin=0;
}

//copy move constructors for long long of object <ut_timer>
ut_timer::ut_timer( const long long & other)
{
	this->duration_us = other;
}
ut_timer::ut_timer( long long && other)
{
	this->duration_us = other;
	other=0;
}

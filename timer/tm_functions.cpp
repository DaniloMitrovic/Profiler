void clear_timer_dump(void)
{
	timer_dump =0;
}

void show_timer_dump(void)
{
	std::cout << timer_dump << std::endl;
}


void swap_timer_dump(ut_timer_us &placeholder)
{
	ut_timer_us temp = timer_dump;
	timer_dump = placeholder;
	placeholder = temp;
}

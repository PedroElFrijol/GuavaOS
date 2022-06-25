#include <stdint.h>
#define CURRENT_YEAR 2022

namespace cmos
{
	void init();
	int seconds();
	int minutes();
	int hours();
	int days();
	int months();
	int years();
	int centuries();
};
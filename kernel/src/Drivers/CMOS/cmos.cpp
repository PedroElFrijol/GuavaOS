#include "cmos.h"
#include "../IO/IObus.h"

namespace cmos{
	int seconds(){
		int cmos_address = 0x70;
		int cmos_data    = 0x71;
        outb(cmos_address, 0x0); //0x0 is seconds and 2, 4, 7, 8, 9, and 32 are all minutes, hours, days, months, years, and centuries

        int second = inb(cmos_data);
        second = (second & 0x0F) + ((second / 16) * 10);
        return second;
    }

	int minutes(){
		int cmos_address = 0x70;
		int cmos_data    = 0x71;
        outb(cmos_address, 0x2); 

        int minute = inb(cmos_data);
        minute = (minute & 0x0F) + ((minute / 16) * 10);
        return minute;
    }

	int hours(){
		int cmos_address = 0x70;
		int cmos_data    = 0x71;
        outb(cmos_address, 0x4);     

        int hour = inb(cmos_data);
        hour = (hour & 0x0F) + ((hour / 16) * 10);
        return hour;
    }

	int days(){
		int cmos_address = 0x70;
		int cmos_data    = 0x71;
        outb(cmos_address, 0x7);     

        int day = inb(cmos_data);
        day = (day & 0x0F) + ((day / 16) * 10);
        return day;
    }

	int months(){
		int cmos_address = 0x70;
		int cmos_data    = 0x71;
        outb(cmos_address, 0x8);     

        int month = inb(cmos_data);
        month = (month & 0x0F) + ((month / 16) * 10);
        return month;
    }

	int years(){
		int cmos_address = 0x70;
		int cmos_data    = 0x71;
        outb(cmos_address, 0x9);     

        int year = inb(cmos_data);
        year = (year & 0x0F) + ((year / 16) * 10);
        return year;
    }

    int centuries(){
        int cmos_address = 0x70;
		int cmos_data    = 0x71;
        outb(cmos_address, 0x32);   

        int year = inb(cmos_data);
        int century_register = 0x00; 
        int century = inb(cmos_data);

        if(century_register != 0) {
              century = (century & 0x0F) + ((century / 16) * 10);
        }

        if(century_register != 0) { //make sure we are in the correct year and not in the wrong year
              year += century * 100;
        } else {
              year += (CURRENT_YEAR / 100) * 100;
              if(year < CURRENT_YEAR) year += 100;
        }

        return century;
    }
}
#include <iostream>
#include <iostream>
#include "Functions.h"
#include <random>
#include <chrono>
#include <ctime>
#include <fstream>
#include <experimental\filesystem>

time_t funcT = time(nullptr);
tm* tmPtr = localtime(&funcT);

int random(int min, int max)
{
	unsigned int seed = static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count());
	std::mt19937 generator(seed);
	std::uniform_int_distribution<int> distribution(min, max);
	return distribution(generator);
}

void non_RepRandom(int array[], int min, int max)
{
	for (int i = 0; i < max; i++)
	{
		array[i] = random(min, max);

		for (int j = 0; j < i; j++)
		{
			if ((array[i] == array[j]) && (i != j))
			{
				i--;
				break;
			}
		}
	}
}

void non_RepRandom(int array[], int min, int max, int index)
{
	for (int i = index; i < max + index; i++)
	{
		array[i] = random(min, max);

		for (int j = index; j < i; j++)
		{
			if ((array[i] == array[j]) && (i != j))
			{
				i--;
				break;
			}
		}
	}
}

std::string currentMonth()
{
	std::string months[12] = { "01", "02", "03", "04", "05", "06", "07", "08", "09", "10", "11", "12" };
	return months[tmPtr->tm_mon];
}

std::string currMonthName()
{
	std::string months[12] = { "Styczen", "Luty", "Marzec", "Kwiecien", "Maj", "Czerwiec",
							   "Lipiec", "Sierpien", "Wrzesien", "Pazdziernik", "Listopad", "Grudzien" };
	return months[tmPtr->tm_mon];
}

int daysIn_CurrMonth()
{
	int currYear = (tmPtr->tm_year) + 1900;
	std::string mon = currentMonth();
	if (mon == "01" || mon == "03" || mon == "05" || mon == "07" || mon == "08" || mon == "10" || mon == "12") { return 31; }
	else if (mon == "04" || mon == "06" || mon == "09" || mon == "11") { return 30; }
	else if (mon == "02")
	{
		if ((currYear % 4 == 0) && (currYear % 100 != 0)) { return 29; }
		else if (currYear % 400 == 0) { return 29; }
		else { return 28; }
	}
}

std::string weekDayStr(int day)
{
	std::string week[] = {  "Niedziela", "Poniedzialek", "Wtorek", "Sroda", "Czwartek", "Piatek", "Sobota"};
	return week[day];
}

int weekDayInt(int day)
{
	int week[] = { 7, 1, 2, 3, 4, 5, 6};
	return week[day];
}
int weekDayIntFunc(int day)
{
	int week[] = { 1, 2, 3, 4, 5, 6, 7 };
	return week[day];
}

bool sysexists(std::string filepath)
{
	return std::experimental::filesystem::exists(filepath) ? 1 : 0;
}

int linesIn(std::ifstream& inputFile)
{
	int i = 0;
	int tmp;
	while (inputFile >> tmp)
	{
		i++;
	}
	return i;
}

int weekDay(int day)
{
	time_t rawtime;
	struct tm * timeinfo;
	int year = 2018, month = 5;
	int weekday[] = { 0,1,2,3,4,5,6 };

	time(&rawtime);
	timeinfo = localtime(&rawtime);
	timeinfo->tm_year = tmPtr->tm_year;
	timeinfo->tm_mon = tmPtr->tm_mon;
	timeinfo->tm_mday = day;

	mktime(timeinfo);

	return weekday[timeinfo->tm_wday];
}

int weekends()
{
	time_t t = time(nullptr);
	tm* tPtr = localtime(&t);
	tPtr->tm_mday = 1;
	mktime(tPtr);

	int sundays = 0, saturdays = 0;
	int day = 0;

	for (int i = 0; i < daysIn_CurrMonth()+1; i++, day++, tPtr->tm_wday++)
	{
		tPtr->tm_mday = day;
		if (weekDayInt(weekDay(day)) == 6)
		{
			saturdays++;
		}
		std::cout << tPtr->tm_wday << std::endl;
		if (weekDayInt(weekDay(day)) == 7)
		{
			sundays++;
			tPtr->tm_wday = 0;
		}
	}
	return saturdays + sundays;
}
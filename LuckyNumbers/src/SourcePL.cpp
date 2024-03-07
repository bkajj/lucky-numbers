#include "Functions.h"

using std::cout;
using std::cin;
using std::endl;

void ver_pl(std::string lang)
{
	std::filesystem::path txtPath = "txt/pl/";
	std::filesystem::path tempPath = "txt/pl/Temp.txt";

	time_t t = time(nullptr);
	tm* tPtr = localtime(&t);
	time_t t2 = time(nullptr);
	tm* setTime = localtime(&t2);

	int ftemp_loopLimiter; //temp loop iterator
	int studentNumber; //number of current student
	int loopLimiter; //log loop iterator, number of randomized numbers written to log
	int *student; //array of lucky numbers
	int linesCount; //number of lines in temp
	int studentsCount; //number of students in class
	int loopRepCounter; //specifies how many times program needs to randomize numbers
	int currYear = tPtr->tm_year + 1900; //current year

	setTime->tm_year = tPtr->tm_year;
	setTime->tm_mon = tPtr->tm_mon;
	setTime->tm_wday = 1;
	mktime(setTime);

	std::ifstream TempI; //temp input
	std::ifstream ReadLinesFoo; //temp temportary variable
	std::ofstream TempO; //temp output
	std::ofstream LogO; //log output

	const std::string logname = "txt/pl/" + currMonthName(lang) + " " + std::to_string(currYear) + ".txt";

	cout << "Ile uczniow jest w klasie... ";
	while (!(cin >> studentsCount)) //reading number of students from user
	{
		cout << "Wystapil blad! Sprobuj ponownie... ";
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	if (sysexists(tempPath))
	{
		TempI.open(tempPath, std::fstream::in);
		ReadLinesFoo.open(tempPath, std::fstream::in);

		linesCount = linesIn(ReadLinesFoo); //counts how much lines with numbers temp contains
		student = new int[studentsCount + linesCount]; //cretes bigger array
		for (int i = 0; TempI >> student[i]; i++); //fills the array with variables from temp (first part of array)


		TempI.close();
		ReadLinesFoo.close();
	}
	else
	{
		linesCount = 0;
		student = new int[studentsCount]; //creates smaller array
	}

	loopRepCounter = (daysIn_CurrMonth() / studentsCount) + 1;

	LogO.open(logname, std::fstream::out);

	for (int i = 0, dayCount = 1; i < loopRepCounter; i++)
	{
		if (dayCount == daysIn_CurrMonth()) break; //prevents from writing more logs than days in current month

		if (sysexists(tempPath))
		{
			if (studentsCount > linesCount) non_RepRandom(student, 1, studentsCount, linesCount); //fills the 2nd part of array with random numbers
		}
		else non_RepRandom(student, 1, studentsCount); //fills whole array with random numbers

		for (loopLimiter = 0, studentNumber = 0; loopLimiter < studentsCount; loopLimiter++, dayCount++, studentNumber++, setTime->tm_wday++)
		{
			setTime->tm_mday = dayCount; //sets the day (log)

			if (weekDayInt(weekDay(dayCount)) == 6) //skip if saturday
			{
				loopLimiter--;
				studentNumber--;
			}
			else if (weekDayInt(weekDay(dayCount)) == 7) //skip if sunday
			{
				loopLimiter--;
				studentNumber--;
				if (dayCount > 1) LogO << endl;
				setTime->tm_wday = 0;
			}
			else //generates 1 line in log
			{
				LogO << std::to_string(setTime->tm_mday) + "." + currentMonth() + "." + std::to_string(currYear) + " "
					+ weekDayStr(weekDay(dayCount), lang) + " | Szczesliwy numerek to " + std::to_string(student[studentNumber]) << endl;
			}

			if (dayCount == daysIn_CurrMonth()) break; //prevents from writing more logs than days in current month
		}

		if (studentsCount <= linesCount)
		{
			ftemp_loopLimiter = linesCount - loopLimiter; //sets temp iterator if numbers were loaded only form temp
			break;
		}
		else
		{
			ftemp_loopLimiter = studentsCount + linesCount - loopLimiter; //sets temp iterator if some or all of the numbers were randomized
		}
	}
	LogO.close();

	loopLimiter++; //precisies the number of log lines in log file
	ftemp_loopLimiter--; //precisies temp loop iterator

	TempO.open(tempPath, std::fstream::out);
	for (int i = 0; i < ftemp_loopLimiter; i++, loopLimiter++) //writes the rest of the number to temp
	{
		TempO << std::to_string(student[loopLimiter]) << endl;
	}
	TempO.close();

	system("pause");
	delete[] student;
}
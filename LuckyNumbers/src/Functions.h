#pragma once

#include <iostream>
#include <string>
#include <random>
#include <chrono>
#include <ctime>
#include <fstream>
#include <filesystem>
#include <algorithm>

//#pragma warning(disable:4715)
#pragma warning(disable:4996)

//polish version
void ver_pl(std::string lang);

//english version
void ver_eng(std::string lang);

//generates random number
int random(int min, int max);

//generates non-repeated numbers
void non_RepRandom(int array[], int min, int max);

//generates non-repeated numbers, index stars at "index"
void non_RepRandom(int array[], int min, int max, int index);

//returns numer of current month (std::string)
std::string currentMonth();

//returns name of the current month
std::string currMonthName(std::string lang);

//returns number of days in current month
int daysIn_CurrMonth();

//returns name of current day in week
std::string weekDayStr(int day, std::string lang);

//returns number of current day in week
int weekDayInt(int day);

//checks if the file of directory existing
bool sysexists(std::filesystem::path path);

//returns number of lines in file
int linesIn(std::ifstream& inputFile);

//returns number of days off in current month
int weekends();

//returns number of set day in week
int weekDay(int day);

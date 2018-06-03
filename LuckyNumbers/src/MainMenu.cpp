#include "Functions.h"

using std::cout;
using std::cin;
using std::endl;

int main()
{
	std::experimental::filesystem::path cfgPath = "txt/Config.txt"; //config file path

	std::string lang; //user defined language

	std::ofstream CfgO; //config file output
	std::ifstream CfgI; //config file input

	if (!sysexists("txt")) // creates txt directory
	{
		std::experimental::filesystem::create_directory("txt/");
	}

	if (!sysexists(cfgPath))
	{
		CfgO.open(cfgPath, std::fstream::out);

		cout << "Select language / Wybierz jezyk" << endl;
		cout << "Type PL or ENG / Wpisz PL lub ENG... ";
		getline(cin, lang); //reads language from user
		CfgO << lang << endl;

		CfgO.close();
	}
	else
	{
		CfgI.open(cfgPath, std::fstream::in);

		getline(CfgI, lang); //reads language from config file

		CfgI.close();
	}
	std::transform(lang.begin(), lang.end(), lang.begin(), toupper); //changes word to uppercase

	if (lang == "PL")
	{
		std::experimental::filesystem::create_directory("txt/pl/");
		ver_pl(lang);
	}
	else if (lang == "ENG")
	{
		std::experimental::filesystem::create_directory("txt/eng/");
		ver_eng(lang);
	}
	else
	{
		cout << "Error occurred when reading language / Podczas wczytywania jezyka wystapil blad" << endl;
		cout << "Try again! / Sprobuj ponownie!" << endl;
		system("pause");
		std::experimental::filesystem::remove(cfgPath); //removes config file when error occurred
		return 1;
	}
	return 0;
}
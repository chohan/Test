// This is the main file of job solution/project
#include "stdafx.h"

#include <iostream>

#include "Brainbench.h"
#include "IKM.h"
#include "Previsor.h"
#include "Tibra.h"
#include "Macquarie.h"
#include "Nomura.h"
#include "Barcap.h"
#include "mySTL.h"
#include "myboost.h"
#include "Test.h"
#include "Temp.h"
#include "Candy.h"
#include "EPAM.h"
#include "C_Questionnaire.h"
#include "MultiThreading.h"
#include "C11Features.h"



//################################### main ############################
int main(int argc, char* argv[])
{
	std::cout << __FILE__ << ":" << __LINE__ << " " << __FUNCTION__ << std::endl;
	std::string choice = "argv[1]";

	if (strcmpi(choice.c_str(), "C") == 0)			main_C_Questionnaire();
	if (strcmpi(choice.c_str(), "C11") == 0)		main_C11Features();
	if (strcmpi(choice.c_str(), "MT") == 0)			main_MultiThreading();
	if (strcmpi(choice.c_str(), "STL") == 0)		main_mySTL();
	if (strcmpi(choice.c_str(), "Boost") == 0)		main_myboost();
	if (strcmpi(choice.c_str(), "tmp") == 0)		main_temp();
	if (strcmpi(choice.c_str(), "Test") == 0)		main_Test();
	if (strcmpi(choice.c_str(), "bb") == 0)			main_Brainbench();
	if (strcmpi(choice.c_str(), "Previsor") == 0)	main_Previsor();
	if (strcmpi(choice.c_str(), "IKM") == 0)		main_IKM();
	if (strcmpi(choice.c_str(), "Tibra") == 0)		main_Tibra();
	if (strcmpi(choice.c_str(), "Macquarie") == 0)	main_Macquarie();
	if (strcmpi(choice.c_str(), "Nomura") == 0)		main_Nomura();
	if (strcmpi(choice.c_str(), "Barcap") == 0)		main_Barcap();
	if (strcmpi(choice.c_str(), "Candy") == 0)		main_Candy();
	if (strcmpi(choice.c_str(), "EPAM") == 0)		main_EPAM();
	std::cout << "\n\n";
}

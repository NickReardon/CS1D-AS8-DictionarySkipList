/*****************************************************************************
 * AUTHOR 	  		: Nick Reardon
 * Assignment #8	: Skip Lists
 * CLASS			: CS1D
 * SECTION			: MW - 2:30p
 * DUE DATE			: 03 / 25 / 20
 *****************************************************************************/
#include "main.h"
#include <queue>
using std::cout; using std::endl;


int main()
{

	/*
	 * HEADER OUTPUT
	 */
	PrintHeader(cout, "Prompt.txt");

	/********************************************************************/

	Skip_list skipList;


	skipList.insert(18, "San Clamente");
	skipList.insert(41, "Mission Viejo");
	skipList.insert(22, "Laguna Niguel");
	skipList.insert(44, "Irvine");

	skipList.print();

	//DELETE KEY 18
	skipList.erase(18);

	skipList.print();


	skipList.insert(58, "Lake Forest");
	skipList.insert(32, "San Diego");
	skipList.insert(49, "Anaheim");

	skipList.print();

	//DELETE KEY 58
	skipList.erase(58);

	skipList.print();


	skipList.insert(31, "Los Angeles");
	skipList.insert(17, "Orange");
	skipList.insert(72, "Palms Springs");
	skipList.insert(41, "Riverside");

	skipList.print();

	//DELETE KEY 49
	skipList.erase(49);

	skipList.print();


	skipList.insert(19, "Brea");
	skipList.insert(60, "Santa Ana");
	skipList.insert(35, "Tustin");
	skipList.insert(103, "Oceanside");
	skipList.insert(11, "La Jolla");
	skipList.insert(18, "Del Mar");
	skipList.insert(22, "Aliso Viejo");
	skipList.insert(49, "Laguna Beach");

	skipList.print();

	//DELETE KEY 41
	skipList.erase(41);

	skipList.print();

	skipList.insert(42, "Vista");
	skipList.insert(49, "San Diego");
	skipList.insert(99, "San Juan");
	skipList.insert(29, "Dana Point");
	skipList.insert(88, "El Segundo");
	skipList.insert(41, "San Clemente");
	skipList.insert(62, "Laguna Hills");

	skipList.print();


	



	system("pause");
	return 0;
}


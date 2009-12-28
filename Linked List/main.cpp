#include <string>
#include <iostream>

#include "LinkedList.h"

using namespace std;

/*
	Program: LinkedList
	Purpose: This program takes a list of contestants for the show "Survivor"
			 and let's the user remove them one by one, then outputs what the
			 user has placed in the list in the first place.

	Inputs: A list of contestants. (Twice. Once for insertion, and once for
			removal).
	Outputs: The list that was originally input.

	Author: Clark Gaebel
	Course Code: ICS4U
	Instructor: Mr. Berry
	SSN: 074-556-192
	Address: 162 Markville Road
	Phone Number: 905-944-0722
	Favorite Color: Blue
	Shoe size: 9
	Blood Type: AB+
	Date created: 28/12/2009
	Mother's maiden name: Levu
	Eye color: brown
	Favorite car: Lamborghini Gallardo

	My goals with this assignment:

		- LinkedList implementation in less than 150 code lines.
		- Main program done in less than 100 code lines.
		- Self-explanatory code.
		- Somehow show you that program headers are made obsolete by any VCS
		  and the information they contain is beyond useless. The stuff that
		  matters should be figured out by looking at the code.
		- Spend more time writing this than I spent on the assignment itself.
*/

// Grabs a list of contestants from user input.
LinkedList<string> GetContestants()
{
	LinkedList<string> retVal;

	string lastInput;

	do
	{
		cout << "Contestant's name? ";
		cin >> lastInput;

		retVal.Push(lastInput);
	}
	while(lastInput != "fin");

	retVal.Pop();	// Remove the "fin" that was inserted last.

	cout << "Done!\n";

	return retVal;
}

// Clears out the linked list one by one based on user input.
void RemoveContestants(LinkedList<string>& contestants)
{
	while(!contestants.empty())
	{
		string toRemove;

		cout << "Who shall we remove? ";
		cin >> toRemove;

		if(contestants.remove(toRemove))
			cout << "Contestant removed!\n";
		else
			cout << "Contestant not found.\n";
	}
}

// Spits out a linked list to cout. This would be so much nicer if I did it iteratively like so...
/*
	void DisplayList(const LinkedList<string>& toDisplay)
	{
		for(LinkedList<string>::iterator i = toDisplay.begin(); i != toDisplay.end(); ++i)
			cout << "Contestant: " << *i << "\n";
	}
*/
void DisplayList(LinkedList<string>::iterator toDisplay, const LinkedList<string>::iterator& end)
{
	if(toDisplay == end)
		return;

	cout << "Contestant: " << *toDisplay << "\n";

	DisplayList(++toDisplay, end);
}

int main(int, wchar_t**)
{
	LinkedList<string> contestants = GetContestants();
	LinkedList<string> backup(contestants);

	RemoveContestants(contestants);

	DisplayList(backup.begin(), backup.end());

	system("PAUSE");
	return 0;
}

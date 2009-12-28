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

	Test run:

	Contestant's name? Alice
	Contestant's name? Bob
	Contestant's name? Carol
	Contestant's name? Dave
	Contestant's name? Edgar
	Contestant's name? Fred
	Contestant's name? Gary
	Contestant's name? Harold
	Contestant's name? fin
	Done!
	Who shall we remove? Harold
	Contestant removed!
	Who shall we remove? Gary
	Contestant removed!
	Who shall we remove? Fred
	Contestant removed!
	Who shall we remove? Edgar
	Contestant removed!
	Who shall we remove? Dave
	Contestant removed!
	Who shall we remove? Carol
	Contestant removed!
	Who shall we remove? Bob
	Contestant removed!
	Who shall we remove? Alice
	Contestant removed!

	Contestant: Harold
	Contestant: Gary
	Contestant: Fred
	Contestant: Edgar
	Contestant: Dave
	Contestant: Carol
	Contestant: Bob
	Contestant: Alice

	Alice wins!
	Press any key to continue . . .
*/

// Grabs a list of contestants from user input.
LinkedList<string> GetContestants()
{
	LinkedList<string> llsRetVal;

	string sLastInput;

	do
	{
		cout << "Contestant's name? ";
		cin >> sLastInput;

		llsRetVal.Push(sLastInput);
	}
	while(sLastInput != "fin");

	llsRetVal.Pop();	// Remove the "fin" that was inserted last.

	cout << "Done!\n";

	// No shinanegans please.
	if(llsRetVal.begin() == llsRetVal.end())
		exit(-1);

	return llsRetVal;
}

// Clears out the linked list one by one based on user input.
// Returns the last contestant to be removed.
string RemoveContestants(LinkedList<string>& llspContestants)
{
	string sLastContestant;

	while(!llspContestants.empty())
	{
		string sToRemove;

		cout << "Who shall we remove? ";
		cin >> sToRemove;

		if(llspContestants.remove(sToRemove))
		{
			cout << "Contestant removed!\n";
			sLastContestant = sToRemove;
		}
		else
			cout << "Contestant not found.\n";
	}

	cout << "\n";

	return sLastContestant;
}

// Spits out a linked list to cout. This would be so much nicer if I did it iteratively like so...
/*
	void DisplayList(const LinkedList<string>& toDisplay)
	{
		for(LinkedList<string>::iterator i = toDisplay.begin(); i != toDisplay.end(); ++i)
			cout << "Contestant: " << *i << "\n";
	}
*/
void DisplayList(LinkedList<string>::iterator llsipBeginning, const LinkedList<string>::iterator& llsipEnd)
{
	if(llsipBeginning == llsipEnd)
		return;

	cout << "Contestant: " << *llsipBeginning << "\n";

	DisplayList(++llsipBeginning, llsipEnd);
}

void CongratulateWinner(string spWinner)
{
	cout << "\n" << spWinner << " wins!\n";
}

int main(int, wchar_t**)
{
	LinkedList<string> llsContestants = GetContestants();
	LinkedList<string> llsBackup(llsContestants);

	string sLastContestant = RemoveContestants(llsContestants);

	DisplayList(llsBackup.begin(), llsBackup.end());

	CongratulateWinner(sLastContestant);

	system("PAUSE");
	return 0;
}

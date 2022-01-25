#include <iostream>
#include <cstring>
#include <iomanip>
using namespace std;

extern const float addtime_rate = 0.5;
struct data
{
	int id;
	int weight;
	string detergent;
	int duration;
	string type;
	float price;
	string start;
	char machine;
};


void input(data *str, int x, char w) //w will determine whether the passed structure washer(w) or dryer(x)
{
	char choice;
	char detergent[4][7] = {"Dynamo", "Breeze", "Daia", "None"};
	char temperature[4][8] = {"+++++++", "+++++", "+++", "+"};
	float price_rate[4] = {1.5, 1.0, 0.5, 0.0};
	bool end = false;
	
	str[x].price = 0;
	system ("cls");
	
	switch (w)
	{
		case 'w' : cout << "WASHING MACHINE\n\n"; break;
		case 'x' : cout << "DRYING MACHINE\n\n"; break;
	}
	
	cout << "\nID number   : " << str[x].id;
	cout << "\nNotes: Please Remember your ID number for other activity.\n\n";

	do
	{
		end = false;
		cout << "Available weight:-\nA - 7kg  (RM 3.00)\nB - 14kg (RM 5.00)\nC - 21kg (RM 7.00)\n" << "\nWeight   : ";
		cin >> choice;
		
		switch (choice)
		{
			case 'A': str[x].weight = 7;
					  str[x].price += 3.0; break;
			case 'B': str[x].weight = 14;
					  str[x].price += 5.0; break;
			case 'C': str[x].weight = 21;
					  str[x].price += 7.0; break;
			default: cout << "Error!\n";
					 end = true;
		}
	}while (end);
	
	if (w == 'w')
	{		
		do
		{
			cout << "\nA = Dynamo (+RM 1.50)\nB = Breeze (+RM 1.00)\nC = Daia   (+RM 0.50)\nD = None   (Free)" << endl 
				 <<"Detergent: ";
			cin >> choice;
			str[x].detergent = detergent[(int)choice - 65];
			str[x].price += price_rate[(int)choice - 65];
			if (choice != 'A' && choice != 'B' && choice != 'C' && choice != 'D')
				cout << "\nError!\n";
		}while (choice != 'A' && choice != 'B' && choice != 'C' && choice != 'D');
	}
		
	cout << "\nDefault duration (minutes)       : 40" << endl 
		 << "Additional time (RM 0.50 / minutes): "; 
	cin >> str[x].duration;
	str[x].price += str[x].duration * addtime_rate;
	str[x].duration += 40;

		do
		{
			cout << "\nA = +++++++ (+RM 1.50)\nB = +++++   (+RM 1.00)\nC = +++     (+RM 0.50)\nD = +       (Free)" << endl 
				 <<"Temperature: ";
			cin >> choice;
			str[x].type = temperature[(int)choice - 65];
			str[x].price += price_rate[(int)choice - 65];
			if (choice != 'A' && choice != 'B' && choice != 'C' && choice != 'D')
				cout << "\nError!\n";
		}while (choice != 'A' && choice != 'B' && choice != 'C' && choice != 'D');

	cout << "\nTotal Price : RM " << fixed << setprecision(2) << str[x].price;
	str[x].start = "Pending";
}

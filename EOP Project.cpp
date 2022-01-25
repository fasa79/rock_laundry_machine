#include <iostream>
#include <iomanip>
#include <cstring>
#include <algorithm>
#include <windows.h>
#include <conio.h>
#include "input.h" //INPUT HEADER
using namespace std;

const int num = 6;

char option(); //SHOW MAIN MENU
void machineStatus (data *str, int index,int machine[num]); //SHOW AND UPDATE MACHINE STATUS
int searchData(int id, data *strwasher, data *strdryer, int sizewasher, int sizedryer); //SEARCH DATA
void startMachine (data *str, int index); //START PENDING MACHINE
void showMachine (int machine[num]); //SHOW ALL MACHINE STATUS
void displayAll(int repeat, data* str, char x); //DISPLAY ALL DATA
void receipt(data *str, int index); //DISPLAY SINGLE DATA
bool Menu(); //ASK USER TO RETURN TO MAIN MENU
bool machineCheck(int *machine); //CHECK AVAILABILITY OF MACHINE BEFORE DATA INPUT

int main()
{
	int countwash = 0, countdry = 0, id; //COUNT DATA ENTERED FOR WASH AND DRY
	char choice;
	int washmachine[num] = {0};
	int drymachine[num] = {0};
	
	data *washer;//declare structure as pointer
	data *dryer; //to save memory
	data *temp; //TEMPORARY MEMORY TO STORE DATA DURING ALLOCATION OF ACTUAL MEMORY (WASHER/DRYER)
	
	do
	{
		system ("cls");
		choice = option();
		
		if (choice == 'W')
		{
			if (machineCheck(washmachine))
			{
				cout << "All machine are currently in use.\n";
				Sleep (3000);
				continue;
			}
			temp = new data[countwash]; //ALLOCATE MEMORY
			copy (washer, washer + (countwash), temp); //COPY WASHER TO TEMPORARY (LINK IN GROUP)
			washer = new data[countwash + 1];
			washer[countwash].id = countwash + 1000; //ID GENERATOR
			machineStatus (washer, countwash, washmachine);
			input(washer, countwash, 'w');
			copy (temp, temp + countwash, washer);
			delete[] temp; //DELETE TEMPORARY MEMORY
			countwash++;
		}
		
		else if (choice == 'D')
		{
			if (machineCheck(drymachine))
			{
				cout << "All machine are currently in use.\n";
				Sleep (3000);
				continue;
			}
			temp = new data[countdry];
			copy (dryer, dryer + (countdry), temp);
			dryer = new data[countdry + 1];
			dryer[countdry].id = countdry + 5000;
			machineStatus (dryer, countdry, drymachine);
			input(dryer, countdry, 'x');
			copy (temp, temp + countdry, dryer);
			delete[] temp;
			countdry++;
		}
		
		else if (choice == 'S') //START MACHINE //ADD MACHINE STATUS ARRAY //BUG DETECTED
		{
			cout << "START MACHINE" << endl;
			cout << "Enter ID number: ";
			cin >> id;
			int index = searchData (id, washer, dryer, countwash, countdry);
			if(index >= 0)
			{
				if (id >=1000 && id < 5000)
				{
					if(washer[index].start == "Pending")
					{
						startMachine(washer, index);
						washmachine[(int)washer[index].machine - 65] = 0;
					}
					
					else
					cout << "\nClothes already processed!\n";
					
				}
					
				else
				{
					if(dryer[index].start == "Pending")
					{
						startMachine(dryer, index);
						drymachine[(int)dryer[index].machine - 65] = 0;
					}
					
					else
					cout << "\nClothes already processed!\n";
				}
			}
		}
		
		else if (choice == 'U')
		{
			cout << "UPDATE DATA" << endl;
			cout << "Enter ID number: ";
			cin >> id;
			int index = searchData (id, washer, dryer, countwash, countdry);
			if(index >= 0)
			{
				if (id >=1000 && id < 5000)
				{
					if (washer[index].start != "Done")
						input(washer, index, 'w');
						
					else
						cout << "The machine already processed the clothes.\n\n";
				}
					
				else
				{
					if (dryer[index].start != "Done")
						input(dryer, index, 'x');
						
					else
						cout << "The machine already processed the clothes.\n\n";
				}
			}
		}
		
		else if (choice == 'F') //FIND DATA
		{
			cout << "FIND YOUR DATA" << endl;
			cout << "Enter ID number: ";
			cin >> id;
			int index = searchData (id, washer, dryer, countwash, countdry);
		}
		
		else if (choice == 'A')
		{
			cout << "ALL DATA\n";
			cout << "\n\nWashing Machine\n\n";
			displayAll (countwash, washer, 'x');
			cout << "\n\nDrying Machine\n\n";
			displayAll (countdry, dryer, 'y');
		}
		
		else if (choice == 'M')
		{
			cout << "MACHINE STATUS\n\n";
			cout << "Washing Machine\n";
			showMachine (washmachine);
			cout << endl << endl << "Drying Machine\n";
			showMachine (drymachine);
		}
		
		else if (choice == 'X')
			break;
		
		else
			cout << "Error!\n\n";
			
	}while(Menu());
	
	return 0;
}

int searchData(int id, data *strwasher, data *strdryer, int sizewasher, int sizedryer) //SEARCH SPECIFIC DATA USING ID NUMBER AND DELETE DATA
{
	int index = -1;
	char choice;

	for (int x = 0 ; x < sizewasher ; x++)
	{
		if (strwasher[x].id == id)
		{
			index = x;
			receipt(strwasher, index);
		}			
	}
	
	for (int x = 0 ; x < sizedryer ; x++)
	{
		if (strdryer[x].id == id)
		{
			index = x;
			receipt(strdryer, index);
		}
	}
	
	if (index < 0)
		cout << "Your search not found.";
	
	if (index >= 0)
	{
		do
		{
			cout << "\n\nIs this your data? (Y-Yes / X-No)\n";
			cin >> choice;
			
			if (choice != 'Y' && choice != 'X')
				cout << "Error!\n";
				
		}while(choice != 'Y' && choice != 'X');
		
		if (choice == 'X')
			return -1;
	}	
		
	return index;
}

void startMachine (data *str, int index)
{
	if (index >= 0)
	{
		system ("cls");
	
		cout << "Machine Processing...";
		for (int i = 0 ; i <= 100 ; i++)
		{
			cout << setw(3) << i << '%';
			Sleep (100);
			cout << "\b\b\b\b";
		}
		cout << "\nComplete!\n";
		str[index].start = "Done";
	}
}

void displayAll(int repeat, data* str, char w) //DISPLAY ALL DATA (COMPLETED)
{	
	cout << setw(6) << left << "ID"
		 << setw(12) << left << "Weight(kg)";
	if (w == 'x')
		cout << setw(11) << left << "Detergent";
	cout << setw(10) << left << "Duration"
		 << setw(13) << left << "Temperature"
		 << setw(11) << left << "Price(RM)" 
		 << setw(9) << left << "Machine"
		 << setw(9) << left <<"Process" << endl;
	for (int x = 0 ; x < repeat ; x++)
	{
		cout << setw(6) << left << str[x].id
			 << setw(12) << left << str[x].weight;
		if (w == 'x')
			cout << setw(11) << left << str[x].detergent;
		cout << setw(10) << left << str[x].duration
			 << setw(13) << left << str[x].type
			 << setw(11) << left << fixed << setprecision(2) << str[x].price
			 << setw(9) << left << str[x].machine
			 << setw(9) << left << str[x].start << endl;
	}
	
}

void receipt(data *str, int index) //PRINT RECEIPT BY ACCEPT ID NUMBER ARGUMENT
{
	cout << "ID Number  : " << str[index].id << endl
		 << "Weight(kg) : " << str[index].weight << endl
		 << "Detergent  : " << str[index].detergent << endl
		 << "Duration   : " << str[index].duration << " minutes" << endl
		 << "Temperature: " << str[index].type << endl
		 << "Machine    : " << str[index].machine << endl
		 << "Total Price: RM " << fixed << setprecision(2) << str[index].price << endl
		 << "Tokens     : " << fixed << setprecision(0) << (int)str[index].price/0.5 << " pieces" << endl;
}

void machineStatus (data *str, int index,int machine[num])
{
	char choice;
	int idx_choice;
	bool end;
	do
	{
		end = false;
		cout << "Machine |" << "  A  |  B  |  C  |  D  |  E  |  F  | (Machine with ID is loaded)\nID      |";
		for (int x = 0 ; x < num ; x++)
			cout << setw(4) << machine[x] << " |";
			
		cout << endl << "Choose your machine: ";
		cin >> choice;
		str[index].machine = choice;
		idx_choice = (int)choice - 65;
		
		if (machine[idx_choice] != 0)
		{
			system ("cls");
			cout << "Machine chosen is loaded. Choose another machine.\n";
			end = true;;
		}
		
		if(choice != 'A' && choice != 'B' && choice != 'C' && choice != 'D' && choice != 'E' && choice != 'F')
		{
			system("cls");
			cout << "Error!\n\n";
			end = true;
		}
	}while(end);
	 
	 machine[idx_choice] = str[index].id;
	}

void showMachine (int machine[num])
{
	cout << "Machine |" << "  A  |  B  |  C  |  D  |  E  |  F  | (Machine with ID is loaded)\nID      |";
		for (int x = 0 ; x < num ; x++)
			cout << setw(4) << machine[x] << " |";
}

char option() // DISPLAY MENU OPTION
{
	char choice;
	cout << "W-Wash               D-Dry            S-Start Machine      U-Update\n\nM-Machines Status    F-Find Data      A-Display All        X-Exit App\n\n"; // PUT NOTES
	cout << "Enter an option: ";
	cin >> choice;
	system ("cls");
	
	return choice;
}

bool Menu() // ASK USER TO GO TO MAIN MENU
{
	
	char choice;
	bool end = false;
	
	do
	{
		cout << "\n\nReturn to Main Menu? (Y - Yes / X - No)" << endl;
		choice = getch();
		
		if (choice == 'Y')
			return true;
		
		else if (choice == 'X')
			return false;
			
		else
		{
			cout << "Error!";
			end = true;
		}
	}while(end);
}

bool machineCheck(int *machine)
{
	for (int x = 0 ; x < num ; x++)
		if (machine[x] == 0)
			return false;
	
	return true;
}

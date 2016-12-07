#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <cmath>
#include <vector>
#include "Zedboard.h"
using namespace std;

int Run(Zedboard z, int states[]);
int CalcTotal(vector<int> inputs, vector<int> operations);

int main()
{
// Initialize
	Zedboard z;
	int states[5];
	int total;

	// Display instructions
	cout << "Use switches to select numbers\n";
	cout << "Use push buttons to perform operations: \n";
	cout << "- left for addition \n";
	cout << "- right for subtraction\n";
	cout << "- up for multiplicaton\n";
	cout << "- down for division\n";
	cout << "- center tomfor result\n\n";

	char response = 'y';
	while (response == 'y')
	{

		// Initial state of pushbuttons
		for (int i = 0; i < 5; i++)
		{
			states[i] = z.RegisterRead(gpio_pbtnl_offset + 4*i);
		}
		// Initialize LEDs to 0
		z.SetLedNumber(0);

		// Run application once
		total = Run(z, states);
		z.SetLedNumber(total);

		cout << "\nRun again? y/n: ";
		cin >> response;
	}
}

//run calculator
int Run(Zedboard z, int states[])
{
	int switch_value = 0;
	int button = 0;
	int total;
	int toggle_value = 0;
	vector<int> inputs; //vector to store input numbers
	vector<int> operations; //vector to store operations

	while (true)
	{
		//set LEDs to display current switch value
		for (int i = 0; i <= 7; i++)
		{
			value = z.RegisterRead(gpio_sw1_offset + 4*i);
			z.RegisterWrite(gpio_led1_offset + 4*i, value);
		}

		//get pressed button
		button = z.PushButtonGet(states);

		if (button != 0)
		{
			// read switches
			for (int i = 0; i < 8; i++)
			{
				switch_value += z.RegisterRead(gpio_sw1_offset + 4*i) * pow(2,i);
			}

			if (button == 5) //center pressed
			{
				inputs.push_back(switch_value);
				cout << switch_value;
				total = CalcTotal(inputs, operations);
				cout << "\n= " << total << endl;
				return total;
			}
			else //append value and operations,
			{
				inputs.push_back(switch_value);
				operations.push_back(button);

				//show calculations to user
				switch(button)
				{
					case 1: //addition
						cout << switch_value << "\n+ ";
						break;
					case 2: //subtraction
						cout << switch_value << "\n- ";
						break;
					case 3: //multiplication
						cout << switch_value << "\n* ";
						break;
					case 4: //division
						cout << switch_value << "\n/ ";
						break;
				}
				// reset input value
				switch_value = 0;
			}
		}
	}
}

//applies operations to inputs to get final value
int CalcTotal(vector<int> inputs, vector<int> operations)
{
	int total = inputs[0];
	int length = inputs.size();
	int button;

	// perform operations
	for (int i = 1; i < length; i++)
	{
		button = operations[i - 1];
		switch(button)
		{
			case 1: //addition
				total += inputs[i];
				break;
			case 2: //subtraction
				total -= inputs[i];
				break;
			case 3: //multiplication
				total *= inputs[i];
				break;
			case 4: //division
				total /= inputs[i];
				break;
		}
	}
	return total;
}

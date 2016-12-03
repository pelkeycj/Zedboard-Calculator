#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <cmath>
#include "Zedboard.h"
using namespace std;

void Run(Zedboard z, int states[]);

int main()
{
// Initialize Zedboard
	Zedboard z;

	// Display instructions
	cout << "Use switches to select numbers\n";
	cout << "Use push buttons to perform operations: \n";
	cout << "- left for addition \n";
	cout << "- right for subtraction\n";
	cout << "- up for multiplicaton\n";
	cout << "- down for division\n";
	cout << "- center for result\n\n";

	char response = 'y';
	while (response == 'y')
	{
		// Initial state of pushbuttons set to 0
		int states[5];
		for (int i = 0; i < 5; i++)
		{
			states[i] = 0;
		}

		// Initialize LEDs to 0
		z.SetLedNumber(0);

		// Run application once
		Run(z, states);

		cout << "\nRun again? y/n: ";
		cin >> response;
	}
}

void Run(Zedboard z, int states[])
{
	bool centerPushed = false;
	int total = 0;
	bool first_num = true;
	int switch_value = 0;
	int button = 0;

	while (!centerPushed)
	{
		// get pressed button
		button = z.PushButtonGet(states);
		if (button != 0)
		{
			// read switches
			switch_value += z.RegisterRead(gpio_sw1_offset) * pow(2,0);
			switch_value += z.RegisterRead(gpio_sw2_offset) * pow(2,1);
			switch_value += z.RegisterRead(gpio_sw3_offset) * pow(2,2);
			switch_value += z.RegisterRead(gpio_sw4_offset) * pow(2,3);
			switch_value += z.RegisterRead(gpio_sw5_offset) * pow(2,4);
			switch_value += z.RegisterRead(gpio_sw6_offset) * pow(2,5);
			switch_value += z.RegisterRead(gpio_sw7_offset) * pow(2,6);
			switch_value += z.RegisterRead(gpio_sw8_offset) * pow(2,7);

			if (first_num) //handle first number being entered
			{
				total += switch_value;
				first_num = false;
				cout << total << endl;
			}
			else
			{
				//perform operation
				switch(button)
				{
					case 1: //left button -> addition
						cout << "+ " << switch_value << endl;
						total += switch_value;
						switch_value = 0;
						break;
					case 2: //right button -> subtraction
						cout << "- " << switch_value << endl;
						total -= switch_value;
						switch_value = 0;
						break;
					case 3: //up button -> multiplication
						cout << "* " << switch_value << endl;
						total *= switch_value;
						switch_value = 0;
						break;
					case 4: //down button -> division
						cout << "/ " << switch_value << endl;
						total /= switch_value;
						switch_value = 0;
						break;
					case 5: // center button -> equals
						cout << "= " << total << endl << endl;
						centerPushed = true;
						z.SetLedNumber(total);
						break;
				}
			}
		}
	}
}

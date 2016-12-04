#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <cmath>
#include "Zedboard.h"
using namespace std;

int Run(Zedboard z, int states[]);

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
		// Run application once
		total = Run(z, states);
		z.SetLedNumber(total);

		cout << "\nRun again? y/n: ";
		cin >> response;
	}
}


int Run(Zedboard z, int states[])
{
	int switch_value = 0;
	int button = 0;

	// Initial state of pushbuttons set to 0
	for (int i = 0; i < 5; i++)
	{
		states[i] = 0;
	}
	// Initialize LEDs to 0
	z.SetLedNumber(0);


	while (true)
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

			//perform operation
			switch(button)
			{
				case 1: //left button -> addition
					cout << switch_value << "\n+ ";
					return switch_value + Run(z, states);
					break;
				case 2: //right button -> subtraction
					cout << switch_value << "\n- ";
					return switch_value - Run(z, states);
					break;
				case 3: //up button -> multiplication
					cout << switch_value << "\n* ";
					return switch_value * Run(z, states);
					break;
				case 4: //down button -> division
					cout << "/ " << switch_value << "\n/ ";
					return switch_value / Run(z, states);
					break;
				case 5: // center button -> equals
					cout << switch_value << endl << endl;
					return switch_value;
					break;
			}
		}
	}
}

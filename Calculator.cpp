#include <iostream>
//#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <cmath>
#include "Zedboard.h"
using namespace std;

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
	cout << " -center for result\n\n";

	char response = 'y'
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
		Run(z);

/*	for (int i = 0; i < 5; i++)
	{
		states[i] = z.RegisterRead(gpio_pbtnl_offset + 4*i);
	}

	for (int i = 0; i < 8; i++)
	{
		led_value += z.RegisterRead(gpio_led1_offset + 4*i) * pow(2,i);
	}

		int value = 0;
		int reset_value = 0;

		bool buttonPressed = false;
		int num1 = 0;
		int num2 = 0;
		int total = 0;
		int nums = 0;
		int final = 0;

		while (true)
		{
			nums = 0;
			buttonPressed = false;
			// Read user input
			while(nums < 2)
			{
				// read switches and display using LEDs
				for (int i = 0; i <= 7; i++)
				{
					value = z.RegisterRead(gpio_sw1_offset + 4*i);
					z.RegisterWrite(gpio_led1_offset + 4*i, value);
				}
				//
				if (z.PushButtonGet(states) == 5) // Button Center Pushed
				{
					nums++;
					led_value = 0;

					led_value += z.RegisterRead(gpio_sw1_offset) * pow(2,0);
					cout << "sw1 status: " << z.RegisterRead(gpio_sw1_offset) << endl;
					led_value += z.RegisterRead(gpio_sw2_offset) * pow(2,1);
					led_value += z.RegisterRead(gpio_sw3_offset) * pow(2,2);
					led_value += z.RegisterRead(gpio_sw4_offset) * pow(2,3);
					led_value += z.RegisterRead(gpio_sw5_offset) * pow(2,4);
					led_value += z.RegisterRead(gpio_sw6_offset) * pow(2,5);
					led_value += z.RegisterRead(gpio_sw7_offset) * pow(2,6);
					led_value += z.RegisterRead(gpio_sw8_offset) * pow(2,7);
					if (nums == 1)
					{
						num1 = led_value;
						cout << "Center Button Pressed: Num" << nums << " = " << num1 << endl;
					}
					else
					{
						num2 = led_value;
						cout << "Center Button Pressed: Num" << nums << " = " << num2 << endl;
					}
				}
			}
			cout << "Now Both Numbers Have Been Entered" << endl;
			final = 0;
			while (!buttonPressed)
			{
				for (int i = 0; i < 5; i++)
				{
					value = z.PushButtonGet(states);
					switch(value)
					{
						case 1:	// Button Left pushed
							final = num1 + num2;
							cout << num1 << " + " << num2 << " = " << final << endl;
							z.SetLedNumber(final);
							buttonPressed = true;
							break;
						case 2: // Button Right pushed
							final = num1 - num2;
							cout << num1 << " - " << num2 << " = " << final << endl;
							z.SetLedNumber(final);
							buttonPressed = true;
							break;
						case 3: // Button Up pushed
							final = num1 * num2;
							cout << num1 << " * " << num2 << " = " << final << endl;
							z.SetLedNumber(final);
							buttonPressed = true;
							break;
						case 4: // Button Down pushed
							final = num1 / num2;
							cout << num1 << " / " << num2 << " = " << final << endl;
							z.SetLedNumber(final);
							buttonPressed = true;
							break;
						case 5: // Button Center Pushed
							cout << "Please press one of the other 4 buttons" << endl;
							break;
					}
				}
			}
		}
		*/
		cout << "\nRun again? y/n: ";
		cin >> response
	}
}

void Run(Zedboard z)
{
	bool centerPushed = false;
	int total = 0;
	int number_count = 0;
	int switch_value = 0;

	// while !centerPushed :::
	// read button states
	// if button pressed != center , read number from switches
	//	if first number being entered
	//		if multiplication or division
	//    	set total to 1 and perform operation using switch_value
	// 		else add/subtract switch_value from total
	//	else perform operation on total using switch_value
	// add 1 to number count, reset switch_value to 0
	// if center pushed
	// display total on leds,
	// return
}

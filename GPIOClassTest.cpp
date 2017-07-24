#include "GPIO.h"
#include <iostream>
#include <unistd.h>

int main (void)
{
 
	auto inputstate = PinValue::Low;
	int i = 0;
	auto gpio4 = GPIO{4}; //create new GPIO object to be attached to  GPIO4
	auto gpio17 = GPIO{17}; //create new GPIO object to be attached to  GPIO17
 
	std::cout << " GPIO pins exported" << std::endl;
 
	gpio17.setDirection(Direction::In); //GPIO4 set to input
	gpio4.setDirection(Direction::Out); // GPIO17 set to output
 
	std::cout << " Set GPIO pin directions" << std::endl;
 
	while(i < 20)
	{
		usleep(500000);  // wait for 0.5 seconds
		inputstate = gpio17.getValue(); //read state of GPIO17 input pin
		std::cout << "Current input pin state is " << inputstate  << std::endl;
		if(inputstate == PinValue::Low) // if input pin is at state "0" i.e. button pressed
		{
			std::cout << "input pin state is \"Pressed \".n Will check input pin state again in 20ms "<<std::endl;
			usleep(20000);
			std::cout << "Checking again ....." << std::endl;
			inputstate = gpio17.getValue(); // checking again to ensure that state "0" is due to button press and not noise
			if(inputstate == PinValue::Low)
			{
				std::cout << "input pin state is definitely \"Pressed\". Turning LED ON" <<std::endl;
				gpio4.setValue(PinValue::High); // turn LED ON 
				std::cout << " Waiting until pin is unpressed....." << std::endl;
				while (inputstate == PinValue::Low){ // ehhhhh i know this is a test but ehhhhh
					inputstate = gpio17.getValue();
				};
				std::cout << "pin is unpressed" << std::endl;
 
			}
			else
				std::cout << "input pin state is definitely \"UnPressed\". That was just noise." <<std::endl;
 
		}
		gpio4.setValue(PinValue::Low);
		i++;
	}
        
	return 0;
}

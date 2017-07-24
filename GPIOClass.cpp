#include "GPIOClass.h"
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

GPIOClass::GPIOClass(int const pin):valuefd(-1),
				    directionfd(-1),
				    exportfd(-1),
				    unexportfd(-1),
				    _pin(pin) {
	this->export_gpio();
}

GPIOClass::~GPIOClass() {
	this->unexport_gpio();
}

auto GPIOClass::export_gpio() -> int {
	int statusVal = -1;
	string exportStr = "/sys/class/gpio/export";
	auto const exportfd = statusVal = open(exportStr.c_str(),  O_WRONLY|O_SYNC);
	if (statusVal < 0){
		perror("could not open SYSFS GPIO export device");
		exit(1);
	}
	
	auto const numStr = std::to_string(this->_pin);
	statusVal = write(exportfd, numStr.c_str(), numStr.length());
	if (statusVal < 0){
		perror("could not write to SYSFS GPIO export device");
		exit(1);
	}
	
	statusVal = close(exportfd);
	if (statusVal < 0){
		perror("could not close SYSFS GPIO export device");
		exit(1);
	}

	return statusVal;
}

auto GPIOClass::unexport_gpio() -> int {
	int statusVal = -1;
	string unexportStr = "/sys/class/gpio/unexport";
	auto const unexportfd = statusVal = open(unexportStr.c_str(),  O_WRONLY|O_SYNC);
	if (statusVal < 0){
		perror("could not open SYSFS GPIO unexport device");
		exit(1);
	}

	auto const numStr = std::to_string(this->_pin);
	statusVal = write(unexportfd, numStr.c_str(), numStr.length());
	if (statusVal < 0){
		perror("could not write to SYSFS GPIO unexport device");
		exit(1);
	}
	
	statusVal = close(unexportfd);
	if (statusVal < 0){
		perror("could not close SYSFS GPIO unexport device");
		exit(1);
	}
	
	return statusVal;
}

auto GPIOClass::setdir_gpio(Direction const direction dir) -> int {
	int statusVal = -1;
	string setdirStr ="/sys/class/gpio/gpio" + std::to_string(this->_pin) + "/direction";	
	
	auto const directionfd = statusVal = open(setdirStr.c_str(), O_WRONLY|O_SYNC); // open direction file for gpio
	if (statusVal < 0){
		perror("could not open SYSFS GPIO direction device");
		exit(1);
	}
		
	if (dir.compare("in") != 0 && dir.compare("out") != 0 ) {
		fprintf(stderr, "Invalid direction value. Should be \"in\" or \"out\". \n");
		exit(1);
	}
		
	statusVal = write(directionfd, dir.c_str(), dir.length());
	if (statusVal < 0){
		perror("could not write to SYSFS GPIO direction device");
		exit(1);
	}
	
	statusVal = close(directionfd);
	if (statusVal < 0){
		perror("could not close SYSFS GPIO direction device");
		exit(1);
	}

	return statusVal;
}


auto GPIOClass::setValue(bool const bval) -> int
{

	int statusVal = -1;
	string setValStr = "/sys/class/gpio/gpio" + std::to_string(this->_pin) + "/value";
	
	auto const valuefd = statusVal = open(setValStr.c_str(), O_WRONLY|O_SYNC);
	if (statusVal < 0){
		perror("could not open SYSFS GPIO value device");
		exit(1);
	}
	auto const val = std::to_string(bval);
	if (val.compare("1") != 0 && val.compare("0") != 0 ) {
		fprintf(stderr, "Invalid  value. Should be \"1\" or \"0\". \n");
		exit(1);
	}
		
	statusVal = write(valuefd, val.c_str(), val.length());
	if (statusVal < 0){
		perror("could not write to SYSFS GPIO value device");
		exit(1);
	}
	
	statusVal = close(valuefd);
	if (statusVal < 0){
		perror("could not close SYSFS GPIO value device");
		exit(1);
	}

	return statusVal;
}

auto GPIOClass::getValue() const -> bool {
	string getValStr = "/sys/class/gpio/gpio" + std::to_string(this->_pin) + "/value";
	char buff[10];
	auto statusVal = false;
	valuefd = statusVal = open(getValStr.c_str(), O_RDONLY|O_SYNC);
	if (statusVal < 0){
		perror("could not open SYSFS GPIO value device");
		exit(1);
	}

	statusVal = read(valuefd, &buff, 1);
	if (statusVal < 0){
		perror("could not read SYSFS GPIO value device");
		exit(1);
	}
	
	buff[1]='\0';
	
	val = string(buff);
	
	if (val.compare("1") != 0 && val.compare("0") != 0 ) {
		fprintf(stderr, "Invalid  value read. Should be \"1\" or \"0\". \n");
		exit(1);
	}
	
	statusVal = close(valuefd);
	if (statusVal < 0){
		perror("could not close SYSFS GPIO value device");
		exit(1);
	}

	return statusVal;
}

auto GPIOClass::getPin() -> int{
	return this->_pin;
}

#pragma once
#include <string>
//#include <unistd.h>
//#include <errno.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <sys/types.h>
//#include <sys/stat.h>
//#include <fcntl.h>

/* GPIO Class
 * Purpose: Each object instatiated from this class will control a GPIO pin
 * The GPIO pin number must be passed to the overloaded class constructor
 */
final class GPIOClass
{
public:
  GPIOClass(int pin);
  ~GPIOClass();
  auto setDirection(std::string dir) -> int;
  auto setHigh(bool high = true) -> int;
  auto getvalue() const -> bool;
  auto getPin() const -> int;
private:
  int export_gpio();
  int unexport_gpio();
	
  int valuefd;
  int directionfd;
  int exportfd;
  int unexportfd;
  int const _pin;	
};


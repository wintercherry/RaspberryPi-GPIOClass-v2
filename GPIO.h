#pragma once
#include <string>

/* GPIO Class
 * Purpose: Each object instatiated from this class will control a GPIO pin
 * The GPIO pin number must be passed to the overloaded class constructor
 */


// todo: would be nice if there were a way to save the state of all pins
// and then push that state back on exit. i believe the python gpio interface
// has a cleanup method that does this but i could be mistaken

enum class Direction { In, Out };
enum class PinValue { High, Low };

std::ostream& operator<<(std::ostream&, Direction);
std::ostream& operator<<(std::ostream&, PinValue);

class GPIO final
{
public:
  GPIO(int pin);
  ~GPIO();
  auto setDirection(Direction) -> int;
  auto getDirection() const -> Direction;
  auto setValue(PinValue) -> int;
  auto getValue() const -> PinValue;
  auto getPin() const -> int;
private:
  int export_gpio();
  int unexport_gpio();
  int const _pin;	
};


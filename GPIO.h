#pragma once
#include <string>

/* GPIO Class
 * Purpose: Each object instatiated from this class will control a GPIO pin
 * The GPIO pin number must be passed to the overloaded class constructor
 */

enum class Direction { In, Out };
enum class PinValue { High, Low };

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


#pragma once
#include "Mux.h"

/**
* So the wiring for buttons:
*  A0-A3 are high pullup inputs
*  A4-A7,B0-B7 are outputs, high by default.
* This provides a 4x12 virtual button matrix.
* Reading the buttons is a loop, iterating over the 12 outputs, putting one of them low in each cycle,
* then reading the inputs. If a button there is pressed, the input will read LOW.
*
* The names of button groups:
*  * NL - numpad left, NL_0...NL_9, NL_STAR (10), NL_HASH (11)
*  * NR - numpad right
*  * CS - central switches (2 rows x 4 columns), CS_0...CS_7 (to right and down, as we read)
*  * PL - pushbuttons left up (4 rows x 2 columns) PL_0...PL_7 (to right and down, as we read)
*  * PR - pushbuttons right up (4 rows x 2 columns)
*
* Wiring of outputs:
*  * A4-A5 - PL, pushbuttons left up
*  * A6-A7 - PR, pushbutons right
*  * B0-B2 - NL numpad left
*  * B3-B5 - NR numpad right
*  * B6-B7 - CS central switches
*
* An button coordinate is a 8 bit number, the high 4 bits give the button group,
* the lower 4 bits give the number in series, thus
*   NL_HASH = 0x2B;
*   CS_4 = 0x44;
*
*/
enum ButtonGroup { PL, PR, NL, NR, CS };
class Buttons {
private:
	byte previousButtonState[12] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	byte buttonGroupDecode [12] = { PL, PL, PR, PR, NL, NL, NL, NR, NR, NR, CS, CS};
	Multiplexer * mux = new Multiplexer();
public:
	void setup();
	short read();
};

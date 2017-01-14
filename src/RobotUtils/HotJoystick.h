#ifndef SRC_HOTJOYSTICK_H_
#define SRC_HOTJOYSTICK_H_

#include <RobotUtils/HotBot.h>
#include "WPILib.h"

class HotBot;

class HotJoystick: public Joystick {
public:
	/******************************
	 * 	Access Selector
	 ******************************/
	typedef enum {
		kButtonA = 1 << 0,
		kButtonB = 1 << 1,
		kButtonX = 1 << 2,
		kButtonY = 1 << 3,
		kButtonLB = 1 << 4,
		kButtonRB = 1 << 5,
		kButtonBack = 1 << 6,
		kButtonStart = 1 << 7,
		kButtonL3 = 1 << 8,
		kButtonR3 = 1 << 9,

		/**
		 * 	Next Two:
		 * 		Using triggers as buttons (good for shooting)
		 * 		These buttons are on if the triggers are pressed more than 40%
		 */
		kButtonLT = 1 << 10,
		kButtonRT = 1 << 11
	} kButton;

	typedef enum {
		kAxisLX = 1 << 0,
		kAxisLY = 1 << 1,
		kAxisLT = 1 << 2,	//	Left Trigger
		kAxisRT = 1 << 3,	//	Right Trigger
		kAxisRX = 1 << 4,
		kAxisRY = 1 << 5,
		kAxisALL = 0xFF
	} kAxis;

	/******************************
	 * 	Constructor
	 ******************************/
	HotJoystick(unsigned int port);

	/******************************
	 * 	HotJoystick
	 ******************************/
	/**
	 * 	Set Deadband
	 */
	void SetDeadband(int channels, float value);

	/**
	 * 	Get Deadband
	 */
	float GetDeadband(kAxis axis);

	/******************************
	 * 	Access with Access Selector
	 ******************************/
	/**
	 * 	Simply Access Button with Access Selector
	 */
	bool Button(kButton btn);

	/**
	 * 	Combined Button Access
	 */
	bool Button(int btns);

	/**
	 * 	Simply Access Axis With Access Selector
	 */
	float Axis(kAxis axis);


	/**
	 * 	Access Button Press
	 * 		This function only return true when a button is newly pressed
	 * 		Whole the button is pressed, this function returns false
	 */
	bool ButtonPressed(kButton btn);

	/**
	 * 	Combined Button Pressed
	 */
	bool ButtonPressed(int btns);

	/******************************
	 * 	Access Individual
	 ******************************/
	/**
	 * 	Button
	 */
	bool ButtonA() { return Button(kButtonA); }
	bool ButtonB() { return Button(kButtonB); }
	bool ButtonX() { return Button(kButtonX); }
	bool ButtonY() { return Button(kButtonY); }
	bool ButtonLB() { return Button(kButtonLB); }
	bool ButtonRB() { return Button(kButtonRB); }
	bool ButtonBack() { return Button(kButtonBack); }
	bool ButtonStart() { return Button(kButtonStart); }
	bool ButtonL3() { return Button(kButtonL3); }
	bool ButtonR3() { return Button(kButtonR3); }
	bool ButtonLT() { return Button(kButtonLT); }
	bool ButtonRT() { return Button(kButtonRT); }

	/**
	 * 	Button Pressed
	 */
	bool ButtonPressedA() { return ButtonPressed(kButtonA); }
	bool ButtonPressedB() { return ButtonPressed(kButtonB); }
	bool ButtonPressedX() { return ButtonPressed(kButtonX); }
	bool ButtonPressedY() { return ButtonPressed(kButtonY); }
	bool ButtonPressedLB() { return ButtonPressed(kButtonLB); }
	bool ButtonPressedRB() { return ButtonPressed(kButtonRB); }
	bool ButtonPressedStart() { return ButtonPressed(kButtonStart); }
	bool ButtonPressedBack() { return ButtonPressed(kButtonBack); }
	bool ButtonPressedL3() { return ButtonPressed(kButtonL3); }
	bool ButtonPressedR3() { return ButtonPressed(kButtonR3); }
	bool ButtonPressedLT() { return ButtonPressed(kButtonLT); }
	bool ButtonPressedRT() { return ButtonPressed(kButtonRT); }

	/**
	 * 	Axis
	 */
	float AxisLX() { return Axis(kAxisLX); }
	float AxisLY() { return Axis(kAxisLY); }
	float AxisRX() { return Axis(kAxisRX); }
	float AxisRY() { return Axis(kAxisRY); }
	float AxisLT() { return Axis(kAxisLT); }
	float AxisRT() { return Axis(kAxisRT); }
private:

	bool f_A, f_B, f_X, f_Y, f_LB, f_RB, f_Back, f_Start, f_L3, f_R3, f_LT, f_RT;
	float db_LX, db_LY, db_LT, db_RT, db_RX, db_RY;
};

#endif /* SRC_HOTJOYSTICK_H_ */

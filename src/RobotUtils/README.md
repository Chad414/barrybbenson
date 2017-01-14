# RobotUtils

This is a series of classes written by Team 67 that enhance the functionality of WPILib.

This library is unfinished as of yet. This list will be updated as new functionality is added to it, and once everything is present, the wiki will be updated with reference on the library.

## Features

* HotBot
  * Base class of robot
  * Instead of inheriting IterativeRobot, inherit this class
* HotSubsystem
  * Base class of subsystem of robot
  * Contain periodic/init functions such as `InitRobot`, `TeleopPeriod`
* HotJoystick
  * Wrapper class of Joystick
  * Specialized for xbox controller
  * Detect button press
  * Trigger as button
* HotPIDController
  * Wrapper for PIDController
  * Log basic data automatically, including input/output value, PID coefficients, setpoints, etc...


## Details
### HotBot

Base class that extends `IterativeRobot`.
Main robot class should inherit this class
This is also replacement of `HotSubsystemHandler`.
To register a subsystem, you can just initialize the subsystem with parameter `HotBot*`.

Also, to handle all routines, routine functions are renamed.
- `RobotInit` -> `BeforeRobot`
- `DisabledInit` -> `BeforeDisabled`
- `AutonomousInit` -> `BeforeAuton`
- `TeleopInit` -> `BeforeTeleop`
- `TestInit` -> `BeforeTest`
- `DisabledPeriodic` -> `DisabledPeriod`
- `AutonomousPeriodic` -> `AutonPeriod`
- `TeleopPeriodic` -> `TeleopPeriod`
- `TestPeriodic` -> `TestPeriod`

To handle more general routines, new function called `GeneralPeriod` is added.  This function runs in every mode.

### HotSubsystem

Base class for subsystem.
As soon as this class is instantiated, this subsystem is set as subsystem of parent HotBot class.

`HotSubsystem` has routine functions that are name the same way with `HotBot`.
These function works same way with the `HotBot`.  (the order that each subsystem is called is not specified)
They are for background computation (checking the status of the subsystem, etc...)

### HotJoystick

Wrapper of Joystick specified for xbox controller.
This class extends `Joystick` of WPILib.
In addition to normation `Joystick` functionalities, we have:
- `void SetDeadband(float)`
- `bool Button**()` where ** is name of button.
- `bool ButtonPressed**()` where ** is name of button
- `float Axis**()` where ** is name of axis

### HotPIDController

Wrapper of PIDController.
Easy access to PID coefficients, dynamic PID Control.


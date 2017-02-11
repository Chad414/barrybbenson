
#ifndef SRC_HOTPIDCONTROLLER_H_
#define SRC_HOTPIDCONTROLLER_H_

#include "WPILib.h"


class HotPIDController: public PIDController {
public:
	HotPIDController(float p, float i, float d, PIDSource *source, PIDOutput *output, float period = 0.05);
	HotPIDController(float p, float i, float d, float f, PIDSource *source, PIDOutput *output, float period = 0.05);

	/******************************
	 * 	Configuration
	 ******************************/
	/******************************
	 * 	Enable/Disable
	 ******************************/
	/**
	 * 	Enable PID if it is not enabled
	 */
	void Enable();

	/**
	 * 	Disabled PID if it is enabled
	 */
	void Disable();

	/******************************
	 * 	Set Set Point
	 ******************************/
	void SetSetpoint(float setpoint, bool enable=false);

	/******************************
	 * 	Get Input/Output Value
	 ******************************/
	double GetInput() const;
	double GetOutput() const;

	/******************************
	 * 	Control P/I/D
	 ******************************/
	/**
	 * 	Get Default PID
	 */
	float GetDefP();
	float GetDefI();
	float GetDefD();

	/**
	 * 	Modify PID
	 * 		These are tmp configuration,
	 * 		as soon as any new value is set, or Update() function is called,
	 * 		These values are eliminated and may not be recalled.
	 */
	void SetP(float p);
	void SetI(float i);
	void SetD(float d);

	/**
	 * 	Modify Default PID
	 * 		These function should not be called;
	 * 		default value of PID should be set in constructor and
	 * 		most likely you should not change the value.
	 */
	void SetDefPID(float p, float i, float d);
	void SetDefP(float p);
	void SetDefI(float i);
	void SetDefD(float d);

	/**
	 * 	Reset PID Value To Default
	 */
	void ResetToDefPID();

	/**
	 * 	Set Dynamic PID
	 */
	void DynamicPID(float range, float p, float i, float d);

	/**
	 * 	Update Dynamic PID Value
	 */
	void Update();

private:
	/**
	 * 	PIDSource
	 */
	PIDSource* m_source;

	/**
	 * 	Default PID Value
	 */
	float def_p, def_i, def_d;

	/**
	 * 	Dynamic PID
	 */
	class PIDCoef {
	public:
		PIDCoef(float p, float i, float d) {
			m_p = p;
			m_i = i;
			m_d = d;
		}

		float GetP() { return m_p; }
		float GetI() { return m_i; }
		float GetD() { return m_d; }

	private:
		float m_p, m_i, m_d;
	};

	std::map<float, PIDCoef*> m_dynamicPIDs;
};

#endif /* SRC_HOTPIDCONTROLLER_H_ */

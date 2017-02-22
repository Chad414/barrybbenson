#include "WPILib.h"
#include "RobotUtils/RobotUtils.h"
#include "CANTalon.h"
#include "MotionProfileExample.h"

#define L_P 0.001
#define L_I 0.00
#define L_D 0.0
#define L_FF 0.8234

#define R_P 0.00
#define R_I 0.00
#define R_D 0.0
#define R_FF 0.8214



class barrybbenson: public HotBot {
private:
//	CANTalon* m_LF;
	CANTalon* m_LR;
	CANTalon* m_RF;
	CANTalon* m_RR;

	double L_error_rpm, R_error_rpm, speed_pctVbus;
	double L_PID_P, L_PID_I, L_PID_D, L_PID_FF, L_PID_Position, L_PID_Speed, L_PID_Error, L_PID_Setpoint;
	double R_PID_P, R_PID_I, R_PID_D, R_PID_FF, R_PID_Position, R_PID_Speed, R_PID_Error, R_PID_Setpoint;
	double LF_PID_Current, LR_PID_Current, RF_PID_Current, RR_PID_Current;

	double count = 0;


public:
	/** The Talon we want to motion profile. */
	CANTalon m_LF;

	/** some example logic on how one can manage an MP */
	MotionProfileExample _example;
	barrybbenson() : m_LF(11), _example(m_LF) {

		/* Left Front Motor */
		m_LF.SetFeedbackDevice(CANTalon::QuadEncoder);
		//m_LF->SetControlMode(CANTalon::kSpeed);
		m_LF.SetControlMode(CANTalon::kMotionProfile);
		m_LF.SelectProfileSlot(1);
		//m_LF->SetControlMode(CANTalon::kPercentVbus);
		m_LF.ConfigEncoderCodesPerRev(256*1.4);
		m_LF.SelectProfileSlot(1);
		m_LF.SetPID(L_P, L_I, L_D);
		m_LF.SetF(L_FF);
		m_LF.Enable();
		m_LF.SetAllowableClosedLoopErr(25);
		m_LF.SetSensorDirection(true);
		m_LF.ConfigNominalOutputVoltage(+0.0F, -0.0F);
		m_LF.ConfigPeakOutputVoltage(+12.0F, -12.0F);
		m_LF.SetPosition(0.0);
		//m_CANmotor1->SetCloseLoopRampRate(65);

		/* Left Rear Motor */
		m_LR = new CANTalon(12);
		m_LR->SetFeedbackDevice(CANTalon::QuadEncoder);
		m_LR->SetClosedLoopOutputDirection(false);
		m_LR->SetControlMode(CANTalon::kFollower);
		m_LR->Set(21);





		/* Right Front Motor */
		m_RF = new CANTalon(21);
		m_RF->SetFeedbackDevice(CANTalon::QuadEncoder);
		m_RF->SetClosedLoopOutputDirection(true);
		m_RF->SetControlMode(CANTalon::kSpeed);
		//m_RF->SetControlMode(CANTalon::kPercentVbus);
		m_RF->SetInverted(false);  //false for pid
		m_RF->ConfigEncoderCodesPerRev(256*1.4);
		m_RF->SetPID(R_P, R_I, R_D);
		m_RF->SetF(R_FF);
		m_RF->Enable();
		m_RF->SetAllowableClosedLoopErr(0);
		m_RF->SetSensorDirection(false);
		m_RF->ConfigNominalOutputVoltage(+0.0F, -0.0F);
		m_RF->ConfigPeakOutputVoltage(+12.0F, -12.0F);
		m_RF->SetPosition(0.0);
		//m_CANmotor1->SetCloseLoopRampRate(65);

		/* Right Rear Motor */
		m_RR = new CANTalon(20);
		m_RR->SetFeedbackDevice(CANTalon::QuadEncoder);
		m_RR->SetControlMode(CANTalon::kFollower);
		m_RR->SetClosedLoopOutputDirection(false);
		m_RR->Set(21);


	}
	void RobotInit() {
	}


	void AutonomousInit() {

	}

	void AutonomousPeriodic() {

	}

	void TeleopInit() {
		m_LF.SetPosition(0.0);
		_example.reset();
	}

	void TeleopPeriodic() {

	 _example.control();
	 TeleopShoot();

	}

	void TeleopShoot() {
		speed_pctVbus = 1.0;


		//m_RF->Set(200.0);


		CANTalon::SetValueMotionProfile setOutput = _example.getSetValue();
		m_LF.Set(setOutput);
		_example.start();

		L_PID_P = m_LF.GetP();
		L_PID_I = m_LF.GetI();
		L_PID_D = m_LF.GetD();
		L_PID_FF = m_LF.GetF();
		L_PID_Position = m_LF.GetPosition();
		L_PID_Speed = m_LF.GetSpeed();
		L_PID_Error = m_LF.GetClosedLoopError();           /* Closed loop error is is is Native Units per 100ms for Encoder */
		L_error_rpm = L_PID_Error * 0.4185;                 /* Formula to convert 1433.6 Native Units/Rot per 100ms to rpm       */
		L_PID_Setpoint = m_LF.GetSetpoint();

		R_PID_P = m_RF->GetP();
		R_PID_I = m_RF->GetI();
		R_PID_D = m_RF->GetD();
		R_PID_FF = m_RF->GetF();
		R_PID_Position = m_RF->GetPosition();
		R_PID_Speed = m_RF->GetSpeed();
		R_PID_Error = m_RF->GetClosedLoopError();           /* Closed loop error is is is Native Units per 100ms for Encoder */
		R_error_rpm = R_PID_Error * 0.4185;                 /* Formula to convert 1433.6 Native Units/Rot per 100ms to rpm       */
		R_PID_Setpoint = m_RF->GetSetpoint();

		LF_PID_Current = m_LF.GetOutputCurrent();
		LR_PID_Current = m_LR->GetOutputCurrent();
		RF_PID_Current = m_RF->GetOutputCurrent();
		RR_PID_Current = m_RR->GetOutputCurrent();

		SmartDashboard::PutNumber("L_PID_P", L_PID_P);
		SmartDashboard::PutNumber("L_PID_I", L_PID_I);
		SmartDashboard::PutNumber("L_PID_D", L_PID_D);
		SmartDashboard::PutNumber("L_PID_FF", L_PID_FF);
		SmartDashboard::PutNumber("L_PID_Position", L_PID_Position);
		SmartDashboard::PutNumber("L_PID_Speed", L_PID_Speed);
		SmartDashboard::PutNumber("L_PID_Error", L_PID_Error);
		SmartDashboard::PutNumber("L_PID_Setpoint", L_PID_Setpoint);
		SmartDashboard::PutNumber("L_error_rpm", L_error_rpm);

		SmartDashboard::PutNumber("R_PID_P", R_PID_P);
		SmartDashboard::PutNumber("R_PID_I", R_PID_I);
		SmartDashboard::PutNumber("R_PID_D", R_PID_D);
		SmartDashboard::PutNumber("R_PID_FF", R_PID_FF);
		SmartDashboard::PutNumber("R_PID_Position", R_PID_Position);
		SmartDashboard::PutNumber("R_PID_Speed", R_PID_Speed);
		SmartDashboard::PutNumber("R_PID_Error", R_PID_Error);
		SmartDashboard::PutNumber("R_PID_Setpoint", R_PID_Setpoint);
		SmartDashboard::PutNumber("R_error_rpm", R_error_rpm);

		SmartDashboard::PutNumber("LF_PID_Current", LF_PID_Current);
		SmartDashboard::PutNumber("LR_PID_Current", LR_PID_Current);
		SmartDashboard::PutNumber("RF_PID_Current", RF_PID_Current);
		SmartDashboard::PutNumber("RR_PID_Current", RR_PID_Current);

		SmartDashboard::PutNumber("count", count);


	}

	void TestPeriodic() {
	}

	void DisabledPeriodic()
	{
		/* it's generally a good idea to put motor controllers back
		 * into a known state when robot is disabled.  That way when you
		 * enable the robot doesn't just continue doing what it was doing before.
		 * BUT if that's what the application/testing requires than modify this accordingly */
		m_LF.SetControlMode(CANTalon::kPercentVbus);
		m_LF.Set( 0 );
		/* clear our buffer and put everything into a known state */
		_example.reset();
	}
};

START_ROBOT_CLASS(barrybbenson)

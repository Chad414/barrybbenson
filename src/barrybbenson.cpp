#include "WPILib.h"
#include "RobotUtils/RobotUtils.h"
#include "CANTalon.h"

#define K_P 0.05
#define K_I 0.001
#define K_D 0.0
#define K_Kv 0.014595
#define K_Ka 0.0

const int kMotionProfileSz =232;

const double kMotionProfile[][4] = {
{ 0,0,0,0 },
{ 0.01,0.0000195,0.0016935,0.1693395 },
{ 0.02,0.000039,0.003387,0.338679 },
{ 0.03,0.000117,0.007841,0.445434 },
{ 0.04,0.00024,0.012252,0.441079 },
{ 0.05,0.000416,0.017643,0.539116 },
{ 0.06,0.000656,0.024015,0.63717 },
{ 0.07,0.00097,0.031367,0.735249 },
{ 0.08,0.001367,0.039701,0.83336 },
{ 0.09,0.001857,0.049016,0.931512 },
{ 0.1,0.00245,0.059313,1.029715 },
{ 0.11,0.003156,0.070593,1.127981 },
{ 0.12,0.003985,0.082856,1.226321 },
{ 0.13,0.004946,0.096104,1.32475 },
{ 0.14,0.006049,0.110336,1.423283 },
{ 0.15,0.007305,0.125556,1.521933 },
{ 0.16,0.008722,0.141763,1.62072 },
{ 0.17,0.010312,0.15896,1.719659 },
{ 0.18,0.012083,0.177147,1.818771 },
{ 0.19,0.014047,0.196328,1.918074 },
{ 0.2,0.016212,0.216504,2.01759 },
{ 0.21,0.018588,0.237677,2.117341 },
{ 0.22,0.021187,0.259851,2.217349 },
{ 0.23,0.024017,0.283027,2.317638 },
{ 0.24,0.027089,0.30721,2.418233 },
{ 0.25,0.030413,0.332401,2.519159 },
{ 0.26,0.033999,0.358606,2.620443 },
{ 0.27,0.037858,0.385827,2.722113 },
{ 0.28,0.041998,0.414069,2.824195 },
{ 0.29,0.046432,0.443336,2.92672 },
{ 0.3,0.051168,0.473633,3.029717 },
{ 0.31,0.056218,0.504965,3.133218 },
{ 0.32,0.061591,0.537338,3.237253 },
{ 0.33,0.067299,0.570756,3.341854 },
{ 0.34,0.073351,0.605227,3.447056 },
{ 0.35,0.079759,0.640756,3.552893 },
{ 0.36,0.086527,0.676855,3.609902 },
{ 0.37,0.093657,0.713034,3.617921 },
{ 0.38,0.10115,0.749297,3.62634 },
{ 0.39,0.109007,0.785649,3.635154 },
{ 0.4,0.117228,0.822093,3.644364 },
{ 0.41,0.125814,0.858632,3.653969 },
{ 0.42,0.134767,0.895272,3.663967 },
{ 0.43,0.144087,0.932016,3.674359 },
{ 0.44,0.153776,0.968867,3.685146 },
{ 0.45,0.163834,1.00583,3.696328 },
{ 0.46,0.174263,1.042909,3.707909 },
{ 0.47,0.185064,1.080108,3.71989 },
{ 0.48,0.196238,1.117431,3.732275 },
{ 0.49,0.207787,1.154882,3.745069 },
{ 0.5,0.219712,1.192465,3.758278 },
{ 0.51,0.232014,1.230184,3.771905 },
{ 0.52,0.244694,1.268043,3.785961 },
{ 0.53,0.257755,1.306048,3.800451 },
{ 0.54,0.271197,1.344202,3.815386 },
{ 0.55,0.285022,1.382509,3.830775 },
{ 0.56,0.299232,1.420976,3.84663 },
{ 0.57,0.313828,1.459605,3.862963 },
{ 0.58,0.328812,1.498403,3.879788 },
{ 0.59,0.344185,1.537374,3.897117 },
{ 0.6,0.359951,1.576524,3.914968 },
{ 0.61,0.376109,1.615857,3.933355 },
{ 0.62,0.392663,1.65538,3.952296 },
{ 0.63,0.409614,1.695099,3.971809 },
{ 0.64,0.426964,1.735018,3.991913 },
{ 0.65,0.444716,1.775144,4.012625 },
{ 0.66,0.46287,1.815484,4.033966 },
{ 0.67,0.481431,1.856043,4.055955 },
{ 0.68,0.500399,1.896829,4.078611 },
{ 0.69,0.519778,1.937849,4.101953 },
{ 0.7,0.539569,1.979109,4.126 },
{ 0.71,0.559775,2.020616,4.150768 },
{ 0.72,0.580399,2.062379,4.176274 },
{ 0.73,0.601443,2.104404,4.202529 },
{ 0.74,0.62291,2.1467,4.229544 },
{ 0.75,0.644802,2.189273,4.257326 },
{ 0.76,0.667124,2.232132,4.285877 },
{ 0.77,0.689877,2.275284,4.315194 },
{ 0.78,0.713064,2.318737,4.345267 },
{ 0.79,0.736689,2.362497,4.376077 },
{ 0.8,0.760749,2.406042,4.354476 },
{ 0.81,0.785238,2.44884,4.279747 },
{ 0.82,0.810147,2.490885,4.204512 },
{ 0.83,0.835468,2.532171,4.128652 },
{ 0.84,0.861195,2.572692,4.052032 },
{ 0.85,0.88732,2.612437,3.974502 },
{ 0.86,0.913834,2.651396,3.895899 },
{ 0.87,0.940729,2.689556,3.816041 },
{ 0.88,0.967998,2.726903,3.734729 },
{ 0.89,0.995632,2.763421,3.651748 },
{ 0.9,1.023623,2.799089,3.566866 },
{ 0.91,1.051962,2.833888,3.479836 },
{ 0.92,1.08064,2.867792,3.390394 },
{ 0.93,1.109648,2.900774,3.298264 },
{ 0.94,1.138976,2.932806,3.20316 },
{ 0.95,1.168614,2.963854,3.104785 },
{ 0.96,1.198553,2.993882,3.002841 },
{ 0.97,1.228782,3.022852,2.897029 },
{ 0.98,1.259289,3.050723,2.787058 },
{ 0.99,1.290063,3.077449,2.672645 },
{ 1,1.321093,3.102985,2.55353 },
{ 1.01,1.352366,3.12728,2.429479 },
{ 1.02,1.383869,3.150282,2.300293 },
{ 1.03,1.415588,3.171941,2.165814 },
{ 1.04,1.44751,3.1922,2.025939 },
{ 1.05,1.47962,3.211006,1.880621 },
{ 1.06,1.511903,3.228305,1.729883 },
{ 1.07,1.544344,3.244043,1.573821 },
{ 1.08,1.576926,3.258169,1.412606 },
{ 1.09,1.609632,3.270634,1.246495 },
{ 1.1,1.642446,3.281393,1.075824 },
{ 1.11,1.67535,3.290403,0.90101 },
{ 1.12,1.708326,3.297628,0.72255 },
{ 1.13,1.741356,3.303038,0.541009 },
{ 1.14,1.774423,3.306608,0.357013 },
{ 1.15,1.807502,3.30791,0.130161 },
{ 1.16,1.840571,3.306932,-0.097756 },
{ 1.17,1.873612,3.304084,-0.28484 },
{ 1.18,1.906606,3.29937,-0.471398 },
{ 1.19,1.939534,3.292803,-0.6567 },
{ 1.2,1.972378,3.284403,-0.840041 },
{ 1.21,2.00512,3.274195,-1.020756 },
{ 1.22,2.037742,3.262213,-1.198235 },
{ 1.23,2.070227,3.248493,-1.37193 },
{ 1.24,2.102557,3.23308,-1.541368 },
{ 1.25,2.134718,3.216018,-1.706152 },
{ 1.26,2.166691,3.197359,-1.865968 },
{ 1.27,2.198463,3.177153,-2.020583 },
{ 1.28,2.230017,3.155454,-2.169844 },
{ 1.29,2.26134,3.132317,-2.313677 },
{ 1.3,2.292418,3.107797,-2.452078 },
{ 1.31,2.323238,3.081946,-2.585107 },
{ 1.32,2.353786,3.054817,-2.712883 },
{ 1.33,2.384051,3.026461,-2.835573 },
{ 1.34,2.41402,2.996927,-2.953387 },
{ 1.35,2.443683,2.966262,-3.066563 },
{ 1.36,2.473028,2.934508,-3.175368 },
{ 1.37,2.502045,2.901707,-3.280083 },
{ 1.38,2.530724,2.867897,-3.381002 },
{ 1.39,2.559055,2.833113,-3.478422 },
{ 1.4,2.587029,2.797386,-3.572639 },
{ 1.41,2.614636,2.760747,-3.663943 },
{ 1.42,2.641868,2.723221,-3.752617 },
{ 1.43,2.668717,2.684831,-3.838933 },
{ 1.44,2.695173,2.6456,-3.923146 },
{ 1.45,2.721228,2.605545,-4.005498 },
{ 1.46,2.746875,2.564683,-4.086215 },
{ 1.47,2.772105,2.523028,-4.165505 },
{ 1.48,2.796911,2.480592,-4.24356 },
{ 1.49,2.821285,2.437387,-4.320556 },
{ 1.5,2.845219,2.39342,-4.396651 },
{ 1.51,2.86871,2.349081,-4.433966 },
{ 1.52,2.891759,2.304901,-4.418 },
{ 1.53,2.914369,2.261027,-4.38734 },
{ 1.54,2.936544,2.217455,-4.357257 },
{ 1.55,2.958286,2.174177,-4.327789 },
{ 1.56,2.979597,2.131187,-4.298963 },
{ 1.57,3.000482,2.088479,-4.270798 },
{ 1.58,3.020943,2.046046,-4.243306 },
{ 1.59,3.040981,2.003881,-4.216491 },
{ 1.6,3.060601,1.961978,-4.190354 },
{ 1.61,3.079805,1.920329,-4.164891 },
{ 1.62,3.098594,1.878928,-4.140094 },
{ 1.63,3.116972,1.837768,-4.115955 },
{ 1.64,3.13494,1.796844,-4.092459 },
{ 1.65,3.152501,1.756148,-4.069594 },
{ 1.66,3.169658,1.715674,-4.047345 },
{ 1.67,3.186412,1.675417,-4.025697 },
{ 1.68,3.202766,1.635371,-4.004633 },
{ 1.69,3.218721,1.595529,-3.984139 },
{ 1.7,3.23428,1.555887,-3.964197 },
{ 1.71,3.249445,1.51644,-3.944793 },
{ 1.72,3.264216,1.47718,-3.925912 },
{ 1.73,3.278597,1.438105,-3.90754 },
{ 1.74,3.29259,1.399208,-3.889663 },
{ 1.75,3.306194,1.360486,-3.87227 },
{ 1.76,3.319414,1.321932,-3.855349 },
{ 1.77,3.332249,1.283543,-3.838889 },
{ 1.78,3.344702,1.245315,-3.822881 },
{ 1.79,3.356775,1.207241,-3.807317 },
{ 1.8,3.368468,1.169319,-3.79219 },
{ 1.81,3.379783,1.131545,-3.777493 },
{ 1.82,3.390722,1.093912,-3.763221 },
{ 1.83,3.401287,1.056419,-3.749371 },
{ 1.84,3.411477,1.019059,-3.735938 },
{ 1.85,3.421296,0.98183,-3.722922 },
{ 1.86,3.430743,0.944727,-3.710321 },
{ 1.87,3.43982,0.907745,-3.698135 },
{ 1.88,3.448529,0.870882,-3.686364 },
{ 1.89,3.45687,0.834132,-3.675009 },
{ 1.9,3.464845,0.797491,-3.664073 },
{ 1.91,3.472455,0.760955,-3.653559 },
{ 1.92,3.4797,0.724521,-3.643468 },
{ 1.93,3.486582,0.688183,-3.633806 },
{ 1.94,3.493101,0.651937,-3.624576 },
{ 1.95,3.499263,0.616133,-3.58041 },
{ 1.96,3.505075,0.581259,-3.487369 },
{ 1.97,3.51055,0.54745,-3.380941 },
{ 1.98,3.515697,0.514698,-3.275197 },
{ 1.99,3.520527,0.482997,-3.170104 },
{ 2,3.52505,0.45234,-3.065625 },
{ 2.01,3.529277,0.422723,-2.961726 },
{ 2.02,3.533219,0.394139,-2.858373 },
{ 2.03,3.536885,0.366584,-2.755533 },
{ 2.04,3.540285,0.340052,-2.653174 },
{ 2.05,3.54343,0.31454,-2.551264 },
{ 2.06,3.546331,0.290042,-2.449772 },
{ 2.07,3.548996,0.266555,-2.348669 },
{ 2.08,3.551437,0.244076,-2.247926 },
{ 2.09,3.553663,0.222601,-2.147513 },
{ 2.1,3.555684,0.202127,-2.047405 },
{ 2.11,3.557511,0.182651,-1.947575 },
{ 2.12,3.559153,0.164171,-1.847997 },
{ 2.13,3.56062,0.146685,-1.748648 },
{ 2.14,3.561921,0.13019,-1.649504 },
{ 2.15,3.563068,0.114684,-1.550544 },
{ 2.16,3.56407,0.100167,-1.451746 },
{ 2.17,3.564936,0.086636,-1.353092 },
{ 2.18,3.565677,0.07409,-1.254562 },
{ 2.19,3.566302,0.062529,-1.156139 },
{ 2.2,3.566822,0.051951,-1.057808 },
{ 2.21,3.567246,0.042355,-0.959554 },
{ 2.22,3.567583,0.033742,-0.861363 },
{ 2.23,3.567844,0.026109,-0.763223 },
{ 2.24,3.568039,0.019458,-0.665123 },
{ 2.25,3.568176,0.013788,-0.567054 },
{ 2.26,3.568267,0.009097,-0.469007 },
{ 2.27,3.568321,0.005388,-0.370976 },
{ 2.28,3.568348,0.002658,-0.272954 },
{ 2.29,3.568357,0.000909,-0.174937 },
{ 2.3,3.568358,0.00014,-0.076923 },
{ 2.31,3.568358,0,-0.013958 }};


class barrybbenson: public HotBot {
private:
	CANTalon* m_CANmotor1;
	AnalogPotentiometer* m_pot;
	Timer m_timer;

	double target_rpm, error_rpm;
	double PID_P, PID_I, PID_D, PID_FF, PID_Current, PID_Position, PID_Speed, PID_Error, PID_Setpoint, PID_SpeedGet;
	double potentio;
	double timerLast, timerCurrent, deltaTime;
	double errorSum, errorLast, errorCurrent, errorDeriv;
	int index;
	double targetTime, targetPos, targetVel, targetAcc, interpolate;
	double Cmd_Kp, Cmd_Ki, Cmd_Kd, Cmd_Ka, Cmd_Kv, Cmd_Total;


public:
	barrybbenson() {
		m_CANmotor1 = new CANTalon(2);
		m_CANmotor1->SetFeedbackDevice(CANTalon::CtreMagEncoder_Relative);
		m_CANmotor1->SetClosedLoopOutputDirection(true);
		m_CANmotor1->SetControlMode(CANTalon::kPercentVbus);
		m_CANmotor1->Enable();
		m_CANmotor1->SetAllowableClosedLoopErr(0);
		m_CANmotor1->SetSensorDirection(true);
		m_CANmotor1->SetClosedLoopOutputDirection(true);
		m_CANmotor1->ConfigNominalOutputVoltage(+0.0F, -0.0F);
		m_CANmotor1->ConfigPeakOutputVoltage(+12.0F, -12.0F);
		m_CANmotor1->SetCloseLoopRampRate(65);

		AnalogInput *ai = new AnalogInput(0);
		m_pot = new AnalogPotentiometer(ai, 360, 0);


	}
	void RobotInit() {
	}


	void AutonomousInit() {

	}

	void AutonomousPeriodic() {

	}

	void TeleopInit() {
		target_rpm = 0.0;
		potentio = 0.0F;
		m_timer.Reset();
		m_timer.Start();
		timerLast = m_timer.Get();
		m_CANmotor1->SetPosition(0.0);
		errorSum = 0.0;
		errorLast = 0.0;
		errorCurrent = 0.0;
		errorDeriv = 0.0;
		index = 0;
		targetTime = kMotionProfile[index][0];
		targetPos = kMotionProfile[index][1];
		targetVel = kMotionProfile[index][2];
		targetAcc = kMotionProfile[index][3];
		interpolate = 0.0;
	}

	void TeleopPeriodic() {
	 TeleopShoot();

	}

	void TeleopShoot() {
		timerCurrent = m_timer.Get();
		deltaTime = timerCurrent - timerLast;

		while ((kMotionProfile[index + 1][0] < timerCurrent) &&
			   ((index + 1) < kMotionProfileSz)) {
			index++;
		}

		if ((index + 1) == kMotionProfileSz) {
			targetTime = kMotionProfile[index][0];
			targetPos = kMotionProfile[index][1];
			targetVel = kMotionProfile[index][2];
			targetAcc = kMotionProfile[index][3];
			interpolate = 1.0;
		}
		else {
			interpolate = ((timerCurrent - kMotionProfile[index][0]) / (kMotionProfile[index + 1][0] - kMotionProfile[index][0]));
			targetTime = (interpolate * (kMotionProfile[index + 1][0] - kMotionProfile[index][0])) + kMotionProfile[index][0];
			targetPos = (interpolate * (kMotionProfile[index + 1][1] - kMotionProfile[index][1])) + kMotionProfile[index][1];
			targetVel = (interpolate * (kMotionProfile[index + 1][2] - kMotionProfile[index][2])) + kMotionProfile[index][2];
			targetAcc = (interpolate * (kMotionProfile[index + 1][3] - kMotionProfile[index][3])) + kMotionProfile[index][3];
		}

		errorCurrent = targetPos - m_CANmotor1->GetPosition();
		errorSum += (errorCurrent * deltaTime);
		errorDeriv = (errorCurrent - errorLast) / deltaTime;
		Cmd_Kp = K_P * errorCurrent;
		Cmd_Ki = K_I * errorSum;
		Cmd_Kd = K_D * errorDeriv;
		Cmd_Ka = K_Ka * targetAcc;
		Cmd_Kv = K_Kv * targetVel;

		Cmd_Total = Cmd_Kp + Cmd_Ki + Cmd_Kd + Cmd_Ka + Cmd_Kv;

		if (timerCurrent > kMotionProfile[kMotionProfileSz - 1][0]) {
			m_CANmotor1->Set(0);
		}
		else {
			m_CANmotor1->Set(Cmd_Total);
		}

		timerLast = timerCurrent;
		errorLast = errorCurrent;

		PID_Current = m_CANmotor1->GetOutputCurrent();
		PID_Position = m_CANmotor1->GetPosition();
		PID_Speed = m_CANmotor1->GetSpeed();
		PID_Setpoint = m_CANmotor1->GetSetpoint();


		SmartDashboard::PutNumber("PID_Current", PID_Current);
		SmartDashboard::PutNumber("PID_Position", PID_Position);
		SmartDashboard::PutNumber("PID_Speed", PID_Speed);
		SmartDashboard::PutNumber("PID_Setpoint", PID_Setpoint);
		SmartDashboard::PutNumber("timerCurrent", timerCurrent);
		SmartDashboard::PutNumber("deltaTime", deltaTime);
		SmartDashboard::PutNumber("Cmd_Kp", Cmd_Kp);
		SmartDashboard::PutNumber("Cmd_Ki", Cmd_Ki);
		SmartDashboard::PutNumber("Cmd_Kd", Cmd_Kd);
		SmartDashboard::PutNumber("Cmd_Ka", Cmd_Ka);
		SmartDashboard::PutNumber("Cmd_Kv", Cmd_Kv);
		SmartDashboard::PutNumber("Cmd_Total", Cmd_Total);
		SmartDashboard::PutNumber("interpolate", interpolate);
		SmartDashboard::PutNumber("targetTime", targetTime);
		SmartDashboard::PutNumber("targetPos", targetPos);
		SmartDashboard::PutNumber("targetVel", targetVel);
		SmartDashboard::PutNumber("targetAcc", targetAcc);
		SmartDashboard::PutNumber("errorCurrent", errorCurrent);
		SmartDashboard::PutNumber("errorSum", errorSum);
		SmartDashboard::PutNumber("errorDeriv", errorDeriv);
	}

	void TestPeriodic() {
	}

};

START_ROBOT_CLASS(barrybbenson)


#include "ace.h"


Drive chassis(
	// Left Chassis Ports (negative port will reverse it!)
	{ PORT_CHASSIS_L_F, PORT_CHASSIS_L_B, PORT_CHASSIS_L_M},

	// Right Chassis Ports (negative port will reverse it!)
	{ PORT_CHASSIS_R_F,  PORT_CHASSIS_R_B, PORT_CHASSIS_R_M},

	// IMU Port
	PORT_IMU,

	// Wheel Diameter (Remember, 4" wheels are actually 4.125!)
	2.75,

	// Cartridge RPM
	600,

	// External Gear Ratio (MUST BE DECIMAL)
	0.75
);


// partner controller
pros::Controller partner(pros::E_CONTROLLER_PARTNER);

namespace ace
{

	/* ========================================================================== */
	/*                         Global Variable Definitions                        */
	/* ========================================================================== */

	bool partner_connected = false;
	bool is_red_alliance = false;

	float launch_speed = LAUNCH_SPEED;

	util::timer endgame_timer(200);
	util::timer intake_timer(2000);

	// leds
	pros::ADILed led(PORT_LED, 60);

	A_Motor launcherMotorLeft(PORT_LAUNCHER_LEFT, MOTOR_GEARSET_36, true); //red


	A_Motor intakeMotorLeft(PORT_INTAKE_LEFT, MOTOR_GEARSET_06, false); //blue

	A_Motor intakeMotorRight(PORT_INTAKE_RIGHT,MOTOR_GEARSET_06, false);

	A_Motor LiftMotorLeft(PORT_LIFT_LEFT,MOTOR_GEARSET_36, false);

	A_Motor LiftMotorRight(PORT_LIFT_RIGHT,MOTOR_GEARSET_36, false);

	
	

	/* ========================================================================= */
	/*                              Class Definitions                             */
	/* ========================================================================== */

	/* --------------------------- Custom Motor Class --------------------------- */
	void A_Motor::init()
	{
		if (!has_init)
		{
			has_init = true;

			set_encoder_units(MOTOR_ENCODER_DEGREES);
		}
	}
	float A_Motor::get_temp()
	{

		return util::cel_to_faren(get_temperature());
	}
	void A_Motor::spin_percent(float percent)
	{

		if (std::abs(percent) <= 5)
		{
			move_voltage(0);
			return;
		}

		if (get_gearing() == MOTOR_GEARSET_06)
		{
			move_velocity(percent * 6.0f);
		}
		else if (get_gearing() == MOTOR_GEARSET_18)
		{
			move_velocity(percent * 2.0f);
		}
		else if (get_gearing() == MOTOR_GEARSET_36)
		{
			move_velocity(percent);
		}
		else
		{
			printf("ERROR CARTRIDGE NOT FOUND");
		}
	}
	float A_Motor::get_percent_velocity()
	{

		if (get_gearing() == MOTOR_GEARSET_06)
		{
			return get_actual_velocity() / 6.0f;
		}
		else if (get_gearing() == MOTOR_GEARSET_18)
		{
			return get_actual_velocity() / 2.0f;
		}
		else if (get_gearing() == MOTOR_GEARSET_36)
		{
			return get_actual_velocity() / 1.0f;
		}
		else
		{
			printf("ERROR CARTRIDGE NOT FOUND");
			return 0.0f;
		}
	}
	float A_Motor::get_percent_torque()
	{

		if (get_gearing() == MOTOR_GEARSET_06)
		{
			return get_torque() * 6.0f / 2.1f * 100.0f;
		}
		else if (get_gearing() == MOTOR_GEARSET_18)
		{
			return get_torque() * 2.0f / 2.1f * 100.0f;
		}
		else if (get_gearing() == MOTOR_GEARSET_36)
		{
			return get_torque() * 1.0f / 2.1f * 100.0f;
		}
		else
		{
			printf("ERROR CARTRIDGE NOT FOUND");
			return 0.0f;
		}
	}

	/* --------------------------- Custom Button Class -------------------------- */

	// Constructor with one btn
	Btn_Digi::Btn_Digi(pros::controller_digital_e_t btn_assign, cntr_t is_master)
	{

		mode = is_master;
		btn_master = btn_assign;
		btn_partner = btn_assign;
	};
	// get whether button pressed
	bool Btn_Digi::get_press()
	{

		if (mode == cntr_both)
		{

			if (partner_connected)
			{
				return partner.get_digital(btn_partner);
			}
			else
			{
				return master.get_digital(btn_master);
			}
		}
		else if (mode == cntr_partner)
		{
			if (partner_connected)
			{
				return partner.get_digital(btn_partner);
			}
			else	
			{
				return false;
			}
		}
		else if (mode == cntr_master)
		{
			return master.get_digital(btn_master);
		}
		return false;
	};
	// get whether new button press
	bool Btn_Digi::get_press_new()
	{

		if (mode == cntr_both)
		{
			return master.get_digital_new_press(btn_master) || partner.get_digital_new_press(btn_partner);
		}
		else if (mode == cntr_partner)
		{
			if (partner_connected)
			{
				return partner.get_digital_new_press(btn_partner);
			}
			else
			{
				return false;
			}
		}
		else if (mode == cntr_master)
		{
			return master.get_digital_new_press(btn_master);
		}
		return false;
	};

	/* -------------------------------------------------------------------------- */
	/*                             User Control Stuffs                            */
	/* -------------------------------------------------------------------------- */

	bool curr_launching = false;
	util::timer long_launch_timer(650);


	//launch triball
	
	void launch(float speed){
		
	
		launcherMotorLeft.move_voltage(speed * 120);	

	}


	/*void launch_reverse(float speed){

		launcherMotorRight.move_voltage(speed * -120);

	}*/

	// launch standby
	void launch_standby(bool enabled, float speed)
	{
		curr_launching = false;
		if (enabled)
			launcherMotorLeft.move_velocity(speed * 6);
			
		else
			launcherMotorLeft.move_velocity(0);
			
	}

	// reset motors to 0 voltage
	void reset_motors()
	{	
		launcherMotorLeft.move_voltage(0);
		intakeMotorLeft.move_voltage(0);
		intakeMotorRight.move_voltage(0);
	
	

		launcher_standby_enabled = false;

		flapPneumatics.set_value(false);
		endgamePneumatics.set_value(false);
		lockPneumatics.set_value(false);
	}


	// toggles flapjack

	void flap_toggle(bool enabled)
	{
		if (enabled)
		{
			flapPneumatics.set_value(1);
			return;

		}
		else
		{
			flapPneumatics.set_value(0);
		}
	}

	
	// toggles endgame
	void endgame_toggle(bool enabled)
	{
		if (enabled)
		{
			endgame_timer.reset();
			endgamePneumatics.set_value(1);
			return;
		}
		else
		{
			if (endgame_timer.done())
			{
				//endgamePneumatics.set_value(0);
				return;
			}

			endgame_timer.update(20);
			//endgamePneumatics.set_value(0);
		}
	}

	void lock_toggle(bool enabled)
	{
		if (enabled)
		{
			lockPneumatics.set_value(1);
			return;
		}
		else
		{
			lockPneumatics.set_value(0);
		}
	}

	void intake(bool enabled)
	{
		// intake enabled
		if (enabled)
		{
			intakeMotorLeft.spin_percent(INTAKE_SPEED);
			

		}

		// Not enabled
		else
		{
			intake_timer.reset();
			intakeMotorLeft.spin_percent(0);
			

		}
	}

	void intake_reverse(bool enabled)
	{
		if (enabled) {
			intakeMotorLeft.spin_percent(-INTAKE_SPEED);
			intakeMotorRight.spin_percent(-INTAKE_SPEED);
		


		}else {
			intakeMotorLeft.spin_percent(0);
			intakeMotorRight.spin_percent(0);
		}
	}
	void lift_up(bool enabled)
	{
		if (enabled){
			LiftMotorLeft.spin_percent(ace::LIFT_SPEED);
			LiftMotorRight.spin_percent(ace::LIFT_SPEED);
		
		}
		else{
			LiftMotorLeft.spin_percent(0);
			LiftMotorRight.spin_percent(0);
		}
	}

	void lift_down(bool enabled)
	{
		if (enabled){
			LiftMotorLeft.spin_percent(-ace::LIFT_SPEED);
			LiftMotorRight.spin_percent(-ace::LIFT_SPEED);
		
		}
		else{
			LiftMotorLeft.spin_percent(0);
			LiftMotorRight.spin_percent(0);
		}
	}

	
	/*
	
	
	*/
	/* ------------------------------ Vision Sensor ----------------------------- */
	double theta = 0;
	void auto_target(bool enabled)
	{
		pros::vision_object_s_t goal = visionSensor.get_by_sig(0, 0);

		theta = (((double)(goal.x_middle_coord) / ((double)VISION_FOV_WIDTH / 2.0)) * 30.0) + auto_target_angle_adjustment;

		if (enabled && std::abs(theta) <= 30)
		{
			if (std::abs(theta) > 1)
			{
				chassis.reset_gyro();
				chassis.set_turn_pid(theta, 0.5 * 127.0);
				// Have to figure out finding correct distance , or have Ross adjust manually using preset 
				auton::drive_chassis(1, DRIVE_SPEED);
			} else {
				// Have to figure out finding correct distance , or have Ross adjust manually using preset 
				auton::drive_chassis(1, DRIVE_SPEED);

			}
		}
	}

	/* ------------------------------ Light Sensor ------------------------------ */
	int ambient_light = 0;
	float light_diff_factor = 1.2;

	bool current_detecting = false;

	bool light_sensor_detect()
	{
		// if is detecting disk
		if ((lightSensor.get_value() >= ambient_light * light_diff_factor)) {
			current_detecting = true;
		}
		// no disk
		else {
			if (current_detecting)
			{
				current_detecting = false;
				return true;
			}
		}

		return false;
	}



	/* -------------------------------------------------------------------------- */
	/*                              Controller Stuffs                             */
	/* -------------------------------------------------------------------------- */

	bool new_haptic_request = false;
	std::string cntr_haptic_text = "";

	bool cntr_task_init = false;

	void update_cntr_task()
	{

		bool draw_master = false;
		int curr_line = 0;

		while (1)
		{

			partner_connected = partner.is_connected();

			if (new_haptic_request)
			{
				if (new_haptic_request_is_master)
				{
					master.rumble(cntr_haptic_text.c_str());
				}
				else
				{
					partner.rumble(cntr_haptic_text.c_str());
				}
				new_haptic_request = false;
			}

			/* ------------------------------ Update Screen ----------------------------- */
			else if (!draw_master)
			{
				partner.set_text(curr_line, 0, cntr_partner_text_arr[curr_line]);
			}
			else
			{
				master.set_text(curr_line, 0, cntr_master_text_arr[curr_line]);
			}

			curr_line++;
			if (curr_line > 2)
			{
				curr_line = 0;
				draw_master = !draw_master;
			}

			pros::delay(50);
		}
	}

	std::string cntr_compile_string(std::vector<std::string> arr)
	{

		std::string result = "";
		for (int i = 0; i <= 3; i++)
		{
			result += arr[i];
			if (i < 3)
			{
				result += "\n";
			}
		}
		return result;
	}

	void update_cntr_text(cntr_t cntr, u_int8_t row, std::string text)
	{

		text = text + "      ";

		// both controllers
		if (cntr == cntr_both)
		{
			cntr_partner_text_arr[row] = text;
			cntr_master_text_arr[row] = text;
		}

		//  master controller
		else if (cntr == cntr_master)
		{
			cntr_master_text_arr[row] = text;
		}

		//  partner controller
		else if (cntr == cntr_partner)
		{
			cntr_partner_text_arr[row] = text;
		}
	}

	bool new_haptic_request_is_master = false;

	void update_cntr_haptic(std::string new_haptic, bool is_master)
	{
		new_haptic_request = true;
		new_haptic_request_is_master = is_master;
		cntr_haptic_text = new_haptic;
	}

	/* ========================================================================== */
	/*                                Update LED's                                */
	/* ========================================================================== */

	/*led_state_t curr_led_state = led_idle;

	bool led_task_init = false;

	void update_leds_task()
	{

		led_state_t curr_state = led_idle;

		util::timer led_intake_timer(2000);

		while (1)
		{

			int color = (ace::is_red_alliance) ? ace::led_color_red : ace::led_color_blue;
			int color_bright = (ace::is_red_alliance) ? ace::led_color_red_bright : ace::led_color_blue_bright;

			// check if state changed
			if (curr_led_state != curr_state)
			{
				curr_state = curr_led_state;

				if (curr_state == led_idle)
				{
					led.set_all(color);
				}
			}

			// check if either intake or launch state
			if (curr_led_state == led_intake)
			{
				int arr[led.length()] = {};

				int index = (int)((float)led.length()) * (led_intake_timer.currTime / led_intake_timer.maxTime);

				for (int i = 0; i < led.length(); i++)
				{

					if (i == index)
					{
						arr[i] = color_bright;
					}
					else
					{
						arr[i] = color;
					}
				}

				led_intake_timer.update(10);
			}

			pros::delay(10);
		}
	}*/
}

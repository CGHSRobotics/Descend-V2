
#include "ace.h"

namespace ace::auton {

/* ========================================================================== */
/*                        Global Variables Definitions                        */
/* ========================================================================== */

int auton_selection_index = 0;
/* ========================================================================== */
/*                               Score Auton                                   */
/* ========================================================================== */
void score() {
  drive_chassis(20, DRIVE_SPEED);
  turn_chassis(45, TURN_SPEED);
  drive_chassis(20, DRIVE_SPEED);

  // chassis.set_drive_pid(43, DRIVE_SPEED, false);
  // pros::delay(10000);

  /*drive_chassis(70, DRIVE_SPEED);
  turn_chassis(90, TURN_SPEED);
  ace::intake_reverse(true);
  pros::delay(1000);
  ace::intake_reverse(false);
  drive_chassis(-30, DRIVE_SPEED);
  turn_chassis(270, TURN_SPEED);
  drive_chassis(-50, DRIVE_SPEED);



  turn_chassis(-90, TURN_SPEED);
  drive_chassis(65, DRIVE_SPEED);
  drive_chassis(3,DRIVE_SPEED);
  turn_chassis(-90, TURN_SPEED);
  drive_chassis(46, DRIVE_SPEED);
  turn_chassis(180, TURN_SPEED);
  drive_chassis(-24, DRIVE_SPEED);*/

  // Go for more goals?
}

/* ========================================================================== */
/*                               Contact Auton                                  */
/* ========================================================================== */
void contact() {
}

/* ========================================================================== */
/*                              Three Side Auton                              */
/* ========================================================================== */
void offense_side() {
 ace::lift_up(true);
 pros::delay(200);
 ace::lift_up(false);

 drive_chassis(12,DRIVE_SPEED);
 ace::intake(true);
 pros::delay(200);
 drive_chassis(-70, DRIVE_SPEED);
 turn_chassis(145, TURN_SPEED);

 ace::intake(false);
 ace::intake_reverse(true);
 drive_chassis(40, DRIVE_SPEED);
 turn_chassis(100, TURN_SPEED);
 drive_chassis(45, DRIVE_SPEED);
 drive_chassis(-20, DRIVE_SPEED);
 turn_chassis(17, TURN_SPEED);
 ace::intake_reverse(false);
 ace::intake(true);
 drive_chassis(90, DRIVE_SPEED);
 pros::delay(200);
 turn_chassis(150, TURN_SPEED);
 drive_chassis(35, DRIVE_SPEED);
 ace::intake(false);
 ace::intake_reverse(true);
 pros::delay(400);
 turn_chassis(35,TURN_SPEED);
 drive_chassis(36, DRIVE_SPEED);
 ace::intake(true);
 pros::delay(300);
 turn_chassis(180, TURN_SPEED);
 ace::flap_toggle(true);
 ace::intake(false);
 ace::intake_reverse(true);
 drive_chassis(70, DRIVE_SPEED);
 drive_chassis(-30, DRIVE_SPEED);





  

  

  
  // Dead
}

// ross is good

/* ========================================================================== */
/*                               Two Side Auton                               */
/* ========================================================================== */
void defense_side() {
  
  drive_chassis(-35, ace::AUTON_DRIVE_SPEED, true);
  // 30
  turn_chassis(40, ace::AUTON_TURN_SPEED, true);


  drive_chassis(-40, ace::AUTON_DRIVE_SPEED, true);

  drive_chassis(25, ace::AUTON_DRIVE_SPEED, true);
  turn_chassis(40, TURN_SPEED);
  drive_chassis(20, DRIVE_SPEED);
  turn_chassis(-5, TURN_SPEED);
  //turn_chassis(-130, TURN_SPEED);
 // drive_chassis(72, DRIVE_SPEED);
  //ace::intake(true);
  //pros::delay(300);
 // turn_chassis(-115, TURN_SPEED);
  //drive_chassis(-115, DRIVE_SPEED);

  ace::flap_toggle(true);
   pros::delay(300);
  drive_chassis(20, DRIVE_SPEED);
 turn_chassis(-30, TURN_SPEED);
  flap_toggle(false);
 // turn_chassis(150, TURN_SPEED);
  //ace::intake_reverse(true);
  drive_chassis(63, DRIVE_SPEED);
  ace::intake_reverse(true);
  pros::delay(500);
  ace::intake_reverse(false);
  
  //ace::intake_reverse(false);
  




  

  // Dead
}

/* ========================================================================== */
/*                                   Skills                                   */
/* ========================================================================== */
void skills() {
  drive_chassis(-35, ace::AUTON_DRIVE_SPEED, true);
  // 30
  turn_chassis(40, ace::AUTON_TURN_SPEED, true);


  drive_chassis(-40, ace::AUTON_DRIVE_SPEED, true);

  drive_chassis(24, ace::AUTON_DRIVE_SPEED, true);

  turn_chassis(120, ace::AUTON_TURN_SPEED, true);
  drive_chassis( 5, DRIVE_SPEED, true);

  drive_chassis(20, ace::AUTON_DRIVE_SPEED, true);

  launch_auton(ace::launch_speed);
  pros::delay(33000);
  launch_auton(0);

  drive_chassis(-10, DRIVE_SPEED);
  turn_chassis(0, TURN_SPEED);
  drive_chassis(45, DRIVE_SPEED);
  turn_chassis(-45, TURN_SPEED);
  drive_chassis(135, DRIVE_SPEED);
  turn_chassis(-140, TURN_SPEED);
  drive_chassis(40, DRIVE_SPEED);
  turn_chassis(-170, TURN_SPEED);
  
  drive_chassis(70, DRIVE_SPEED);

  turn_chassis(-50, TURN_SPEED);
  ace::flap_toggle(true);
  drive_chassis(80, DRIVE_SPEED);
  drive_chassis(-20, DRIVE_SPEED);
  drive_chassis(40, DRIVE_SPEED); 
  ace::flap_toggle(false);
  drive_chassis(-70, DRIVE_SPEED);
  turn_chassis(-65, TURN_SPEED);
  drive_chassis(40, DRIVE_SPEED);
  ace::flap_toggle(true);
  turn_chassis(-100, TURN_SPEED);
  drive_chassis(70, DRIVE_SPEED);
  drive_chassis(-30, DRIVE_SPEED);




// sad
  /*
  drive_chassis(-20.5, ace::AUTON_DRIVE_SPEED, true);
  // flag
  turn_chassis(-190, ace::AUTON_TURN_SPEED, true);
  // 200


  ace::intakeMotorLeft.move_voltage(80 * 120);

  drive_chassis(55.35, ace::AUTON_DRIVE_SPEED, true);
  // drive to other side

  ace::flapPneumatics.set_value(0);

  turn_chassis(90, ace::AUTON_TURN_SPEED, true);
  // 90
  //  ace::intakePneumatics.set_value(0);

  // 30
  drive_chassis(16.4, ace::AUTON_DRIVE_SPEED, true);

  ace::intakeMotorLeft.move_voltage(90);

  drive_chassis(-16.4, ace::AUTON_DRIVE_SPEED, true);

  turn_chassis(80, ace::AUTON_DRIVE_SPEED, true);

  drive_chassis(22.55, ace::AUTON_DRIVE_SPEED, true);
  // drive_chassis(-30, ace::AUTON_DRIVE_SPEED, true);
  //  resume run second back out

  turn_chassis(-29, ace::AUTON_TURN_SPEED, true);

  drive_chassis(30.75, ace::AUTON_DRIVE_SPEED, true);
  // 55

  turn_chassis(45, ace::AUTON_TURN_SPEED, true);

  drive_chassis(20.5, ace::AUTON_DRIVE_SPEED, true);

  turn_chassis(130, ace::AUTON_TURN_SPEED, true);

  ace::flapPneumatics.set_value(1);

  ace::intakeMotorLeft.move_voltage(80 * 120);

  drive_chassis(22.55, ace::AUTON_DRIVE_SPEED, true);

  ace::intakeMotorLeft.move_voltage(0);

  drive_chassis(-4.1, ace::AUTON_DRIVE_SPEED, true);

  ace::flapPneumatics.set_value(0);

  turn_chassis(45, ace::AUTON_TURN_SPEED, true);
  // 95
  drive_chassis(41, ace::AUTON_DRIVE_SPEED, true);

  turn_chassis(185, ace::AUTON_TURN_SPEED, true);

  drive_chassis(22.55, ace::AUTON_DRIVE_SPEED, true);
  */
}

/* ========================================================================== */
/*                         Auton Function Definitions                         */
/* ========================================================================== */

/* ------------------------------ Auton Page Up ----------------------------- */
void auton_page_up() {
  auton_selection_index += 1;
  if (auton_selection_index > auton_selection.size() - 1) {
    auton_selection_index = 0;
  }
}

/* ----------------------------- Auton Page Down ---------------------------- */
void auton_page_down() {
  auton_selection_index -= 1;
  if (auton_selection_index < 0) {
  }
  auton_selection_index = auton_selection.size() - 1;
}

/* ------------------------------ Roller Auton ------------------------------ */

void roller_auton(float rollerDegrees) {
  float actual_degrees = rollerDegrees * 3.0;
  // Untested, previously only for 1 motor
  intakeMotor.move_relative(actual_degrees, 100);

  while (intakeMotor.is_stopped() == 0) {
    pros::delay(ez::util::DELAY_TIME);
  }
}

/* --------------------------- Drive Chassis Auton -------------------------- */
void drive_chassis(float distance, float speed, bool wait) {
  bool slew_enabled = false;  // distance >= 14;
  chassis.set_drive_pid(distance, speed, slew_enabled);
  if (wait) {
    chassis.wait_drive();
  }
}

/* --------------------------- Turn Chassis Auton --------------------------- */
void turn_chassis(float angle, float speed, bool wait) {
  chassis.set_turn_pid(angle, speed);
  if (wait) {
    chassis.wait_drive();
  }
}

/* ------------------------------ Launch Auton ------------------------------ */
/*void launch_auton(float time, float speed, bool isLong, bool early_exit) {

  ace::util::timer launch_timer(time);

  int launchedCounter = 0;
  while (1)
  {
    //launch(speed, isLong);
      launch(speed);
    // detect if disk launched
    if (light_sensor_detect())
    {
      launchedCounter++;
      long_launch_timer.reset();
    }

    // if 3, exit
    if (launchedCounter >= 3 && early_exit)
    {
      //break;
    }

    // Timer
    launch_timer.update(ez::util::DELAY_TIME);
    if (launch_timer.done())
    {
      break;
    }

    pros::delay(ez::util::DELAY_TIME);
  }
  launcherMotor.spin_percent(0);
}
*/

void launch_auton(float speed) {
  launch(ace::launch_speed);

}

/* ------------------------------ Endgame Auton ----------------------------- */
/*void endgame_auton() {
  endgame_toggle(true);
  while (!endgame_timer.done()) {
    pros::delay(ez::util::DELAY_TIME);
    endgame_toggle(false);
  }
  endgame_toggle(false);
}*/
}  // namespace ace::auton
/*
*     _________          _____________     _________________    ______________
*    /          \       |    _____    |   |                 /  |   _______    |   
*   /    ___     \      |   |     |   |   |                /   |  |       |   |
*  /    /   \     \     |   |     |   |   |________       /    |  |       |   |
* |_____|   /     /     |   |     |   |           /      /     |  |       |   |
*          /     /       \   \___/    /          /      /      |  |_______|   |
*         /     /         \          /          /      /       |__________    |
*        /     /          /   ____   \         /      /                   |   |
*       /     /          /   /    \   \       /      /                    |   |
*      /     /          |   |      |   |     /      /                     |   |
*     /     /_______    |   |      |   |    /      /                      |   | 
*    |              |   |   |______|   |   /      /                       |   |
*    |______________|   |______________|  /______/                        |___|  
*/

/*
* TEAM 2879 robot code
* Version unknown - continuing pre-kickoff development
* 
*/

/*
*   HARDWARE CONFIGURATION
*   
*   Device:                      Connection:
*   --------------------------------------------------
*   (jag) Front Right            (Sidecar) PWM port #1 
*   (jag) Front Left             (Sidecar) PWM port #2
*   (jag) Back Right             (Sidecar) PWM port #3
*   (jag) Back Left              (Sidecar) PWM port #4
*   (spike) Compressor           (Sidecar) Relay port #1
*   Logitech Attack3 joystick    (Laptop)  USB port #1
*   USB Xbox controller          (Laptop)  USB port #1 (as an alternative to the joystick)
*/


#include "WPILib.h"

class River : public SimpleRobot
{
     // Misc Variables
     bool squaredInputs;  // variable used to set "squared inputs" Not actually used at this point.
     float throttle;   // used to represent the position of the "throttle" on an attack 3 joystick
     float move;  // used to represent the raw Y AXIS. AXIS #2 on the attack 3 joystick
     float spin; // used to represent the raw X AXIS. AXIS #1 on the attack 3 joystick
     
     // Relays
     
     // Motor Controllers
     Jaguar frontRight; // jag on port #1
     Jaguar frontLeft;  // jag on port #2
     Jaguar backRight;  // jag on port #3
     Jaguar backLeft;   // jag on port #4
     
     // HIDs
     Joystick driveStick;
     //Joystick derpDerp  // uncomment for xbox control
     
     // Important Stuff
     RobotDrive River_Drive;
     DriverStationLCD* userDisplay;
     
public:
    River(void):
         //as they are declared above! 
         frontRight(1),
         frontLeft(2),
         backRight(3),
         backLeft(4),
         driveStick(1),
         // derpDerp(1),   // uncomment for xbox control
         River_Drive(&frontLeft, &backLeft, &frontRight, &backRight) // River_Drive uses jags as declared above
    {
         GetWatchdog().SetExpiration(0.1);   //sets the saftey expiration for watchdog
         River_Drive.SetExpiration(0.1);     //sets safey expiration for River_Drive
         
         throttle=((.5 * driveStick.GetThrottle()) + .5); // changes throttle from raw input (-1 to 1) to (0 to 1)
         userDisplay = DriverStationLCD::GetInstance();
         userDisplay->Clear();
    }
    
    //~~~~~~~~~~~~~~ Display Utities ~~~~~~~~~~~~~~~~~~
    void clearlineOne(void) {   // Clears line #1
       userDisplay->Printf(DriverStationLCD::kUser_Line1, 1, "                   ");
       userDisplay->UpdateLCD();
    }
    void clearlineTwo(void) {   // Clears line #2
       userDisplay->Printf(DriverStationLCD::kUser_Line2, 1, "                   ");
       userDisplay->UpdateLCD();
    }
    void clearlineThree(void) {   // Clears line #3
       userDisplay->Printf(DriverStationLCD::kUser_Line3, 1, "                   ");
       userDisplay->UpdateLCD();
    }
    void clearlineFour(void) {   // Clears line #4
       userDisplay->Printf(DriverStationLCD::kUser_Line4, 1, "                   ");
       userDisplay->UpdateLCD();
    }
    void clearlineFive(void) {   // Clears line #5
       userDisplay->Printf(DriverStationLCD::kUser_Line5, 1, "                   ");
       userDisplay->UpdateLCD();
    }
    void clearlineSix(void) {   // Clears line #6
       userDisplay->Printf(DriverStationLCD::kUser_Line6, 1, "                   ");
       userDisplay->UpdateLCD();
    }
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    
    //~~~~~~~~~~~~ Motor Control ~~~~~~~~~~~~~~~~~~~~~~~
    void allJags (float speed) { // sets all the jags 
        frontRight.Set (speed);
        frontLeft.Set (speed);
        backRight.Set (speed);
        backLeft.Set (speed);
    }
    void rightJags (float speed) { // sets just the right jags 
        frontRight.Set (speed);
        backRight.Set (speed);
    }
    void leftJags (float speed) { // sets just the left jags
        frontLeft.Set (speed);
        backLeft.Set (speed);
    }
    void rotateRight (float speed) { // roates the robot Right
        rightJags (-speed);
        leftJags (speed);
    }
    void roateLeft (float speed) { // rotates the robot Left
        rightJags (speed);
        leftJags (-speed);
    }
    void strafeLeft(float speed) { // strafes Left at a given speed
        frontRight.Set(speed);
        frontLeft.Set(-speed);
        backRight.Set(-speed);
        backLeft.Set(speed);
    }
    void strafeRight(float speed) { // strafes Right at a given speed
        frontRight.Set(-speed);
        frontLeft.Set(speed);
        backRight.Set(speed);
        backLeft.Set(-speed);
    }
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    
    void Autonomous(void)
    {
       rotateRight(1.0);
       Wait(10.0);   // lololololloololololololol
       allJags(0.0);
    }
    
    void OperatorControl(void)
    {
         GetWatchdog().SetEnabled(true);
         while (IsOperatorControl()) {
             
             GetWatchdog().Feed();
             
             //~~~~~~~~~~~~~ Updated Variabled and Diagnostics ~~~~~~~~~~~~~~~~~
             throttle = ((.5 * driveStick.GetThrottle()) + .5);
             move = (driveStick.GetRawAxis(2));
             spin = (driveStick.GetRawAxis(1));
             
             clearlineOne();
             clearlineTwo();
             userDisplay->Printf(DriverStationLCD::kUser_Line2, 1, "Move: %d", (int) (move*100));
             userDisplay->Printf(DriverStationLCD::kUser_Line2, 15, "Spin: %d", (int) (spin*100));
             userDisplay->Printf(DriverStationLCD::kUser_Line1, 1, "LOLz: %d", (int) (throttle*100));
             userDisplay->UpdateLCD();
             //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
             if (driveStick.GetTrigger()) {
                 River_Drive.MecanumDrive_Cartesian(driveStick.GetX(), driveStick.GetY(), 0.0, 0.0);
             }
             /*
              * if (derpDerp.GetRawAxis(3) > .5) {
              *    River_Drive.Mecanum_Cartesian(derpDerp.GetRawAxis(1), derpDerp.GetRawAxis(2), derpDerp.GetRawAxis(4), 0.0)
              * }
              */
             else if (driveStick.GetRawButton(3)) {
                 allJags(throttle);
                 //all of these commands can be assigned to the d pad on the xbox controler, but firt we're gonna have to figure out which buttons those are...
             }
             else if (driveStick.GetRawButton(2)){
                 allJags(-throttle);
             }
             else if (driveStick.GetRawButton(4)) {
                 strafeLeft(throttle);
             }
             else if (driveStick.GetRawButton(5)) {
                 strafeRight(throttle);
             }
             else {
             River_Drive.ArcadeDrive(spin, move, false);
             }
             /*
              * else {
              * River_Drive.ArcadeDrive(derpDerp.GetRawAxis(1)), derpDerp.GetRawAxis(2), false);
              * }
              */
            
         }
        
    }
    
};

START_ROBOT_CLASS(River);
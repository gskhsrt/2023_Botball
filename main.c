#include <kipr/botball.h>

// function prototype
void line_follow(int right, int left, int power, int black, int tophat, int touch);
void line_follow2(int right, int left, int power, int black, int tophat, int distance, int et);

int main()
{
    int left = 0;
    int right = 1;
    int touch = 0;
    int claw = 0;
    int open = 400;
    int closed = 1500;
    int tophat = 0;
    int black = 3000;
    int black2 = 1000;
    int power;
    int distance = 550;
    int et = 1;
    
    printf("pool noodel time\n");
    enable_servos();
    set_servo_position(claw,open);
    msleep(1000);
    
    // gets out of the starting  box
    motor(left, 50);
    motor(right, 50);
    msleep(2500);
    
    ao();
    msleep(500);
    
    while (analog(tophat) <= black)
    {
    	motor(left, 25);
    	msleep(100);
    }
    
    ao();
    // motor(left, 25);
    msleep(650);
    // line follows toward the pool noodel until the touch sensor is booped
    power = 35;
    line_follow(right, left, power, black, tophat, touch);
    
    printf("I got out of the while loop\n");
    
    // turns a bit to get noodel align
    motor(left, 0);
    motor(right, 25);
    msleep(1000);
    
    ao();
    msleep(2000);
    
    // grabs the noodel by moving the right side of the arm
    set_servo_position(claw, closed);
    msleep(1000);
    
    // backs up a bit to get the touch sensor off
    motor(right, -25);
    motor(left, -25);
    msleep(5000);

    // ------------------------------------------------------
    // dropping off pool noodle
    
    // turns right a bit to get off the line
    motor(left, 25);
    msleep(2000);
    
    // turns until it finds black
    while (analog(tophat) <= black2)
    {
    	motor(left, 25);
    	msleep(250);
    }
    
    // goes forward
    motor(left, 25);
    motor(right, 25);
    msleep(5000);
    
    // opens claw
    ao();
    set_servo_position(claw, open);
    msleep(1000);
    
    //--------------------------------------------
    
    // turns left to line follow
    motor(left, 50);
    msleep(3000);
    
    // finds the black line to center itself
    while (analog(tophat) <= black2)
    {
    	motor(left, 50);
    	msleep(250);
    }
    
    ao();
    msleep(2000);
    
    motor(left, 0);
    motor(right, 25);
    msleep(1000);
    
    // line follows on the black until it reaches the correct distance
    line_follow2(right, left, power, black2, tophat, distance, et);
    
    // line follows on the black until it catches the blue tower
   	line_follow2(right, left, power, black2, tophat, distance, et);
    
    // backwards
   //  motor(left, -50);
    // motor(right, -50);
    // msleep(2000);
    ao();
    msleep(500);
        
    // motor(right, 50);
    // motor(left, 50);
   //  msleep(1500);
    
    motor(left, 50);
    motor(right, 0);
    msleep(3000);
    
    // turns right to line follow
    while (analog(tophat) <= black2)
    {
        motor(left, 25);
        motor(right, 25);
        msleep(500);
        printf("%d\n", analog(tophat));
    }
    printf("\nI found the grey");
        
   	// line follows on the grey until it bumps
    line_follow(right, left, power, black2, tophat, touch);
    
 
    // turns a bit to get noodel align
    motor(right, 25);
    msleep(1500);
    
    ao();
    msleep(2000);
    
    // grabs the noodel by moving the right side of the arm
    set_servo_position(claw, closed);
    msleep(3000);
    
    // backs up until it reaches the black line
    while (analog(tophat) <= black)
    {
        motor(left, -25);
        motor(right, -25);
        msleep(500);
    }
    
    // turns right
    motor(left, 25);
    msleep(2000);
    
    power = -35;
    
    // line follows on the black
   	line_follow2(right, left, power, black2, tophat, distance, et);
    
    ao();
    disable_servos();
    return 0;
}

//-------------------------------------------------------------------
/*
- line follow accepts port numbers and the power value
- to either back up or go forward in the line following
- line follows
*/

void line_follow(int right, int left, int power, int black, int tophat, int touch)
{
    while (digital(touch) == 0)
    {
        // if sees black goes forward
        if (analog(tophat) >= black)
        {
            motor(left, power + 10);
            motor(right, power);
            msleep(500);
            
            motor(left, 0);
            motor(right, power);
            msleep(500);
        }
        // if sees white turns right
        else
        {
            motor(left, power);
            motor(right, 0);
            msleep(500);
            
            // checker to make sure it doesn't get stuck in the turning
            if (analog(tophat) >= black)
        	{
                motor(left, power);
                motor(right, power);
                msleep(500);
                
                motor(left, 0);
            	motor(right, power);
            	msleep(500);
        	}
            // if sees white turns left
            else
            {
                motor(left, 0);
                motor(right, power);
                msleep(500);


            }
        }
    }
}
    
//-------------------------------------------------------------------
/*
- line follow accepts port numbers and the power value
- to either back up or go forward in the line following
- line follows
*/

void line_follow2(int right, int left, int power, int black, int tophat, int distance, int et)
{
    while (analog(et) >= distance)
    {
        printf("%d\n", analog(et));
        
        // if sees black goes forward
        if (analog(tophat) <= black)
        {
            motor(left, power + 10);
            motor(right, power);
            msleep(150);
            
            motor(left, 0);
            motor(right, power);
            msleep(150);
        }
        // if sees white turns right
        else
        {
            motor(left, power);
            motor(right, 0);
            msleep(400);
            
            // checker to make sure it doesn't get stuck in the turning
            if (analog(tophat) >= black)
        	{
                motor(left, power);
                motor(right, power);
                msleep(400);
                
                motor(left, 0);
            	motor(right, power);
            	msleep(400);
        	}
            // if sees white turns left
            else
            {
                motor(left, 0);
                motor(right, power);
                msleep(400);


            }
        }
    }
}

#include "_Can.h"
#include "all_line.h"
#include "main.h"
#include "pid.h"
#include "Motor.h"
uint16_t time_3508=800;
uint8_t action_time3508=0;
typedef struct {
    float Kp;  
    float Ki;  
    float Kd;  
    float setpoint;  
    float error_sum;  
    float last_error;  
	  float error;
} PIDController;
PIDController Power_r;
PIDController Power_l;
float PIDController_computeinner(PIDController* pid1, float input, float dt,float Kp, float Ki, float Kd, float setpoint)
 {   
    pid1->Kp = Kp;
    pid1->Ki = Ki;
    pid1->Kd = Kd;
    pid1->setpoint = setpoint;
    pid1->error_sum = 0;
    pid1->last_error = 0;
	 
    pid1->error = pid1->setpoint - input;
	
    pid1->error_sum += pid1->error * dt;
    float error_delta = (pid1->error - pid1->last_error) / dt;
    float output1 = pid1->Kp * pid1->error+ pid1->Ki * pid1->error_sum + pid1->Kd * error_delta;
    pid1->last_error = pid1->error;
    if(output1<-15000)
			 output1=-15000;
		if(output1>15000)
			 output1=15000;
    return output1;
	}
void Power_on_3508check()
{  
	 time_3508--;
	if(time_3508>10)
	{  
		CAN_send(&hcan1, 0x200,PIDController_computeinner(&Power_r, RM3508_Right.data.rawSpeed, 0.05,5, 0, 0, -500) ,0,0,PIDController_computeinner(&Power_l, RM3508_Left.data.rawSpeed, 0.05,5, 0, 0, 500));
		if(RM3508_Right.data.rawSpeed<-200&&RM3508_Left.data.rawSpeed>200)
		 {
		   action_time3508++;
			 if(action_time3508>=200)
			   {
				   action_time3508=200;
					 status.power_on_3508stutas=1;
				 }
		 }
		 else 
		 {
		    if(status.power_on_3508stutas==1)
				{status.power_on_3508stutas=1;}
				else 
				{status.power_on_3508stutas=0;}
		 }
	}
	if(time_3508<=5)
	{time_3508=5;}
}
void all_line_check()
{ 
	status.RM3508_Yaw_time++;
	status.RM3508_Right_time++;
	status.RM3508_Left_time++;
	status.RM2006_Shoot_time++;
	status.MG4005_Pitch_time++;
	status.Gyro_time++;
	status.romote_time++;
	status.self_aiming_time++;
        if (status.RM3508_Yaw_time >= 50)
				{
						if(status.RM3508_Yaw_time>55)
						{status.RM3508_Yaw_time=50;}
						 status.RM3508_Yaw_status = off_line;
				}
				else
           status.RM3508_Yaw_status = on_Line;
       
				if (status.RM3508_Right_time>= 50)
				{ 
						if(status.RM3508_Right_time> 55)
						{status.RM3508_Right_time=50;}
						status.RM3508_Right_status = off_line;
				}
        else
            status.RM3508_Right_status = on_Line;
       
				if (status.RM3508_Left_time >= 50)
				{  
						if(status.RM3508_Left_time >=55)
						{status.RM3508_Left_time=50;}
						status.RM3508_Left_status = off_line;
				}
        else
             status.RM3508_Left_status = on_Line;
       
				if (status.RM2006_Shoot_time >= 50)
				{
						if(status.RM2006_Shoot_time >55)
						{status.RM2006_Shoot_time=50;}
						status.RM2006_Shoot_status = off_line;
				}
        else
            status.RM2006_Shoot_status = on_Line;
       
				if (status.MG4005_Pitch_time >= 50)
					{ if(status.MG4005_Pitch_time >55)
						{status.MG4005_Pitch_time=50;}
						status.MG4005_Pitch_status = off_line;
				}
					else
           status.MG4005_Pitch_status = on_Line;
       
				if (status.Gyro_time >= 50)
				{ if(status.Gyro_time > 55)
					{status.Gyro_time=50;}
				  status.Gyro_status = off_line;
				}
        else
            status.Gyro_status= on_Line;  
				
       if (status.romote_time >= 50)
				{ if(status.romote_time > 55)
					{status.romote_time=50;}
				  status.romote_status = off_line;
				}
        else
            status.romote_status= on_Line; 	

       if (status.self_aiming_time >= 50)
				{ if(status.self_aiming_time > 55)
					{status.self_aiming_time=50;}
				  status.self_aiming_status = off_line;
				}
        else
            status.self_aiming_status= on_Line; 						
      //Power_on_3508check();
}



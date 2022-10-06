/*
 ============================================================================
 Name        : C_Project.c
 Author      : Mohamed Khaled
 Description : Vehicle Control system
 ============================================================================
 */

#include <stdio.h>

#define WITH_ENGINE_TEMP_CONTROLLER 1

/* enum for states of systems */
typedef enum
{
	ON, OFF
}state;

/* struct that represent vehicle state */
typedef struct
{
	int speed, room_temperature;

#if WITH_ENGINE_TEMP_CONTROLLER == 1
	int engine_temperature;
	state engine_temperature_controller;
#endif

	state engine, ac;
}vehicle_state;

/* sensors_set_menu function prototype */
void sensors_set_menu(void);

/* Set_the_traffic_light_color function prototype */
void Set_the_traffic_light_color(vehicle_state * ptr);

/* Set_the_room_temperature function prototype */
void Set_the_room_temperature(vehicle_state * ptr);

#if WITH_ENGINE_TEMP_CONTROLLER == 1

/* Set_the_engine_temperature function prototype */
void Set_the_engine_temperature(vehicle_state * ptr);
#endif

/* speed_is_30 function prototype */
void speed_is_30(vehicle_state * ptr);

/* display_the_current_vehicle_state function prototype */
void display_the_current_vehicle_state(vehicle_state * ptr);

/* Start of program is from main function */
int main(void) {

	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	/* variable to store what the user will choose from the list */
	char input='\0';

	/* do...while loop to show the list before taking an input */
	do{

		/* list */
		printf("a. Turn on the vehicle engine\n");
		printf("b. Turn off the vehicle engine\n");
		printf("c. Quit the system\n\n");
		scanf(" %c",&input);

		/* if user choose Turn off the vehicle engine print it and show the list and ask for another input */
		if(input=='B'||input=='b')
		{
			printf("Turn off the vehicle engine\n\n");
		}

		/* if user choose Turn on the vehicle engine
		 * show the sensors set menu by calling a function to display it
		 * and return from function when the user choose Turn off the vehicle engine
		 * and show this list again and wait for input */
		else if(input=='A'||input=='a')
		{
			sensors_set_menu();
			input='b';
		}

	}while(input=='B'||input=='b'); /* condition if user choose Turn off the vehicle engine keeping showing the list */

	/* if user choose Quit the system print it and terminate the program */
	if(input=='C'||input=='c')
	{
		printf("Quit the system\n");
	}

	return 0;
}

/* sensors_set_menu function */
void sensors_set_menu(void)
{
#if WITH_ENGINE_TEMP_CONTROLLER == 1

	/* variable of structure vehicle_state type Initialized. In addition,
	 * it will store the data for Vehicle Control system */
	vehicle_state myCar={0, 35, 90, OFF, ON, OFF};
#else

	/* variable of structure vehicle_state type Initialized. In addition,
	 * it will store the data for Vehicle Control system */
	vehicle_state myCar={0, 35, ON, OFF};
#endif


	/* variable to store what the user will choose from the menu */
	char inp='\0';

	/* do...while loop to show the list before taking an input */
	do{
		/* if user choose Set the traffic light color
		 * call Set_the_traffic_light_color function
		 * that takes a struct by reference since the function will change the variable */
		if(inp=='b'||inp=='B')
		{
			Set_the_traffic_light_color(&myCar);
		}

		/* if user choose Set the room temperature (Temperature Sensor)
		 * call Set_the_room_temperature function
		 * that takes a struct by reference since the function will change the variable */
		else if(inp=='c'||inp=='C')
		{
			Set_the_room_temperature(&myCar);
		}
#if WITH_ENGINE_TEMP_CONTROLLER == 1

		/* if user choose Set the engine temperature (Engine Temperature Sensor)
		 * call Set_the_engine_temperature function
		 * that takes a struct by reference since the function will change the variable */
		else if(inp=='d'||inp=='D')
		{
			Set_the_engine_temperature(&myCar);
		}
#endif

		/* to display the vehicle state after the user has already entered a value */
		if(inp!='\0')
		{
			display_the_current_vehicle_state(&myCar);
		}

		/* menu */
		printf("a. Turn off the engine\n");
		printf("b. Set the traffic light color\n");
		printf("c. Set the room temperature (Temperature Sensor)\n");

#if WITH_ENGINE_TEMP_CONTROLLER == 1
		printf("d. Set the engine temperature (Engine Temperature Sensor)\n");
#endif

		printf("\n");
		scanf(" %c",&inp);
	}while(inp!='a'&&inp!='A'); /* condition continue as long as the user doesn't choose Turn off the engine */

}

/* Set the traffic light color function */
void Set_the_traffic_light_color(vehicle_state * ptr)
{
	/* variable to store what the user will enter */
	char inp;

	printf("Enter the required color:\n");
	scanf(" %c", &inp);

	/* switch case to choose speed of car according to traffic light color */
	switch(inp)
	{
	case 'g':
	case 'G':
		ptr->speed=100;
		break;
	case 'o':
	case 'O':
		ptr->speed=30;
		break;
	case 'r':
	case 'R':
		ptr->speed=0;
		break;
	default :
		printf("Invalid Character\n");
	}

	/* if speed is 30 call speed_is_30 function
	 * that takes a struct by reference since the function will change the variable */
	if(ptr->speed==30)
	{
		speed_is_30(ptr);
	}
}

/* Set_the_room_temperature function */
void Set_the_room_temperature(vehicle_state * ptr)
{
	/* variable to store what the user will enter */
	int temp;

	printf("Enter the required room temp:\n");
	scanf("%d", &temp);

	if(temp<10)
	{
		ptr->ac=ON;
		ptr->room_temperature=20;
	}
	else if(temp>30)
	{
		ptr->ac=ON;
		ptr->room_temperature=20;
	}
	else
	{
		ptr->ac=OFF;
		ptr->room_temperature=temp;
	}
}

#if WITH_ENGINE_TEMP_CONTROLLER == 1

/* Set_the_engine_temperature function */
void Set_the_engine_temperature(vehicle_state * ptr)
{
	/* variable to store what the user will enter */
	int temp;

	printf("Enter the required engine temperature:\n");
	scanf("%d", &temp);

	if(temp<100)
	{
		ptr->engine_temperature_controller=ON;
		ptr->engine_temperature=125;
	}
	else if(temp>150)
	{
		ptr->engine_temperature_controller=ON;
		ptr->engine_temperature=125;
	}
	else
	{
		ptr->engine_temperature_controller=OFF;
		ptr->engine_temperature=temp;
	}
}

#endif
/* speed_is_30 function */
void speed_is_30(vehicle_state * ptr)
{
	if(ptr->ac==OFF)
	{
		ptr->ac=ON;
	}

	ptr->room_temperature=((float)ptr->room_temperature*5)/4+1;

#if WITH_ENGINE_TEMP_CONTROLLER == 1
	if(ptr->engine_temperature_controller==OFF)
	{
		ptr->engine_temperature_controller=ON;
	}

	ptr->engine_temperature=((float)ptr->engine_temperature*5)/4+1;
#endif
}

/* display_the_current_vehicle_state function */
void display_the_current_vehicle_state(vehicle_state * ptr)
{
	/* Engine State */
	printf("Engine is ON\n");

	/* AC State */
	printf("AC is ");
	puts((ptr->ac==ON)?"ON":"OFF");

	/* Vehicle Speed */
	printf("Vehicle Speed: %d Km/Hr\n", ptr->speed);

	/* Room Temperature */
	printf("Room Temperature: %d C\n", ptr->room_temperature);

#if WITH_ENGINE_TEMP_CONTROLLER == 1

	/* Engine Temperature Controller State */
	printf("Engine Temperature Controller is ");
	puts((ptr->engine_temperature_controller==ON)?"ON":"OFF");

	/* Engine Temperature */
	printf("Engine Temperature: %d C\n", ptr->engine_temperature);
#endif

	printf("\n");
}

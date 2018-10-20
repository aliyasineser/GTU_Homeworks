#include <stdio.h>

#define ROADLENGTH 50

typedef enum State
{
	PLAY,
	CRASH,
	END
} object_state;

/*
Prints road, each car’s location and letter symbols to the console. When game_state is PLAY shows 
two cars, otherwise just displays one so that they have same position value at CRASH and END states.
*/
void
print_game_state(char object1, double pos1, char object2, double pos2, object_state game_state);

/*
Returns crash time as double. When a crash is going to happen, use this function to determine crash time.
*/
double
car_crash_time(double p1, double p2, double s1, double s2);

/*
Moves each car according to their speed. Updates output parameters. Changes object1 and object2 
to ‘X’ character when the crash happens. Changes speed1 and speed2 (inelastic collision) as well. 
Note that after crash, they will move together and their position and speed will be same. Updates 
game_state variable value when necessary, according to the situation.
*/
void
make_move(char *object1, double *pos1, double *speed1, int weight1,
	char *object2, double *pos2, double *speed2, int weight2, object_state *game_state);


int
main(int argc, char* argv[])
{
	char object1, object2;
	double speed1, speed2, pos1 = 1, pos2 = ROADLENGTH;
	int weight1, weight2;
	object_state game_state = PLAY;

	printf("Please enter character of 1st item:");
	scanf("%c", &object1);

	printf("Please enter character of 2nd item:");
	scanf(" %c", &object2);

	printf("Please enter speed of 1st item:");
	scanf(" %lf", &speed1);

	printf("Please enter speed of 2nd item:");
	scanf("%lf", &speed2);

	printf("Please enter weight of 1st item:");
	scanf("%d", &weight1);

	printf("Please enter weight of 2nd item:");
	scanf("%d", &weight2);

	print_game_state(object1, pos1, object2, pos2, game_state);
	do
	{
		make_move(&object1, &pos1, &speed1, weight1, &object2, &pos2, &speed2, weight2, &game_state);
		print_game_state(object1, pos1, object2, pos2, game_state);
	}while(game_state != END);
	printf("\nEnd!\n");

	return 0;
}

/*
Prints road, each car’s location and letter symbols to the console. When game_state is PLAY shows 
two cars, otherwise just displays one so that they have same position value at CRASH and END states.
*/
void
print_game_state(char object1, double pos1, char object2, double pos2, object_state game_state)
{
	int i;
	int flag;

	/* do not print second car after CRASH trick */
	if(game_state == CRASH || game_state == END)
		pos2 = 2*ROADLENGTH;

	printf("\n");
	for(i=1; i<=ROADLENGTH; ++i)
	{
		flag = 1;
		
		if(i == (int)pos1)
		{
			printf("%c", object1);
			flag=0;
		} 
		if(i == (int)pos2)
		{
			printf("%c", object2);
			flag=0;
		}

		if(flag == 1)
		{
			printf("_");
		}
		
	}
	printf("\n");
	for(i=1; i<=ROADLENGTH; ++i)
	{
		printf("%d", i%10);
	}
	printf("\n");

}

/*
Returns crash time as double. When a crash is going to happen, use this function to determine crash time.
*/
double
car_crash_time(double p1, double p2, double s1, double s2)
{
	double diff, speed, time;
	diff = p1-p2;
	if(diff < 0)
		diff *= -1;

	if(s1<0)
		s1 *= -1;

	if(s2<0)
		s2 *= -1;
	
	speed = s1 + s2;
	time = diff/speed;

	return time;
}

/*
Moves each car according to their speed. Updates output parameters. Changes object1 and object2 
to ‘X’ character when the crash happens. Changes speed1 and speed2 (inelastic collision) as well. 
Note that after crash, they will move together and their position and speed will be same. Updates 
game_state variable value when necessary, according to the situation.
*/
void
make_move(char *object1, double *pos1, double *speed1, int weight1,
	char *object2, double *pos2, double *speed2, int weight2, object_state *game_state)
{	
	double next_pos1, next_pos2, crash_time;
	double momentum1, momentum2, momentum_all;

	next_pos1 = *pos1 + *speed1;
	next_pos2 = *pos2 + *speed2;

	/* if crash is going to happen */
	if(next_pos1 > next_pos2)
	{
		crash_time = car_crash_time(*pos1, *pos2, *speed1, *speed2);
		next_pos1 = next_pos2 = *pos1 + crash_time * *speed1;

		*game_state = CRASH;
		momentum1 = *speed1 * weight1;
		momentum2 = *speed2 * weight2;

		momentum_all = momentum1 + momentum2;
		*speed1 = *speed2 = momentum_all / (weight1 + weight2);

		*object1 = 'X';
		*object2 = 'X';
	}

	/* out of range situation for car1 */
	if(next_pos1 > ROADLENGTH)
	{
		next_pos1 = ROADLENGTH;
	} else if (next_pos1 < 1)
	{
		next_pos1 = 1;
	}

	/* out of range situation for car2 */
	if(next_pos2 > ROADLENGTH)
	{
		next_pos2 = ROADLENGTH;
	} else if (next_pos2 < 1)
	{
		next_pos2 = 1;
	}

	/* no movement situation */
	if(*pos1 == next_pos1 && *pos2 == next_pos2)
	{
		*game_state = END;
	}

	*pos1 = next_pos1;
	*pos2 = next_pos2;

	/* cars came to end together and no movement situation */
	if( (next_pos1 == next_pos2 )&& (next_pos1 == 1 || next_pos1 == ROADLENGTH) )
	{
		*game_state = END;
	}	
}
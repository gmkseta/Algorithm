#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#define norm_rand() (rand()/(RAND_MAX + 1.0))
#define S 10

double expntl(double);
int main()
{
	int n;//n은 현재 있는 customer 수인듯

		  //arrival time , Service time
	double Ta = 200.0, Ts = 100.0, simulation_time = 200000.0, next_arrival_time, next_departure_time;

	double elapsed_time;

	double B, C, L, s, tb, tn, U, W, X;
	/************************

	s : 가게 안에 있는 고객 수 * 그때 머문 시간
	L : 시간당 가게 안에 있는 평균 고객 수 =  s / elapsed_time


	W : 고객당 평균 머문 시간		=  L/X
	U : 효율 . = 일한 시간 / 전체 시간

	C : 서비스한 고객 수
	X : 단위시간당 처리율 = C / elapsed_time

	*************************/
	n = 0; next_arrival_time = 0.0;
	next_departure_time = simulation_time; elapsed_time = 0.0;
	//일단 출발시간 겁나 멀리해놓고 .

	B = s = 0.0; C = 0; tn = elapsed_time;
	

	/* Seed the random-number generator with current time so that the number will be dif ferent every time we run.*/

	srand((unsigned)time(NULL));

	while (elapsed_time < simulation_time)//경과된 시간이 시뮬레이션 시간보다 적을 때.
	{	//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
		//     ㅣ  next_arrival_time                 ㅣ next_departure_time
		if (next_arrival_time < next_departure_time)
		{ /* event 1 : customer arrival */
			elapsed_time = next_arrival_time;

			s += n*(elapsed_time - tn); //elapsed_time - tn 은 지난 시간이고 n 은 그동안 안에 있던 사람 수 임 . 즉 s는 사람들 있던 시간.
			n++;//n 증가시켜줌
			tn = elapsed_time;//지금으로 시점 옮겨주고~

			next_arrival_time = elapsed_time + expntl(Ta);//다음 도착시간 계산

			if (n ==1) //아,... n++ 
			{//고객 한명일 때
				tb = elapsed_time; //tb에 경과시간 넣어주고 아마 출발이 더 빠르면
				next_departure_time = elapsed_time + expntl(Ts); //다음 출발시간 ( 서비스 하고나서 출)발
			}
		}
		//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
		//    ㅣ next_departure_time                 ㅣ  next_arrival_time 
		else
		{ /* event 2 : customer departure */
			elapsed_time = next_departure_time; //시간 경과 시켜주고
			s += n*(elapsed_time - tn); //이거도 마찬가지고
			n--; //줄여주고
			tn = elapsed_time; //~~
			C++;//서비스 한 Customer 수 증가
			if (n > 0) next_departure_time = elapsed_time + expntl(Ts);//안에 있는 사람이 있을때임
			else {
				next_departure_time = simulation_time;
				B += elapsed_time - tb;
			}//B는 서버가 일한 시간인듯 그럼
		}

	}


	X = C / elapsed_time; printf("throughput = %f\n", X);
	U = B / elapsed_time; printf("utilization = %f\n", U);
	L = s / elapsed_time; printf("mean customer no. in store = %f \n", L);
	W = L / X; printf("mean residence time per customer = %f \n", W);
}

double expntl(double x)
{ /* 'expntl' returns a psuedo -random variate from a negative exponen tial distribution with mean x */
	return(-x*log(norm_rand()));
}


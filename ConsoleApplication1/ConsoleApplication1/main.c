#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#define norm_rand() (rand()/(RAND_MAX + 1.0))
#define sits 10 //우동가게 좌석의 수
#define cost 4000 //우동의 가격(원)
//#define simulation_TIME 200000.0
#define simulation_TIME 200000.0

typedef enum bool{ true = 1,false = 0 } bool;
double expntl(double);
double shortest_departure_time(double time_table[]);
bool insert_time_table(double time_table[], double value);
bool delete_shortest_time(double time_table[]);



int main()
{
	double time_table[sits] = { 0, }; //각 서버의 departure time을 관리
	int n, queue; //시스템 내의 전체 고객 수(n), 대기줄의 수(q)
	double Ta = 200.0, Ts = 100.0,
		//평균 Ta 동안에 손님이 한명 도착 (1/lambda) 200
		//평균 Ts 동안에 손님이 한명 서비스 를 받고 나감 (1/mu) 100
		simulation_time,
		next_arrival_time,  //다음 도착 시간
		next_departure_time, //다음 서비스 처리 시간
		elapsed_time, //총 경과된 시간
		now_departure_time; //손님별 departure Time을 계산하기 위한 변수
	double B, C, L, s, tb, tn, U, W, X, Y, q, Lq, Wq;
	n = queue = 0;
	simulation_time = simulation_TIME;
	next_arrival_time = 0.0;
	next_departure_time = simulation_time;
	elapsed_time = 0.0;
	B = s = q = 0.0;
	C = 0;
	tn = elapsed_time;
	int max_n = 0;
	double total_cost = 0.0;
	/* Seed the random-number generator with current time so that the number will be dif ferent every time we run.*/
	srand((unsigned)time(NULL));


	while (elapsed_time < simulation_time)
	{
		if (next_arrival_time < next_departure_time)
		{ /* event 1 : customer arrival */
			elapsed_time = next_arrival_time; //경과시간 계산
			s += n*(elapsed_time - tn); //손님별 시스템에 머문 시간을 누적 계산
			q += queue*(elapsed_time - tn); //손님별 대기줄에 머문 시간을 누적 계산
			n++;

			/*학부생 추가*/
			total_cost += cost; //총매출
			if (max_n < n) max_n = n; //최대 손님수
									  //추가 끝

			tn = elapsed_time;
			next_arrival_time = elapsed_time + expntl(Ta); //다음 도착시간 계산
			if (n == 1) tb = elapsed_time; //손님이 처음 들어왔을 때부터 로봇이 움직인다.
			if ((n <= sits) && (n >= 1)) {  //손님이 도착하고나서, n이 1명 ~ 10명 일때
				now_departure_time = elapsed_time + expntl(Ts); //손님의 끝나는 시간을 계산
				insert_time_table(&time_table, now_departure_time);
				next_departure_time = shortest_departure_time(time_table); //현재 가게에 있는 사람 중에서 가장 먼저 일어나는 사람
			}
			else if (n>sits) { //손님이 도착하고나서 n이 11명이상이면(자리가 없을때) 큐에 넣어준다
				queue++;
				printf("@@@@@@@@@@@@큐다 시발 %d", queue);
			}
		}
		else
		{ /* event 2 : customer departure */
			elapsed_time = next_departure_time; //customer arrival과 동일
			s += n*(elapsed_time - tn);
			q += queue*(elapsed_time - tn);
			n--;
			tn = elapsed_time; C++; //시간간격 계산과, 가게를 떠난 손님수 Check

									//손님이 한명 떠날때, 가장 빨리 먹은 사람이 떠난것이므로 타임테이블에서 가장 작은 값을 제거
			delete_shortest_time(&time_table);

			/**
			손님이 한명 떠나가고 나서 발생하는 경우
			1. 10자리 모두 꽉 차는경우(큐에서 손님이 1명이상 대기하고있던 경우)
			- 큐에서 한명을 데리고 오고, 해당 손님의 종료시간 계산
			2. 1자리 ~ 9자리로 남는 경우
			- 남아있는 손님중 가장 빨리 나가는 손님의 시간을 ndt에 대입
			3. 가게의 자리가 비는경우
			- 로봇의 작동이 멈추므로, 로봇의 일한 시간 +=
			*/
			if (n >= sits) { //case 1.
				queue--;
				now_departure_time = elapsed_time + expntl(Ts); //Arrival떄와 같은 방법으로 처리
				insert_time_table(&time_table, now_departure_time);
				next_departure_time = shortest_departure_time(time_table);
			}
			else if (n == 0) //case 3.
			{
				next_departure_time = simulation_time; B += (elapsed_time - tb);
			}
			else { //case 2.
				next_departure_time = shortest_departure_time(time_table);
			}
		}
	}

	X = C / elapsed_time; printf("throughput = %lf\n", X); //평균 처리율
	U = B / elapsed_time; printf("utilization = %lf\n", U); //로봇의 평균 이용률
	Y = B / C; printf("t : 로봇이 손님 한사람당 서비스한 시간 = %lf\n", Y); //로봇의 평균 이용률
	L = s / elapsed_time; printf("Ls : 전체 시스템에서 평균 손님 수 = %lf \n", L); //전체 시스템에서의 손님 수
	W = L / X; printf("Ws : 고객이 전체 시스템에서 기다리는 평균시간 = %lf \n", W); //전체 시스템에서 손님이 평균 기다리는 시간
	Lq = q / elapsed_time; printf("Lq : 평균 대기 손님 수 = %lf \n", Lq); //평균 대기줄에 머무는 손님 수
	Wq = Lq / X; printf("Wq : 평균 대기 시간 = %lf \n", Wq); //평균 큐 대기 시간
	printf("\n\n단위시간당 방문 손님의 수(lambda) : %lf\n", 1.0 / Ta);
	printf("단위시간당 가게를 떠나는 손님 수(mu)  : %lf\n", 1.0 / Ts);
	printf("총 영업시간 : %.0lf초\n", simulation_time);
	printf("영업 시간 동안 총 손님 수 : %.lf\n", total_cost / cost);
	printf("영업 시간 동안 최대 손님 수 : %d\n", max_n);
	printf("총 이익 : %.0lf원\n", total_cost);
}

double expntl(double x)
{ /* 'expntl' returns a psuedo -random variate from a negative exponen tial distribution with mean x */
	return(-x*log(norm_rand()));
}

double shortest_departure_time(double time_table[]) {
	double tmp = simulation_TIME;
	for (int i = 0; i < sits; i++) {
		if ((time_table[i] < tmp) && (time_table[i] != 0.0)) tmp = time_table[i];
	}
	return tmp;
}

bool insert_time_table(double time_table[], double value) {
	bool flag = false;
	for (int i = 0; i < sits; i++) {
		if (time_table[i] == 0.0) {
			time_table[i] = value;
			flag = true;
			break;
		}
	}
	return flag;
}

bool delete_shortest_time(double time_table[]) {
	double tmp = simulation_TIME;
	bool flag = false;
	int index = 0;
	for (int i = 0; i < sits; i++) {
		if ((time_table[i] < tmp) && (time_table[i] != 0.0)) {
			tmp = time_table[i]; index = i; flag = true;
		}
	}
	time_table[index] = 0; return flag;
}

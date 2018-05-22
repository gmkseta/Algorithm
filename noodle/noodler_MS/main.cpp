#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#define norm_rand() (rand()/(RAND_MAX + 1.0))
#define S 10

double expntl(double);
int main()
{
	int n;//n�� ���� �ִ� customer ���ε�

		  //arrival time , Service time
	double Ta = 200.0, Ts = 100.0, simulation_time = 200000.0, next_arrival_time, next_departure_time;

	double elapsed_time;

	double B, C, L, s, tb, tn, U, W, X;
	/************************

	s : ���� �ȿ� �ִ� �� �� * �׶� �ӹ� �ð�
	L : �ð��� ���� �ȿ� �ִ� ��� �� �� =  s / elapsed_time


	W : ���� ��� �ӹ� �ð�		=  L/X
	U : ȿ�� . = ���� �ð� / ��ü �ð�

	C : ������ �� ��
	X : �����ð��� ó���� = C / elapsed_time

	*************************/
	n = 0; next_arrival_time = 0.0;
	next_departure_time = simulation_time; elapsed_time = 0.0;
	//�ϴ� ��߽ð� �̳� �ָ��س��� .

	B = s = 0.0; C = 0; tn = elapsed_time;
	

	/* Seed the random-number generator with current time so that the number will be dif ferent every time we run.*/

	srand((unsigned)time(NULL));

	while (elapsed_time < simulation_time)//����� �ð��� �ùķ��̼� �ð����� ���� ��.
	{	//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
		//     ��  next_arrival_time                 �� next_departure_time
		if (next_arrival_time < next_departure_time)
		{ /* event 1 : customer arrival */
			elapsed_time = next_arrival_time;

			s += n*(elapsed_time - tn); //elapsed_time - tn �� ���� �ð��̰� n �� �׵��� �ȿ� �ִ� ��� �� �� . �� s�� ����� �ִ� �ð�.
			n++;//n ����������
			tn = elapsed_time;//�������� ���� �Ű��ְ�~

			next_arrival_time = elapsed_time + expntl(Ta);//���� �����ð� ���

			if (n ==1) //��,... n++ 
			{//�� �Ѹ��� ��
				tb = elapsed_time; //tb�� ����ð� �־��ְ� �Ƹ� ����� �� ������
				next_departure_time = elapsed_time + expntl(Ts); //���� ��߽ð� ( ���� �ϰ��� ��)��
			}
		}
		//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
		//    �� next_departure_time                 ��  next_arrival_time 
		else
		{ /* event 2 : customer departure */
			elapsed_time = next_departure_time; //�ð� ��� �����ְ�
			s += n*(elapsed_time - tn); //�̰ŵ� ����������
			n--; //�ٿ��ְ�
			tn = elapsed_time; //~~
			C++;//���� �� Customer �� ����
			if (n > 0) next_departure_time = elapsed_time + expntl(Ts);//�ȿ� �ִ� ����� ��������
			else {
				next_departure_time = simulation_time;
				B += elapsed_time - tb;
			}//B�� ������ ���� �ð��ε� �׷�
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


#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#define norm_rand() (rand()/(RAND_MAX + 1.0))
#define sits 10 //�쵿���� �¼��� ��
#define cost 4000 //�쵿�� ����(��)
//#define simulation_TIME 200000.0
#define simulation_TIME 200000.0

typedef enum bool{ true = 1,false = 0 } bool;
double expntl(double);
double shortest_departure_time(double time_table[]);
bool insert_time_table(double time_table[], double value);
bool delete_shortest_time(double time_table[]);



int main()
{
	double time_table[sits] = { 0, }; //�� ������ departure time�� ����
	int n, queue; //�ý��� ���� ��ü �� ��(n), ������� ��(q)
	double Ta = 200.0, Ts = 100.0,
		//��� Ta ���ȿ� �մ��� �Ѹ� ���� (1/lambda) 200
		//��� Ts ���ȿ� �մ��� �Ѹ� ���� �� �ް� ���� (1/mu) 100
		simulation_time,
		next_arrival_time,  //���� ���� �ð�
		next_departure_time, //���� ���� ó�� �ð�
		elapsed_time, //�� ����� �ð�
		now_departure_time; //�մԺ� departure Time�� ����ϱ� ���� ����
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
			elapsed_time = next_arrival_time; //����ð� ���
			s += n*(elapsed_time - tn); //�մԺ� �ý��ۿ� �ӹ� �ð��� ���� ���
			q += queue*(elapsed_time - tn); //�մԺ� ����ٿ� �ӹ� �ð��� ���� ���
			n++;

			/*�кλ� �߰�*/
			total_cost += cost; //�Ѹ���
			if (max_n < n) max_n = n; //�ִ� �մԼ�
									  //�߰� ��

			tn = elapsed_time;
			next_arrival_time = elapsed_time + expntl(Ta); //���� �����ð� ���
			if (n == 1) tb = elapsed_time; //�մ��� ó�� ������ ������ �κ��� �����δ�.
			if ((n <= sits) && (n >= 1)) {  //�մ��� �����ϰ���, n�� 1�� ~ 10�� �϶�
				now_departure_time = elapsed_time + expntl(Ts); //�մ��� ������ �ð��� ���
				insert_time_table(&time_table, now_departure_time);
				next_departure_time = shortest_departure_time(time_table); //���� ���Կ� �ִ� ��� �߿��� ���� ���� �Ͼ�� ���
			}
			else if (n>sits) { //�մ��� �����ϰ��� n�� 11���̻��̸�(�ڸ��� ������) ť�� �־��ش�
				queue++;
				printf("@@@@@@@@@@@@ť�� �ù� %d", queue);
			}
		}
		else
		{ /* event 2 : customer departure */
			elapsed_time = next_departure_time; //customer arrival�� ����
			s += n*(elapsed_time - tn);
			q += queue*(elapsed_time - tn);
			n--;
			tn = elapsed_time; C++; //�ð����� ����, ���Ը� ���� �մԼ� Check

									//�մ��� �Ѹ� ������, ���� ���� ���� ����� �������̹Ƿ� Ÿ�����̺��� ���� ���� ���� ����
			delete_shortest_time(&time_table);

			/**
			�մ��� �Ѹ� �������� ���� �߻��ϴ� ���
			1. 10�ڸ� ��� �� ���°��(ť���� �մ��� 1���̻� ����ϰ��ִ� ���)
			- ť���� �Ѹ��� ������ ����, �ش� �մ��� ����ð� ���
			2. 1�ڸ� ~ 9�ڸ��� ���� ���
			- �����ִ� �մ��� ���� ���� ������ �մ��� �ð��� ndt�� ����
			3. ������ �ڸ��� ��°��
			- �κ��� �۵��� ���߹Ƿ�, �κ��� ���� �ð� +=
			*/
			if (n >= sits) { //case 1.
				queue--;
				now_departure_time = elapsed_time + expntl(Ts); //Arrival���� ���� ������� ó��
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

	X = C / elapsed_time; printf("throughput = %lf\n", X); //��� ó����
	U = B / elapsed_time; printf("utilization = %lf\n", U); //�κ��� ��� �̿��
	Y = B / C; printf("t : �κ��� �մ� �ѻ���� ������ �ð� = %lf\n", Y); //�κ��� ��� �̿��
	L = s / elapsed_time; printf("Ls : ��ü �ý��ۿ��� ��� �մ� �� = %lf \n", L); //��ü �ý��ۿ����� �մ� ��
	W = L / X; printf("Ws : ���� ��ü �ý��ۿ��� ��ٸ��� ��սð� = %lf \n", W); //��ü �ý��ۿ��� �մ��� ��� ��ٸ��� �ð�
	Lq = q / elapsed_time; printf("Lq : ��� ��� �մ� �� = %lf \n", Lq); //��� ����ٿ� �ӹ��� �մ� ��
	Wq = Lq / X; printf("Wq : ��� ��� �ð� = %lf \n", Wq); //��� ť ��� �ð�
	printf("\n\n�����ð��� �湮 �մ��� ��(lambda) : %lf\n", 1.0 / Ta);
	printf("�����ð��� ���Ը� ������ �մ� ��(mu)  : %lf\n", 1.0 / Ts);
	printf("�� �����ð� : %.0lf��\n", simulation_time);
	printf("���� �ð� ���� �� �մ� �� : %.lf\n", total_cost / cost);
	printf("���� �ð� ���� �ִ� �մ� �� : %d\n", max_n);
	printf("�� ���� : %.0lf��\n", total_cost);
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

#include <cstdlib>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>
#define norm_rand() (rand()/(RAND_MAX + 1.0))
#define MAX_TABLE 10

double expntl(double);

bool descending(int i, int j) { return (i>j);}
// ���͸� ������������ �����ϱ����� �Լ�

int main()
{

	using namespace std;
	vector<double> departure_table;
	int queue = 0;
	

	int n;//n�� ���� �ִ� customer ���ε�
	//arrival time , Service time
	double Ta = 20, Ts = 100, simulation_time = 200000.0, next_arrival_time, next_departure_time;
	double elapsed_time;
	double B, C, L, s, tb, tn, U, W, X;
	departure_table.push_back(simulation_time);//dummy��

	double sumQ = 0.0, tQ = 0.0, q_len = 0.0;
	//ť�� �ִ� �� ���� �������� ������� ���� �������� ����
	//sumQ ���� ť�� ����� * �� ���� ������� �־��� �ð� ���� ����ؼ� ��������
	//tQ�� �� ���� ������� �־��� �ð��� üũ�ϱ����� �����̴�.
	//������ �ڵ忡�� B �� ����ϴ� ��İ� ���� ���������
	//B�� ����ϴ� ����� �ý��� ���� �ְ� ���� �ΰ��� ���ۿ� ������
	//ť�� ���� 1�� ������ 2�� ������ ������ �������� ��¦ �˰����� �޶�����.

	/************************
	s : ���� �ȿ� �ִ� �� �� * �׶� �ӹ� �ð�
	L : �ð��� ���� �ȿ� �ִ� ��� �� �� =  s / elapsed_time

	C : ������ �� ��
	X : �����ð��� ó���� = C / elapsed_time

	W : ���� ��� �ӹ� �ð�		=  L/X

	B : ���� �ð�
	U : ȿ��  = ���� �ð� / ��ü �ð�
	*************************/

	n = 0; next_arrival_time = 0.0;
	next_departure_time = simulation_time; elapsed_time = 0.0;
	//�ϴ� ��߽ð��� �ִ�� �س��� �������� 0���� �ʱ�ȭ

	B = s = 0.0; C = 0; tn = elapsed_time;
	
	
	/* Seed the random-number generator with current time so that the number will be dif ferent every time we run.*/
	srand((unsigned)time(NULL));

	while (elapsed_time < simulation_time)//����� �ð��� �ùķ��̼� �ð����� ���� ��.
	{	// Time line
		//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
		//     ��  next_arrival_time                 �� next_departure_time
		if (next_arrival_time < next_departure_time)
		{ /* event 1 : customer arrival */
			elapsed_time = next_arrival_time;

			s += n*(elapsed_time - tn); //elapsed_time - tn �� ���� �ð��̰� n �� �׵��� �ȿ� �ִ� ��� �� �� . �� s�� ����� �ִ� �ð�.
			n++;//n ����������

			tn = elapsed_time;//�������� ���� �Ű��ְ�

			next_arrival_time = elapsed_time + expntl(Ta);//���� �����ð� ���

			if (n ==1) //n++  n�� 0�̿��ڴ�.
			{//�� �Ѹ��� �� �� ���� ���� ���� ���°���.
				tb = elapsed_time; 
				//tb�� ����ð� �־��ش�.���� ���ݺ��� n�� 0�� �ɶ��� 
				//���� �ð��� �ǰ���?
			}//B�� ����ϱ����ؼ� 

			if (n <= MAX_TABLE)
			{
				departure_table.push_back(elapsed_time + expntl(Ts));
				//�̹��� ���� �մ��� �� �԰� ����ϴ� �ð��� ����ؼ� ���̺� �ִ´�.
				sort(departure_table.begin(), departure_table.end(), descending);
				//���Ϻ����� �Ǿտ�������
				next_departure_time = departure_table.back();
				//�� �ð����� �������ش�.
				
			}
			else
			{//ť�� �����Ǹ� ���±��� �迡 �־��� ť�� �ð����� ������ ��
				sumQ += (elapsed_time - tQ)*queue;
				queue++;// �׷��� ť ����
				tQ = elapsed_time;// �ٽ� ����� ���� ���� �ٲ��ֱ�

			}

		}
		// Time line
		//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
		//    �� next_departure_time                 ��  next_arrival_time 
		else
		{ /* event 2 : customer departure */
			elapsed_time = next_departure_time; //�ð� ��� �����ְ�
			s += n*(elapsed_time - tn); //
			n--; //�ٿ��ְ�
			tn = elapsed_time; //~~
			C++;//���� �� Customer �� ����
			
			//����� ���̺��� �� ������ ����

			departure_table.pop_back();

			if (n >= MAX_TABLE)//������ �ƽ� ���̺��̻��̿��� ������ �ڸ��� ���Ŷ��
			{//ť���� ������ �Ǹ� ���±��� �迡 �־��� ť�� �ð����� ������ ��
				sumQ += (elapsed_time - tQ)*queue;
				queue--;//ť ����
				tQ = elapsed_time;// ���� ������ ���� tQ�� �ʱ�ȭ
				

				departure_table.push_back(elapsed_time + expntl(Ts));
				//�̹��� ���� �մ��� �� �԰� ����ϴ� �ð��� ����ؼ� ���̺� �ִ´�.
				sort(departure_table.begin(), departure_table.end(), descending);
				//���Ϻ����� �Ǿտ�������
				next_departure_time = departure_table.back();
			}
			else if (n > 0) //�ƽ��� �������� �ƴ� ����. ť�� ��������
			{//�ٵ� ���� ���� ť�ϳ��� ���°Ŷ�� ����� ��¦ ���󤿶���
				next_departure_time = departure_table.back();
			}
			else if(n==0){//n �� 0�� �ɶ� ��
				next_departure_time = simulation_time;
				B += elapsed_time - tb;
			}//B�� ������ ���� �ð�
		}

	}
	sumQ += (elapsed_time - tQ)*queue;
	B += elapsed_time - tb;//���������� ����� �ѹ��� ����
	//�� ����� �����ϰ� �Ǹ� ���������� ������ �ð� tb ~ �ùķ��̼Ǥ��� ���� �ð���
	//���ѽð����� �������� �Ǳ� ������ ȿ���� �� ���� ���´�.
	//���� Q ���� ��������.
	 cout << "�� �մԼ� = " << C << endl;;
	X = C / elapsed_time; cout << "���� �ð��� ������ = " << X<<endl;;
	U = B / elapsed_time; cout<< "�κ��� ȿ��  = "<< U << endl;
	L = s / elapsed_time; cout << "���� �ð��� �մ��� �� = " << L << endl;
	W = L / X; cout<<"�� �� �ӹ� �ð� = " << W << endl;
	q_len = sumQ / elapsed_time; cout << "���� �ð��� �ټ� �մ��� ��  = " << q_len << endl;
	

}



double expntl(double x)
{ /* 'expntl' returns a psuedo -random variate from a negative exponen tial distribution with mean x */
	return(-x*log(norm_rand()));
}


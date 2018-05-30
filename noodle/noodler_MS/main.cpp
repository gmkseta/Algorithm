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
// 벡터를 내림차순으로 정렬하기위한 함수

int main()
{

	using namespace std;
	vector<double> departure_table;
	int queue = 0;
	

	int n;//n은 현재 있는 customer 수인듯
	//arrival time , Service time
	double Ta = 20, Ts = 100, simulation_time = 200000.0, next_arrival_time, next_departure_time;
	double elapsed_time;
	double B, C, L, s, tb, tn, U, W, X;
	departure_table.push_back(simulation_time);//dummy값

	double sumQ = 0.0, tQ = 0.0, q_len = 0.0;
	//큐에 있는 즉 줄을 서기위한 사람들의 수를 세기위한 변수
	//sumQ 에는 큐의 사람수 * 그 줄의 사람들이 있었던 시간 들이 계속해서 더해진다
	//tQ는 그 줄의 사람들이 있었던 시간을 체크하기위한 변수이다.
	//기존의 코드에서 B 를 계산하는 방식과 같은 방식이지만
	//B를 계산하는 방식은 시스템 내에 있고 없고 두가지 경우밖에 없지만
	//큐의 경우는 1명 있을떄 2명 있을때 등으로 여러개라서 살짝 알고리즘이 달라진다.

	/************************
	s : 가게 안에 있는 고객 수 * 그때 머문 시간
	L : 시간당 가게 안에 있는 평균 고객 수 =  s / elapsed_time

	C : 서비스한 고객 수
	X : 단위시간당 처리율 = C / elapsed_time

	W : 고객당 평균 머문 시간		=  L/X

	B : 일한 시간
	U : 효율  = 일한 시간 / 전체 시간
	*************************/

	n = 0; next_arrival_time = 0.0;
	next_departure_time = simulation_time; elapsed_time = 0.0;
	//일단 출발시간을 최대로 해놓고 나머지는 0으로 초기화

	B = s = 0.0; C = 0; tn = elapsed_time;
	
	
	/* Seed the random-number generator with current time so that the number will be dif ferent every time we run.*/
	srand((unsigned)time(NULL));

	while (elapsed_time < simulation_time)//경과된 시간이 시뮬레이션 시간보다 적을 때.
	{	// Time line
		//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
		//     ㅣ  next_arrival_time                 ㅣ next_departure_time
		if (next_arrival_time < next_departure_time)
		{ /* event 1 : customer arrival */
			elapsed_time = next_arrival_time;

			s += n*(elapsed_time - tn); //elapsed_time - tn 은 지난 시간이고 n 은 그동안 안에 있던 사람 수 임 . 즉 s는 사람들 있던 시간.
			n++;//n 증가시켜줌

			tn = elapsed_time;//지금으로 시점 옮겨주고

			next_arrival_time = elapsed_time + expntl(Ta);//다음 도착시간 계산

			if (n ==1) //n++  n이 0이였자늠.
			{//고객 한명일 때 즉 여태 쉬고 지금 들어온거임.
				tb = elapsed_time; 
				//tb에 경과시간 넣어준다.이제 지금부터 n이 0이 될때가 
				//일한 시간이 되겠지?
			}//B를 계산하기위해서 

			if (n <= MAX_TABLE)
			{
				departure_table.push_back(elapsed_time + expntl(Ts));
				//이번에 들어온 손님의 다 먹고 출발하는 시간을 계산해서 테이블에 넣는다.
				sort(departure_table.begin(), departure_table.end(), descending);
				//제일빠른게 맨앞에오도록
				next_departure_time = departure_table.back();
				//그 시간으로 설정해준다.
				
			}
			else
			{//큐가 생성되면 여태까지 계에 있었던 큐의 시간들을 계산먼저 함
				sumQ += (elapsed_time - tQ)*queue;
				queue++;// 그런뒤 큐 연산
				tQ = elapsed_time;// 다시 계산을 위한 변수 바꿔주기

			}

		}
		// Time line
		//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
		//    ㅣ next_departure_time                 ㅣ  next_arrival_time 
		else
		{ /* event 2 : customer departure */
			elapsed_time = next_departure_time; //시간 경과 시켜주고
			s += n*(elapsed_time - tn); //
			n--; //줄여주고
			tn = elapsed_time; //~~
			C++;//서비스 한 Customer 수 증가
			
			//사람이 테이블에서 젤 빠른거 뺴줌

			departure_table.pop_back();

			if (n >= MAX_TABLE)//이전에 맥스 테이블이상이였고 지금이 자리가 난거라면
			{//큐에서 빠지게 되면 여태까지 계에 있었던 큐의 시간들을 계산먼저 함
				sumQ += (elapsed_time - tQ)*queue;
				queue--;//큐 연산
				tQ = elapsed_time;// 다음 연산을 위한 tQ값 초기화
				

				departure_table.push_back(elapsed_time + expntl(Ts));
				//이번에 들어온 손님의 다 먹고 출발하는 시간을 계산해서 테이블에 넣는다.
				sort(departure_table.begin(), departure_table.end(), descending);
				//제일빠른게 맨앞에오도록
				next_departure_time = departure_table.back();
			}
			else if (n > 0) //맥스로 꽉찬것이 아닐 때임. 큐에 들어가지않음
			{//근데 만약 남은 큐하나가 들어온거라면 계산이 살짝 ㄷ라ㅏ라짐
				next_departure_time = departure_table.back();
			}
			else if(n==0){//n 은 0이 될때 임
				next_departure_time = simulation_time;
				B += elapsed_time - tb;
			}//B는 서버가 일한 시간
		}

	}
	sumQ += (elapsed_time - tQ)*queue;
	B += elapsed_time - tb;//마지막으로 계산을 한번더 해줌
	//이 계산을 제외하게 되면 마지막으로 쉬었던 시간 tb ~ 시뮬레이션ㅇ이 끝난 시간이
	//일한시간으로 안쳐지게 되기 때문에 효율이 더 낮게 나온다.
	//위의 Q 또한 마찬가지.
	 cout << "총 손님수 = " << C << endl;;
	X = C / elapsed_time; cout << "단위 시간당 서비스율 = " << X<<endl;;
	U = B / elapsed_time; cout<< "로봇의 효율  = "<< U << endl;
	L = s / elapsed_time; cout << "단위 시간당 손님의 수 = " << L << endl;
	W = L / X; cout<<"고객 당 머문 시간 = " << W << endl;
	q_len = sumQ / elapsed_time; cout << "단위 시간당 줄선 손님의 수  = " << q_len << endl;
	

}



double expntl(double x)
{ /* 'expntl' returns a psuedo -random variate from a negative exponen tial distribution with mean x */
	return(-x*log(norm_rand()));
}


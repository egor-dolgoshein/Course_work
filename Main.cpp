#include<vector>
#include<fstream>
#include<iostream>
#include "breadth-first search.h"
#include<random>
#include<cstdlib>

using namespace std;







void cutter(vector<vector<bool>> &cieve, int N)
{/*
	srand(time(NULL));
	// произвольная вершина
	int v = rand() % N*N + 0;
	int direction = rand() % 4 + 1;
	*/
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dist(0, N * N - 1);
	int v = dist(gen);

	uniform_int_distribution<> dist2(1, 4);
	int direction = dist2(gen);

	vector<bool> possible_directions{ 1,1,1,1 };

	while (true) {



		try {
			if (direction == 1) {
				if (v == 0 ||  v % N == 0)
				{
					possible_directions[0] = 0;
					throw out_of_range{ "Vector::operator[]" };
				}
				// перерезаем влево если есть что
				if (cieve[v - 1][v] == false)
				{
					possible_directions[0] = 0;
					throw false;
				}
				cieve[v - 1][v] = false;
				cieve[v][v - 1] = false;
				//cout << v << ' ' << v - 1 << endl;
			}
			else if (direction == 2 ) {
				if (v > N * N - N - 1)
				{
					possible_directions[1] = 0;
					throw out_of_range{ "Vector::operator[]" };
				}
				// перерезаем вниз если есть что
				if (cieve[v + N][v] == false || v % N == 0 || (v + 1) % N == 0 || v == 0)
				{
					possible_directions[1] = 0;
					throw false;
				}
				cieve[v + N][v] = false;
				cieve[v][v + N] = false;
				//cout << v << ' ' << v + N << endl;
			}
			else if (direction == 3) {
				if ((v + 1) % N == 0)
				{
					possible_directions[2] = 0;
					throw out_of_range{ "Vector::operator[]" };
				}
				// перерезаем вправо если есть что
				if (cieve[v + 1][v] == false)
				{
					possible_directions[2] = 0;
					throw false;
				}
				cieve[v + 1][v] = false;
				cieve[v][v + 1] = false;
				//cout << v << ' ' << v + 1 << endl;
			}
			else{
				if (v < N) 
				{
					possible_directions[3] = 0;
					throw out_of_range{ "Vector::operator[]" };
				}
				// перерезаем вверх если есть что
				if (cieve[v - N][v] == false || v % N == 0 || (v + 1) % N == 0)
				{
					possible_directions[3] = 0;
					throw false;
				}
				cieve[v - N][v] = false;
				cieve[v][v - N] = false;
				//cout << v << ' ' << v - N << endl;
			}
			break;
			}
		catch (out_of_range &e) {
			srand(time(NULL));
			direction = rand() % 4 + 1;
			continue;
		}
		catch (bool excep)
		{
			if (!possible_directions[0] && !possible_directions[1] && !possible_directions[2] && !possible_directions[3])
			{
				//srand(time(NULL));
				//v = rand() % N * N + 0;
				random_device rd;
				mt19937 gen(rd());
				uniform_int_distribution<> dist(0, N * N - 1);
				v = dist(gen);
				possible_directions = { 1,1,1,1 };
			}
			srand(time(NULL));
			direction = rand() % 4 + 1;
			continue;
		}
	}
}







// проверка, что путь еще актуален
bool correct_path(vector<vector<bool>>& cieve, vector<int>& track)
{
	for (int i = 0; i < track.size() - 1; ++i)
	{
		if (!cieve[track[i]][track[i + 1]])
			return false;
	}
	return true;
}


// проверка горизонтальных путей (не факт что в этом есть смысл, тк вначале они будут => время экономится,
// потом они вогут "нарушиться" и будут идти лишние проверки)
bool horizontal_path_check(vector<vector<bool>>& cieve)
{

	for (int i = 0; i < cieve.size() - 1; ++i)
	{
		for (int j = 0; j < cieve.size() - 1; ++j)
		{
			if (!(cieve[i][j] && cieve[i][j + 1]))
				break;
			if (j == cieve.size() - 1) // подходит какой-то из горизонтальных путей
				return true;
		}
	}
	return false;
}


void checker()
{
	ifstream in;
	in.open("C:\\Users\\Егор\\source\\repos\\Study practice\\Study practice\\output.txt");
	double num;
	vector<double> buff;
	while (in >> num)
		buff.push_back(num);
	double sum = 0;
	for (double n : buff)
		sum += n;
	cout << "\nAverage result is " << sum / buff.size() << endl;
	in.close();
}




int main() {
	// матрица 100х100 из нулей
	
	// единицы на i,j; i,j+1; i+1,j месте
	// можно для простоты привести матрицу к нижнетреугольной
	int N = 10;
	ofstream of;
	of.open("C:\\Users\\Егор\\source\\repos\\Study practice\\Study practice\\output.txt");
	for (int i = 0; i < 2; ++i) {

		vector cieve(N*N, vector<bool>(N*N, false));
		for (size_t i = 0; i < cieve.size() - 1; ++i)
		{
			if ((i + 1) % N != 0)
			{
				if (i < cieve.size() - N - 1)
				{
					cieve[i][i] = true;
					cieve[i][i + 1] = true;
					cieve[i + 1][i] = true;
					cieve[i + N][i] = true;
					cieve[i][i + N] = true;
				}
				else
				{
					cieve[i][i] = true;
					cieve[i][i + 1] = true;
					cieve[i + 1][i] = true;
				}
			}
			else if(i != N * N - 1)
			{
				cieve[i][i] = true;
				cieve[i + N][i] = true;
				cieve[i][i + N] = true;
			}
			
		}
		vector<int> track;
		for (int i = 0; i < N; ++i)
			track.push_back(i);

		int count_cut = 0;
		while (true)
		{
			int start = 0;
			int finish = N - 1;
			if (!correct_path(cieve, track))
				track = Breadth_first_search(cieve, start, finish);
			if (track.empty())
				break;

			cutter(cieve, N);

			count_cut++;

		}
	
		//cout << "\n" << count_cut / (double)(2 * N * (N - 1));
	//cout << "\n\n";
	of << count_cut/ (double)(2 * N * (N - 1)) << '\n';
	}
	of.close();
	checker();
	return 1;
}

#include<vector>
#include<fstream>
#include<iostream>
#include "breadth-first search.h"


using namespace std;







void cutter(vector<vector<bool>> &cieve)
{
	srand(time(NULL));
	// произвольная вершина
	int v = rand() % 10000 + 0;
	int direction = rand() % 4 + 1;

	vector<bool> possible_directions{ 1,1,1,1 };

	while (true) {



		try {
			if (direction == 1) {
				if (v - 1 < 0 ||  v % 100 == 0)
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
			}
			else if (direction == 2 ) {
				if (v > 9899 )
				{
					possible_directions[1] = 0;
					throw out_of_range{ "Vector::operator[]" };
				}
				// перерезаем вниз если есть что
				if (cieve[v + 100][v] == false|| v % 100 == 0 || (v + 1) % 100 == 0)
				{
					possible_directions[1] = 0;
					throw false;
				}
				cieve[v + 100][v] = false;
				cieve[v][v + 100] = false;
			}
			else if (direction == 3) {
				if ((v + 1) % 100 == 0)
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
			}
			else{
				if (v < 100) 
				{
					possible_directions[3] = 0;
					throw out_of_range{ "Vector::operator[]" };
				}
				// перерезаем вверх если есть что
				if (cieve[v - 100][v] == false || v % 100 == 0 || (v + 1) % 100 == 0)
				{
					possible_directions[3] = 0;
					throw false;
				}
				cieve[v - 100][v] = false;
				cieve[v][v - 100] = false;
			}
			break;
			}
		catch (out_of_range &e) {
			direction = rand() % 4 + 1;
			continue;
		}
		catch (bool excep)
		{
			if (!possible_directions[0] && !possible_directions[1] && !possible_directions[2] && !possible_directions[3])
			{
				v = rand() % 10000 + 0;
				possible_directions = { 1,1,1,1 };
			}
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





int main() {
	// матрица 100х100 из нулей
	/*
	// единицы на i,j; i,j+1; i+1,j месте
	// можно для простоты привести матрицу к нижнетреугольной
	vector<vector<bool>> cieve =
	{
		{1,1,0,1,0,0,0,0,0},
		{1,1,1,0,1,0,0,0,0},
		{0,1,1,0,0,1,0,0,0},
		{1,0,0,1,1,0,1,0,0}, 
		{0,1,0,1,1,1,0,1,0}, 
		{0,0,1,0,1,1,0,0,1}, 
		{0,0,0,1,0,0,1,1,0}, 
		{0,0,0,0,1,0,1,1,1}, 
		{0,0,0,0,0,1,0,1,1}, };

		*/
	
	ofstream of;
	of.open("C:\\Users\\Егор\\source\\repos\\Study practice\\Study practice\\output.txt");
	for (int i = 0; i < 3; ++i) {

		vector cieve(10000, vector<bool>(10000, false));
		for (size_t i = 0; i < cieve.size() - 100; ++i)
		{
			if ((i + 1) % 100 != 0)
			{
				cieve[i][i] = true;
				cieve[i][i + 1] = true;
				cieve[i + 1][i] = true;
				cieve[i + 100][i] = true;
				cieve[i][i + 100] = true;
			}
			else
			{
				cieve[i][i] = true;
				cieve[i + 100][i] = true;
				cieve[i][i + 100] = true;
			}
		}
		vector<int> track;
		for (int i = 0; i < 100; ++i)
			track.push_back(i);

		int count_cut = 0;
		while (true)
		{
			int start = 0;
			int finish = 99;
			if (/*!horizontal_path_check(cieve) && */!correct_path(cieve, track))
				track = Breadth_first_search(cieve, start, finish);
			if (track.empty())
				break;

			cutter(cieve);

			count_cut++;

		}
		/*for (auto x : cieve)
		{
			for (auto y : x)
				cout << y;
			cout << "\n";
		}*/
	cout << "\n" << count_cut/19800.;
	cout << "\n\n";
	of << count_cut/19800. << '\n';
	}
	of.close();

}

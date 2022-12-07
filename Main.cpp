#include<vector>
#include<fstream>
#include<iostream>
#include<cstdlib>
#include "breadth-first search.h"
//#include "Square_grid.h"
#include "Triangle_grid.h"

using namespace std;






// проверка, что путь еще актуален
bool correct_path(vector<vector<int>>& grid, vector<int>& track)
{
	for (int i = 0; i < track.size() - 1; ++i)
	{
		//!cieve[track[i]][track[i + 1]]
		if (find(grid[track[i]].begin(), grid[track[i]].end(), track[i+1]) == grid[track[i]].end())
			return false;
	}
	return true;
}




void checker()
{
	ifstream in;
	in.open("D:\\EGOR\\study\\source\\repos\\Study practice\\Study practice\\output.txt");
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
	int N = 20;
	ofstream of;
	of.open("D:\\EGOR\\study\\source\\repos\\Study practice\\Study practice\\output.txt");
	for (int i = 0; i < 3; ++i) {
		
		auto filled_case = fill_grid(N);

		auto grid = filled_case.first;
		double vertex_number = filled_case.second;

		vector<int> track;
		for (int i = 0; i < N; ++i)
			track.push_back(i);

		int count_cut = 0;
		while (true)
		{
			int start = 0;
			int finish = N - 1;
			if (!correct_path(grid, track))
				track = Breadth_first_search(grid, start, finish);
			if (track.empty())
				break;

			cutter(grid, N);

			count_cut++;

		}
	
		//cout << "\n" << count_cut / (double)(2 * N * (N - 1));
	//cout << "\n\n";
	//of << count_cut / vertex_number << '\n';
	cout << count_cut / vertex_number << '\n';
	}
	of.close();
	checker();
	return 1;
}

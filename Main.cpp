#include<vector>
#include<fstream>
#include<iostream>
#include<cstdlib>
#include "breadth-first search.h"
//#include "Square_grid.h"
//#include "Triangle_grid.h"
#include"Cube_grid.h"

using namespace std;






// проверка, что путь еще актуален
bool correct_path(vector<vector<int>>& grid, vector<int>& track)
{
	for (int i = 0; i < track.size() - 1; ++i)
	{
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
	int N = 10;
	ofstream of;
	//of.open("D:\\EGOR\\study\\source\\repos\\Study practice\\Study practice\\output.txt");
	for (int i = 0; i < 1; ++i) {
		
		//auto filled_case = fill_grid(N);

		//auto grid = filled_case.first;

		//double vertex_number = filled_case.second;
		auto grid = fill_grid();

		vector<int> track;
		for (int i = 0; i < N; ++i)
			track.push_back(i);

		int count_cut = 0;
		while (true)
		{
			int start = 0;
			int finish = N * N - 1;
			if (!correct_path(grid, track))
				track = Breadth_first_search(grid, start, finish);
			if (track.empty())
				break;

			cutter(grid, N);

			count_cut++;

		}
	//of << count_cut / vertex_number << '\n';
	cout << count_cut / vertex_number << '\n';
	}
	of.close();
	//checker();
}

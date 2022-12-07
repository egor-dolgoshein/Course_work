#pragma once
#include<vector>
#include<random>


// filling square grid as Adjacency list
std::pair<std::vector<std::vector<int>>, double> fill_grid(int N)
{
	std::vector grid(N * N, std::vector<int>(0));

	for (size_t i = 0; i < grid.size() - 1; ++i)
	{
		if ((i + 1) % N != 0)
		{
			if (i < grid.size() - N - 1)
			{
				grid[i].push_back(i + 1);
				grid[i + 1].push_back(i);
				grid[i].push_back(i + N);
				grid[i + N].push_back(i);
				/*grid[i][i] = true;
				grid[i][i + 1] = true;
				grid[i + 1][i] = true;
				grid[i + N][i] = true;
				grid[i][i + N] = true;*/
			}
			else
			{
				grid[i].push_back(i + 1);
				grid[i + 1].push_back(i);
				/*grid[i][i] = true;
				grid[i][i + 1] = true;
				grid[i + 1][i] = true;*/
			}
		}
		else //if (i != N * N - 1)
		{
			grid[i].push_back(i + N);
			grid[i + N].push_back(i);
			/*grid[i][i] = true;
			grid[i + N][i] = true;
			grid[i][i + N] = true;*/
		}
	}
	return { grid, (double)(2 * N * (N - 1)) };
}



// square grid case cutter

void cutter(std::vector<std::vector<int>>& grid, int N)
{/*
	srand(time(NULL));
	// произвольная вершина
	int v = rand() % N*N + 0;
	int direction = rand() % 4 + 1;
	*/
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(0, N * N - 1);
	int v = dist(gen);

	std::uniform_int_distribution<> dist2(1, 4);
	int direction = dist2(gen);

	std::vector<bool> possible_directions{ 1,1,1,1 };

	while (true) {



		try {
			if (direction == 1) {
				if (v == 0 || v % N == 0)
				{
					possible_directions[0] = 0;
					throw std::out_of_range{ "Vector::operator[]" };
				}
				// перерезаем влево если есть что
				//grid[v - 1][v] == false
				auto it = find(grid[v].begin(), grid[v].end(), v - 1);
				if (it == grid[v].end()) //(v - 1) in grid[v]
				{
					possible_directions[0] = 0;
					throw false;
				}
				grid[v - 1].erase(find(grid[v - 1].begin(), grid[v - 1].end(), v)); // delete v from grid[v-1]
				grid[v].erase(it);
				/*grid[v - 1][v] = false;
				grid[v][v - 1] = false;*/
				//cout << v << ' ' << v - 1 << endl;
			}
			else if (direction == 2) {
				if (v > N * N - N - 1)
				{
					possible_directions[1] = 0;
					throw std::out_of_range{ "Vector::operator[]" };
				}
				// перерезаем вниз если есть что
				//grid[v + N][v] == false
				auto it = find(grid[v].begin(), grid[v].end(), v + N);
				if (it == grid[v].end() || v % N == 0 || (v + 1) % N == 0 || v == 0)
				{
					possible_directions[1] = 0;
					throw false;
				}
				grid[v + N].erase(find(grid[v + N].begin(), grid[v + N].end(), v)); // delete v from grid[v+N]
				grid[v].erase(it);
				/*grid[v + N][v] = false;
				grid[v][v + N] = false;*/
				//cout << v << ' ' << v + N << endl;
			}
			else if (direction == 3) {
				if ((v + 1) % N == 0)
				{
					possible_directions[2] = 0;
					throw std::out_of_range{ "Vector::operator[]" };
				}
				// перерезаем вправо если есть что
				//grid[v + 1][v] == false
				auto it = find(grid[v].begin(), grid[v].end(), v + 1);
				if (it == grid[v].end())
				{
					possible_directions[2] = 0;
					throw false;
				}
				grid[v + 1].erase(find(grid[v + 1].begin(), grid[v + 1].end(), v)); // delete v from grid[v+1]
				grid[v].erase(it);
				/*grid[v + 1][v] = false;
				grid[v][v + 1] = false;*/
				//cout << v << ' ' << v + 1 << endl;
			}
			else {
				if (v < N)
				{
					possible_directions[3] = 0;
					throw std::out_of_range{ "Vector::operator[]" };
				}
				// перерезаем вверх если есть что
				//cieve[v - N][v] == false
				auto it = find(grid[v].begin(), grid[v].end(), v - N);
				if (it == grid[v].end() || v % N == 0 || (v + 1) % N == 0)
				{
					possible_directions[3] = 0;
					throw false;
				}
				grid[v - N].erase(find(grid[v - N].begin(), grid[v - N].end(), v)); // delete v from grid[v-N]
				grid[v].erase(it);
				/*grid[v - N][v] = false;
				grid[v][v - N] = false;*/
				//cout << v << ' ' << v - N << endl;
			}
			break;
		}
		catch (std::out_of_range& e) {
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
				std::random_device rd;
				std::mt19937 gen(rd());
				std::uniform_int_distribution<> dist(0, N * N - 1);
				v = dist(gen);
				possible_directions = { 1,1,1,1 };
			}
			srand(time(NULL));
			direction = rand() % 4 + 1;
			continue;
		}
	}
}

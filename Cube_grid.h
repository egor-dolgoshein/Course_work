#pragma once
#include<vector>
#include<random>



double vertex_number;

bool from_back(size_t i, int N = 10)
{
	for (size_t j = 0; j < N; ++j)
		if (i > (N * N - N) + N * N * j &&
			i <= N * N * (j + 1))
			return true;
	return false;
}




// filling the neighbour lists of the square grid

std::vector<std::vector<int>> fill_grid(int N = 10)
{
	vertex_number = (double)(2 * N * (N - 1)) * N + (N - 1) * N * N;
	std::vector grid(N * N * N, std::vector<int>(0));
	for (size_t i = 0; i < grid.size() - 1; ++i)
	{
			if (!from_back(i + 1)) // avoid back of the cube
			{
				// filling right, forward, up
				if ((i + 1) % N != 0 && (i + 1) <= N * N * N - N * N)
				{
					grid[i].push_back(i + 1);
					grid[i].push_back(i + N * N);
					grid[i].push_back(i + N);
					grid[i + 1].push_back(i);
					grid[i + N * N].push_back(i);
					grid[i + N].push_back(i);
					continue;
				}
				// filling forward, up
				if ((i + 1) % N == 0 && (i + 1) <= N * N * N - N * N)
				{
					grid[i].push_back(i + N * N);
					grid[i].push_back(i + N);
					grid[i + N * N].push_back(i);
					grid[i + N].push_back(i);
					continue;
				}
				// filling right, forward
				if ((i + 1) > N * N * N - N * N && (i + 1) % N != 0)
				{
					grid[i].push_back(i + 1);
					grid[i].push_back(i + N);
					grid[i + 1].push_back(i);
					grid[i + N].push_back(i);
					continue;
				}
				//filling forward
				if ((i + 1) % N == 0 || (i + 1) > N * N * N - N * N)
				{
					grid[i].push_back(i + N);
					grid[i + N].push_back(i);
					continue;
				}
			}
			else
			{
				if ((i + 1) <= N * N * N - N)
				{
					// filling right, up
					if ((i + 1) % N != 0)
					{
						grid[i].push_back(i + 1);
						grid[i].push_back(i + N * N);
						grid[i + 1].push_back(i);
						grid[i + N * N].push_back(i);
						continue;
					}
					// filling up
					else
					{
						grid[i].push_back(i + N * N);
						grid[i + N * N].push_back(i);
						continue;
					}
				}
				// filling right
				else
				{
					grid[i].push_back(i + 1);
					grid[i + 1].push_back(i);
					continue;
				}
			}
	}
	return grid;
}


void cutter(std::vector<std::vector<int>>& grid, int N)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(0, grid.size() - 1);
	int v = dist(gen);

	std::uniform_int_distribution<> dist2(1, 6);
	int direction = dist2(gen);

	std::vector<bool> possible_directions{ 1,1,1,1,1,1 };

	while (true)
	{
		try
		{
			// forward
			if (direction == 1)
			{
				// avoid back of the cube
				if (!from_back(v + 1))
				{
					possible_directions[0] = 0;
					throw std::out_of_range{ "Vector::operator[]" };
				}
				// cutting forward, unless it is nothing to cut
				auto it = find(grid[v].begin(), grid[v].end(), v + N);
				if (it == grid[v].end())
				{
					possible_directions[0] = 0;
					throw false;
				}
				grid[v + N].erase(find(grid[v + N].begin(), grid[v + N].end(), v)); // delete v from grid[v+N]
				grid[v].erase(it);
			}
			// backwards
			else if (direction == 2) {
				// avoid front of the cube
				for(size_t i = 0; i < N; ++i)
					if (v + 1 > N * N * i + 1 && v + 1 <= N + (N * N * i))
					{
						possible_directions[1] = 0;
						throw std::out_of_range{ "Vector::operator[]" };
					}
				// cutting backwards, unless it is nothing to cut
				auto it = find(grid[v].begin(), grid[v].end(), v - N);
				if (it == grid[v].end())
				{
					possible_directions[1] = 0;
					throw false;
				}
				grid[v - N].erase(find(grid[v - N].begin(), grid[v - N].end(), v)); // delete v from grid[v-N]
				grid[v].erase(it);
			}
			// right
			else if (direction == 3) {
				// avoid right side of the cube
				if ((v + 1) % N == 0)
				{
					possible_directions[2] = 0;
					throw std::out_of_range{ "Vector::operator[]" };
				}
				// cutting right, unless it is nothing to cut
				auto it = find(grid[v].begin(), grid[v].end(), v + 1);
				for(size_t i = 0; i < N; ++i)
					if (it == grid[v].end() || 
						(v + 1 > N * N * i + 1 && v + 1 <= N + (N * N * i)) || 
						!from_back(v + 1))
					{
						possible_directions[2] = 0;
						throw false;
					}
				grid[v + 1].erase(find(grid[v + 1].begin(), grid[v + 1].end(), v)); // delete v from grid[v+1]
				grid[v].erase(it);
			}
			// left
			else if (direction == 4) {
				// avoid left side of the cube
				for (size_t i = 0; i < N; ++i)
					if (v % N == 0)
					{
						possible_directions[3] = 0;
						throw std::out_of_range{ "Vector::operator[]" };
					}
				// cutting left, unless it is nothing to cut
				auto it = find(grid[v].begin(), grid[v].end(), v - 1);
				for(size_t i = 0; i < N; ++i)
					if (it == grid[v].end() ||
						(v + 1 > N * N * i + 1 && v + 1 <= N + (N * N * i)) ||
						!from_back(v + 1))
					{
					possible_directions[3] = 0;
					throw false;
					}
				grid[v - 1].erase(find(grid[v - 1].begin(), grid[v - 1].end(), v)); // delete v from grid[v-1]
				grid[v].erase(it);
			}
			// up
			else if (direction == 5) {
				// avoid top of the cube
				for (size_t i = 0; i < N; ++i)
					if (v >= N * N * N - N * N)
					{
						possible_directions[4] = 0;
						throw std::out_of_range{ "Vector::operator[]" };
					}
				// cutting up, unless it is nothing to cut
				auto it = find(grid[v].begin(), grid[v].end(), v + N * N);
				for (size_t i = 0; i < N; ++i)
					if (it == grid[v].end() ||
						(v + 1 > N * N * i + 1 && v + 1 <= N + (N * N * i)) ||
						!from_back(v + 1))
					{
						possible_directions[4] = 0;
						throw false;
					}
				grid[v + N * N].erase(find(grid[v + N * N].begin(), grid[v + N * N].end(), v)); // delete v from grid[v+N*N]
				grid[v].erase(it);
			}
			// down
			else {
				// avoid bottom side of the cube
				for (size_t i = 0; i < N; ++i)
					if (v < N * N)
					{
						possible_directions[5] = 0;
						throw std::out_of_range{ "Vector::operator[]" };
					}
				// cutting down, unless it is nothing to cut
				auto it = find(grid[v].begin(), grid[v].end(), v - N * N);
				for (size_t i = 0; i < N; ++i)
					if (it == grid[v].end() ||
						(v + 1 > N * N * i + 1 && v + 1 <= N + (N * N * i)) ||
						(v + 1 > (N * N - N) * i && v + 1 <= (N * N) * i))
					{
						possible_directions[5] = 0;
						throw false;
					}
				grid[v - N * N].erase(find(grid[v - N * N].begin(), grid[v - N * N].end(), v)); // delete v from grid[v-N*N]
				grid[v].erase(it);
			}
			break;
		}
		catch (std::out_of_range& e) {
			srand(time(NULL));
			direction = rand() % 6 + 1;
			continue;
		}
		catch (bool excep)
		{
			if (!possible_directions[0] && !possible_directions[1] && !possible_directions[2] && !possible_directions[3])
			{
				std::random_device rd;
				std::mt19937 gen(rd());
				std::uniform_int_distribution<> dist(0, N * N * N - 1);
				v = dist(gen);
				possible_directions = { 1,1,1,1,1,1 };
			}
			srand(time(NULL));
			direction = rand() % 6 + 1;
			continue;
		}
	}
}
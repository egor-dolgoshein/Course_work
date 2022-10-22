#include<iostream>
#include<vector>
#include<queue>
#include<cassert>

using namespace std;

/*
vector<int> Breadth_first_search(vector<vector<bool>> &matrix, int start, int finish)
{
	queue<int> q;
	q.push(start);
	vector<bool> disclosed(matrix.size() * matrix[0].size());
	disclosed[start] = true;
	//vector<int> distance(matrix.size()* matrix[0].size());
	vector<int> path(matrix.size() * matrix[0].size());
	path[start] = -1;
	while (!q.empty())
	{
		int vertex = q.front();
		q.pop();
		for (int i = 0; i < matrix[vertex].size(); ++i)
		{
			//int to = matrix[vertex][i];
			if (!disclosed[i]  && matrix[vertex][i])
			{
				disclosed[i] = true;
				q.push(i);
				//distance[i] += distance[vertex] + 1;
				path[i] = vertex;
			}
		}
	}
	vector<int> track;
	if (!disclosed[finish])
		assert(0 && "Unattainable vertex");
	else
	{
		for (int v = finish; v != -1; v = path[v])
			track.push_back(v);
		reverse(track.begin(), track.end());
	}
	return track;
}


int main()
{
	vector<vector<bool>> test = { 
		{1,0,0,1,0,0,0,0,0},
		{0,1,0,0,0,0,0,0,0},
		{0,0,1,0,0,1,0,0,0},
		{1,0,0,1,0,0,1,0,0},
		{0,0,0,0,1,0,0,0,0},
		{0,0,1,0,0,1,0,0,1},
		{0,0,0,1,0,0,1,1,0},
		{0,0,0,0,0,0,1,1,0},
		{0,0,0,0,0,1,0,0,1}
	};
	vector<int> res = Breadth_first_search(test, 0, 2);
	for (auto x : res)
		cout << x << '\t';
}*/
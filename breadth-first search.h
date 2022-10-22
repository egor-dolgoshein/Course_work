#pragma once
#include<vector>
#include<queue>

std::vector<int> Breadth_first_search(std::vector<std::vector<bool>>& matrix, int start, int finish)
{
	std::queue<int> q;
	q.push(start);
	std::vector<bool> disclosed(matrix.size() * matrix[0].size());
	disclosed[start] = true;
	//vector<int> distance(matrix.size()* matrix[0].size());
	std::vector<int> path(matrix.size() * matrix[0].size());
	path[start] = -1;
	while (!q.empty())
	{
		int vertex = q.front();
		q.pop();
		for (int i = 0; i < matrix[vertex].size(); ++i)
		{
			//int to = matrix[vertex][i];
			if (!disclosed[i] && matrix[vertex][i])
			{
				disclosed[i] = true;
				q.push(i);
				//distance[i] += distance[vertex] + 1;
				path[i] = vertex;
			}
		}
	}
	std::vector<int> track;
	if (!disclosed[finish])
		return track;
	else
	{
		for (int v = finish; v != -1; v = path[v])
			track.push_back(v);
		reverse(track.begin(), track.end());
	}
	return track;
}
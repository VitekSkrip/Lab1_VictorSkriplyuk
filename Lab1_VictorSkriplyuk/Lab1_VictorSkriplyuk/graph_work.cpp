#include<iostream>
#include<fstream>
#include <string>
#include <vector>
#include "Pipe.h"
#include "CS.h"
#include "utils.h"
#include "unordered_map"
#include "map"
#include <algorithm>
#include "graph_work.h"
using namespace std;


p_id_in AddConnection(int& pipe_id, int& cs_id_in)
{
	p_id_in pair;
	pair.pipe_id = pipe_id;
	pair.cs_id_in = cs_id_in;
	return pair;
}

void cs_delete_fromGraph(unordered_map<int, vector<p_id_in>>& graph, unordered_map<int, CS>& cs_group, int& cs_id)
{
	if (graph.find(cs_id) != graph.end())
	{
		graph.erase(cs_id);
	}
	for (auto iter = graph.begin(); iter != graph.end(); iter++)
	{
		for (auto i = 0; i < iter->second.size(); i++)
		{
			if (iter->second[i].cs_id_in == cs_id)
				iter->second.erase(iter->second.begin() + i);

		}
	}
}


void Print_Graph(unordered_map<int, vector<p_id_in>> graph)
{
	for (auto& i : graph)
	{
		cout << "КС id=" << i.first << " соединена трубой id=";
		for (auto j = i.second.begin(); j != i.second.end(); j++)
		{
			cout << j->pipe_id << " с КС id=" << j->cs_id_in;
			if (j + 1 != i.second.end())
				cout << ", ";
		}
		cout << endl;
	}
}


bool dfs(int cs_id, int& cycle_status, unordered_map<int, vector<p_id_in>> graph, unordered_map<int, char> color, unordered_map<int, int>& used_cs, vector <int>& ans)
{
	// сolor: 0 - не посетили; 1 - посетили; 2 - вышли из вершины
	color[cs_id] = 1;
	for (size_t i = 0; i < graph[cs_id].size(); ++i)
	{
		int to = graph[cs_id][i].cs_id_in;
		if (color[to] == 0)
		{
			if (dfs(to, cycle_status, graph, color, used_cs, ans))
				return true;
		}
		else if (color[to] == 1)
		{
			cycle_status = to;
			return true;
		}
	}

	color[cs_id] = 2;
	used_cs[cs_id] = true;
	vector<p_id_in> arr;
	if (graph.find(cs_id) != graph.end())
	{
		int count = 0;
		int count_v = ans.size();
		for (int j = 0; j < count_v; j++)
			if (ans[j] == cs_id)
				count = count + 1;
		if (count == 0) ans.push_back(cs_id);
	}
	return false;
}


void topological_sort(unordered_map<int, vector<p_id_in>>& graph, vector<int>& ans)
{
	ans.clear();
	unordered_map<int, char> color;
	unordered_map<int, int> used_cs;
	for (auto& i : graph)
	{
		color[i.first] = false;
		used_cs[i.first] = -1;
	}
	int cycle_status = -1;
	for (auto& el : color)
	{
		if (dfs(el.first, cycle_status, graph, color, used_cs, ans))
			break;
	}
	if (cycle_status == -1)
		reverse(ans.begin(), ans.end());
	else cout << "В графе присутствует цикл!" << endl;
}

unordered_map<int, bool> count_vertex(unordered_map<int, vector<p_id_in>>& graph)
{
	unordered_map<int, bool> count;
	for (auto& iter : graph)
	{
		count[iter.first] = false;
		for (auto& v : iter.second)
		{
			count[v.cs_id_in] = false;
		}
	}
	return count;
}

void find_shortest_path(unordered_map<int, vector<p_id_in>>& graph, unordered_map<int, Pipe>& pipe_group)
{
	cout << "Введите id КС - начало пути: ";
	int id_from = checking(1u, CS::GetMaxID(), "Введите id КС - начало пути: ");
	cout << "Введите id КС - конец пути: ";
	int id_to = checking(1u, CS::GetMaxID(), "Введите id КС - конец пути: ");
	if (graph.find(id_from) != graph.end())
	{
		unordered_map <int, int> distance;
		unordered_map <int, bool> passed;
		unordered_map<int, bool> count = count_vertex(graph);
		unordered_map<int, int>p;

		for (auto i = graph.begin(); i != graph.end(); i++)
		{
			int i1 = i->first;
			distance[i1] = INT_MAX;
			passed[i1] = false;
			for (auto j : i->second)
			{
				distance[j.cs_id_in] = INT_MAX;
				passed[j.cs_id_in] = false;
			}
		}
		distance[id_from] = 0;
		int index = 0;
		for (auto j = count.begin(); j != count.end(); j++)
		{
			int min = INT_MAX;
			for (auto i = count.begin(); i != count.end(); i++)
			{
				int i1 = i->first;
				if (!passed[i1] && distance[i1] <= min)
				{
					min = distance[i1];
					index = i1;
				}
			}
			passed[index] = true;
			for (auto i = graph[index].begin(); i != graph[index].end(); i++)
			{
				int i1 = i->cs_id_in;
				if (!passed[i1] && !pipe_group[i->pipe_id].GetRepair() &&  distance[index] != INT_MAX && distance[index] + pipe_group[i1].GetWeight() < distance[i1])
				{
					distance[i1] = distance[index] + pipe_group[i1].GetWeight();
					p[i1] = index;
				}
				if (pipe_group[i->pipe_id].GetRepair())
				{
					distance[i1] = INT_MAX;
				}
			}
		}
		cout << "Наикратчайший путь:" << endl;
		if (distance[id_to] != INT_MAX)
		{
			cout << id_from << " -> " << id_to << " = " << distance[id_to] << endl;
			vector <int> path;
			for (int vertex = id_to; vertex != id_from; vertex = p[vertex])
				path.push_back(vertex);
			path.push_back(id_from);
			reverse(path.begin(), path.end());
			cout << "Путь: ";
			for (auto i = path.begin(); i != path.end(); i++)
			{
				if (i + 1 != path.end()) cout << *i << " -> ";
				else cout << *i;
			}
		}
		else cout << id_from << " -> " << id_to << " - пути нет";
	}
	else cout << "Невозможно!" << endl;
}

void addEdge(int u, int v, int cap, int onEnd[100], int& edgeCount, int nextEdge[100], int firstEdge[100], int capacity[100])
{
	
	onEnd[edgeCount] = v; 
		nextEdge[edgeCount] = firstEdge[u]; 
		firstEdge[u] = edgeCount; 
		capacity[edgeCount++] = cap; 
	
		onEnd[edgeCount] = u; 
		nextEdge[edgeCount] = firstEdge[v]; 
		firstEdge[v] = edgeCount; 
		capacity[edgeCount++] = 0; 
}

int findFlow(int u, int flow, int destinationVertex, int* visited, int* firstEdge, int* nextEdge, int* onEnd, int* capacity) 
{
	if (u == destinationVertex) return flow; 
		visited[u] = true;
	for (int edge = firstEdge[u]; edge != 0; edge = nextEdge[edge]) 
	{
		int to = onEnd[edge];
		if (!visited[to] && capacity[edge] > 0) 
		{
			int minResult = findFlow(to, min(flow, capacity[edge]), destinationVertex, visited, firstEdge, nextEdge, onEnd, capacity);
				if (minResult > 0)
				{ 
					capacity[edge] -= minResult; 			   
					return minResult;
				}
		}
	}
	return 0;
}
void get_maxflow(unordered_map<int, vector<p_id_in>>& graph, unordered_map <int, CS>& cs_group, unordered_map <int, Pipe>& pipe_group, unordered_map<int, bool> count_cs)
{
	size_t n = pipe_group.size();
	int* capacity = new int[n];
	int* onEnd = new int[n];
	int* nextEdge = new int[n];
	int* firstEdge = new int[n];
	int* visited = new int[n];
	for (size_t i = 0; i < n; i++)
	{
		capacity[i] = 0;
		onEnd[i] = 0;
		nextEdge[i] = 0;
		firstEdge[i] = 0;
		visited[i] = 0;
	}
	int edgeCount = 1;

	//unordered_map<int, bool> count_cs = count_vertex(graph);
	int numOfVertex = count_cs.size();
	int sourceVertex, destinationVertex;
	cout << "Введите id КС - исток: ";
	sourceVertex = checking(1u, CS::GetMaxID(), "Введите id КС - исток: ");
	cout << "Введите id КС - сток: ";
	destinationVertex = checking(1u, CS::GetMaxID(), "Введите id КС - сток: ");
		if (destinationVertex == sourceVertex)
			cout << "This KS as start and finish";
		else if ((cs_group.find(sourceVertex) == cs_group.end()) || (cs_group.find(destinationVertex) == cs_group.end()))
			cout << "Have not this KSs or one of this KSs";
		else
		{
			for (auto it = pipe_group.begin(); it != pipe_group.end(); ++it) {
				int u, v, cap;
				if (it->second.GetId_CS_In() != 0 && it->second.GetRepair()==false)
				{
					u = it->second.GetId_CS_Out();
					v = it->second.GetId_CS_In();
					cap = it->second.GetCapacity();
					addEdge(u, v, cap, onEnd, edgeCount, nextEdge, firstEdge, capacity);
				}
			}
			int maxFlow = 0;
			int iterationResult = 0;
			while ((iterationResult = findFlow(sourceVertex, 1000000, destinationVertex, visited, firstEdge, nextEdge, onEnd, capacity)) > 0)
				maxFlow += iterationResult;
			cout << maxFlow << endl;
		}
}
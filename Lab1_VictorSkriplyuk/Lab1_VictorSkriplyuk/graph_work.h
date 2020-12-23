#pragma once
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

using namespace std;

struct p_id_in
{
	int cs_id_in;
	int pipe_id;
};

void Print_Graph(unordered_map<int, vector<p_id_in>> graph);

void cs_delete_fromGraph(unordered_map<int, vector<p_id_in>>& graph, unordered_map<int, CS>& cs_group, int& cs_id);

p_id_in AddConnection(int& pipe_id, int& cs_id_in);

bool dfs(int cs_id, int& cycle_status, unordered_map<int, vector<p_id_in>> graph, unordered_map<int, char> color, unordered_map<int, int>& used_cs, vector <int>& ans);

void topological_sort(unordered_map<int, vector<p_id_in>>& graph, vector<int>& ans);

unordered_map<int, bool> count_vertex(unordered_map<int, vector<p_id_in>>& graph);

void find_shortest_path(unordered_map<int, vector<p_id_in>>& graph, unordered_map<int, Pipe>& pipe_group);

void addEdge(int u, int v, int cap, int onEnd[100], int& edgeCount, int nextEdge[100], int firstEdge[100], int capacity[100]);

int findFlow(int u, int flow, int destinationVertex, int* visited, int* firstEdge, int* nextEdge, int* onEnd, int* capacity);

void get_maxflow(unordered_map<int, vector<p_id_in>>& graph, unordered_map <int, CS>& cs_group, unordered_map <int, Pipe>& pipe_group, unordered_map<int, bool> count_cs);
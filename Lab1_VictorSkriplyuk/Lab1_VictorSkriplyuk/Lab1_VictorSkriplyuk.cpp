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


void delete_pipe(unordered_map<int, Pipe>& pipe_group)
{
	unordered_map<int, Pipe>::iterator number;
	unsigned int index;
	cout << "Введите ID трубы, которую нужно удалить: ";
	index = checking(1u, Pipe::GetMaxID(), "Введите ID трубы, которую нужно удалить: ");
	number = pipe_group.find(index);
	pipe_group.erase(number);
}

void delete_cs(unordered_map<int, CS>& cs_group)
{
	unordered_map<int, CS>::iterator number;
	unsigned int index;
	cout << "Введите ID КС, которую нужно удалить: ";
	index = checking(1u, CS::GetMaxID(), "Введите ID КС, которую нужно удалить: ");
	number = cs_group.find(index);
	cs_group.erase(number);
}

string file_name()
{
	string name_file;
	cout << "Введите название файла: ";
	cin.ignore(1, '\n');
	getline(cin, name_file);
	return name_file;
}

void menu()
{
	cout << endl;
	cout << "1.Добавить трубу" << endl;
	cout << "2.Добавить КС" << endl;
	cout << "3.Просмотр информации о трубе" << endl;
	cout << "4.Просмотр информации о КС" << endl;
	cout << "5.Редактировать трубу" << endl;
	cout << "6.Редактировать КС" << endl;
	cout << "7.Сохранить все" << endl;
	cout << "8.Загрузить все" << endl;
	cout << "9. Поиск труб по признаку repair" << endl;
	cout << "10. Поиск КС по проценту незадействованных цехов" << endl;
	cout << "11. Поиск КС по названию" << endl;
	cout << "12. Удалить трубу" << endl;
	cout << "13. Удалить КС" << endl;
	cout << "14. Пакетное редактирование труб" << endl;
	cout << "15. Создать/изменить граф" << endl;
	cout << "16. Просмотр графа" << endl;
	cout << "17. Удалить граф" << endl;
	cout << "18. Топологическая сортировка графа" << endl;
	cout << "19. Удалить КС из графа" << endl;



	cout << "0.Выход" << endl;
}

template<typename PC, typename T>
using Filter = bool(*)(PC& pc, T param);

bool CheckByName(CS& cs, string param)
{
	return cs.Get_Name() == param;
}

bool CheckByRepair(Pipe& pipe, bool repair)
{
	return pipe.GetRepair() == repair;
}

bool CheckBy_Notworking_CS(CS& cs, float percent)
{
	return abs(percent - ((float)(cs.Get_amount() - (float)cs.Get_amount_work()) / (float)cs.Get_amount() * 100)) < 1e-6;
}


template<typename PC, typename T>
vector<int> Find_PipeOrCS_ByFilter(unordered_map<int, PC>& pc, Filter<PC, T> f, T param)
{
	vector <int> res;
	res.reserve(pc.size());
	for (auto& pipe_or_cs : pc)
	{
		if (f(pipe_or_cs.second, param))
			res.push_back(pipe_or_cs.first);
	}
	return res;
}

struct p_id_in
{
	int cs_id_in;
	int pipe_id;
};

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

template <typename T>
void Print_Graph(T graph)
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


bool dfs(int cs_id, int& cycle_status, unordered_map<int, vector<p_id_in>> graph,  unordered_map<int,char> color, unordered_map<int, int>& used_cs, vector <int>& ans)
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
	unordered_map<int,char> color;	
	unordered_map<int, int> used_cs;
	for (auto& i : graph)
	{
		color[i.first] = false;
		used_cs[i.first] = -1;
	}
	int cycle_status = -1;
	for (auto& el : color)
	{
		if (dfs(el.first, cycle_status, graph, color, used_cs , ans))
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

void find_shortest_path(unordered_map<int, vector<p_id_in>>& graph, unordered_map<int, Pipe>& pipe_group )
{
	cout << "Введите id КС - начало пути: ";
	int id_from = checking(1u, CS::GetMaxID(), "Введите id КС - начало пути: ");
	cout << "Введите id КС - конец пути: ";
	int id_to = checking(1u, CS::GetMaxID(), "Введите id КС - конец пути: ");
	if (graph.find(id_from) != graph.end())
	{
		unordered_map <int,int> distance;
		unordered_map <int,bool> passed;
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
				if (!passed[i1] && distance[index] != INT_MAX && distance[index] + pipe_group[i1].GetWeight() < distance[i1])
				{
					distance[i1] = distance[index] + pipe_group[i1].GetWeight();
					p[i1] = index;
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
		for (auto i=path.begin() ; i!=path.end();i++)
		{
			if (i + 1 != path.end()) cout << *i << " -> ";
			else cout << *i;
		}
		}
		else cout << id_from << " -> " << id_to << " - пути нет";
	}
	else cout << "Невозможно!" << endl;
}


int bfs(unordered_map<int, vector<p_id_in>>& graph, int id_from, int id_to, vector<int>path, map <pair<int, int>, int> flow)
{
	vector<int>color; //цвета вершин
	vector <int>queue; //Очередь, хранящая номера вершин входящих в неё
	//vector<int>path; //массив пути
	//map <pair<int,int>,int> flow;
	map <pair<int, int>, int> capacity;
	

	for (int i = 0; i <= graph.size()-1; i++) 
		color[i] = 0; //отмечаем все вершины непройденными WHITE=0
	int head = 0;   // Начало очереди 0
	int tail = 0;   // Хвост 0

	queue[tail] = id_from;   // Вступили на первую вершину
	tail++;
	color[id_from] = 1;

	path[id_from] = -1;   // Специальная метка для начала пути
	while (head != tail) //Пока хвост не совпадет с головой
	{
		int u = queue[head]; //вершина u пройдена
		head++;
		color[u] = -1;

		for (int i = 0; i <= graph.size() - 1; i++) // Смотрим смежные вершины
		{
			// Если не пройдена и не заполнена
			if (color[i] == 0 && (capacity[make_pair(u, i)] - flow[make_pair(u, i)] > 0))
			{
				// Вступаем на вершину v
				queue[tail] = i;
				tail++;
				color[i] = 1;
				path[i] = u; // Путь обновляем
			}
		}
	}
	if (color[id_to] == -1) // Если конечная вершина, дошли - возвращаем 0, прочитанная
		return 0;
	else return 1;
}

void max_flow(unordered_map<int, vector<p_id_in>>& graph)
{
	cout << "Введите id КС - исток: ";
	int source = checking(1u, CS::GetMaxID(), "Введите id КС - исток: ");
	cout << "Введите id КС - сток: ";
	int stock = checking(1u, CS::GetMaxID(), "Введите id КС - сток: ");
	if (graph.find(source) != graph.end())
	{
		int u;
		int maxflow = 0;            // Изначально нулевой
		map <pair<int, int>, int> flow;
		vector<int>path;
		map <pair<int, int>, int> capacity;
		for (const auto& i:graph)  // Зануляем матрицу потока
		{
			for (const auto& j : graph)
				flow.emplace(make_pair(i.first,j.first),0);
		}
		while (bfs(graph,source, stock,path,flow) == 0)             // Пока сеществует путь
		{
			int delta = INT_MAX;
			for (u = graph.size() - 1; path[u] >= 0; u = path[u]) // Найти минимальный поток в сети
			{
				delta = min(delta, capacity[make_pair(path[u], u)] - flow[make_pair(path[u], u)]);
			}
			for (u = graph.size() - 1; path[u] >= 0; u = path[u]) // По алгоритму Форда-Фалкерсона 
			{
				flow[make_pair(u,path[u])] += delta;
				flow[make_pair(path[u], u)] -=delta;
			}
			maxflow += delta;                       // Повышаем максимальный поток
		}
		cout << "Максимальный поток: " << source << " -> " << stock << " = " << maxflow << endl;
	}
	else cout << "Невозможно!" << endl;
}


int main()
{
	setlocale(LC_ALL, "Russian");
	unordered_map<int, Pipe> pipe_group;
	unordered_map<int, CS> cs_group;
	unordered_map<int, vector<p_id_in>> graph;
	unordered_map<int, bool> used;

	while (true)
	{
		menu();
		int command;
		cout << "Введите команду: ";
		command = checking(0, 21, "Введите команду: ");
		switch (command)
		{
		case 0:
		{
			return 0;
		}
		case 1:
		{
			Pipe pipe;
			cin >> pipe;
			pipe_group.insert(pair<int, Pipe>(pipe.GetId(), pipe));
			break;
		}
		case 2:
		{
			CS cs;
			cin >> cs;
			cs_group.insert(pair<int, CS>(cs.GetId(), cs));
			break;

		}
		case 3:
		{
			if (pipe_group.size() > 0)
				for (auto& iter : pipe_group)
				{
					cout << endl;
					cout << iter.second << endl;
				}
			else cout << "Вы забыли ввести данные трубы!\n";
			system("Pause");
			break;
		}
		case 4:
		{
			if (cs_group.size() > 0)
				for (auto iter : cs_group)
				{
					cout << endl;
					cout << iter.second << endl;
				}
			else cout << "Вы забыли ввести данные КС!\n";
			system("Pause");
			break;
		}
		case 5:
		{
			unordered_map <int, Pipe>::iterator number;
			cout << "Введите ID трубы: ";
			if (pipe_group.size() > 0)
			{
				unsigned index = checking(1u, Pipe::GetMaxID(), "Введите ID трубы: ");
				number = pipe_group.find(index);
				number->second.editing_pipe();
			}
			else cout << "Вы забыли ввести данные трубы!\n";
			system("Pause");
			break;
		}
		case 6:
		{
			unordered_map <int, CS>::iterator number;
			cout << "Введите ID КС: ";
			if (cs_group.size() > 0)
			{
				unsigned index = checking(1u, CS::GetMaxID(), "Введите ID КС: ");
				number = cs_group.find(index);
				number->second.editing_cs();
			}
			else cout << "Вы забыли ввести данные КС!\n";
			system("Pause");
			break;
		}
		case 7:
		{
			ofstream fout;
			fout.open(file_name(), ios::out);
			if (fout.is_open())
			{
				if (pipe_group.size() > 0)
				{
					fout << pipe_group.size() << endl;
					for (auto iter : pipe_group)
						fout << iter.second;
				}
				else cout << "Вы забыли ввести данные для труб!\n";
				if (cs_group.size() > 0)
				{
					fout << endl;
					fout << cs_group.size() << endl;
					for (auto iter : cs_group)
						fout << iter.second;
				}
				else cout << "Вы забыли ввести данные для КС!\n";
				//graph
				fout << endl;
				for (auto& el : graph)
				{
					fout << el.second.size() << " ";
					fout << el.first << " ";
					for (auto cs = el.second.begin(); cs != el.second.end(); ++cs)
					{
						fout << cs->cs_id_in << " " << cs->pipe_id << " ";
					}
					fout << endl;
				}
				fout.close();
			}
			else cout << "Файл не открыт" << endl;
			system("Pause");
			break;
		}
		case 8:
		{
			ifstream fin;
			fin.open(file_name(), ios::in);
			if (fin.is_open())
			{
				pipe_group.erase(pipe_group.begin(), pipe_group.end());
				int count_pipe;
				fin >> count_pipe;
				for (int i = 1; i <= count_pipe; ++i)
				{
					Pipe pipe;
					fin >> pipe;
					pipe_group.insert(pair<int, Pipe>(pipe.GetId(), pipe));
				}

				cs_group.erase(cs_group.begin(), cs_group.end());
				int count_cs;
				fin >> count_cs;
				for (int i = 1; i <= count_cs; ++i)
				{
					CS cs;
					fin >> cs;
					cs_group.insert(pair<int, CS>(cs.GetId(), cs));
				}

				int count;
				while (fin >> count)
				{
					int cs_id_out;
					fin >> cs_id_out;
					for (int i = 0; i < count; i++)
					{
						int cs_id_in;
						fin >> cs_id_in;
						int pipe_id;
						fin >> pipe_id;
						p_id_in pair;
						pair.cs_id_in = cs_id_in;
						pair.pipe_id = pipe_id;
						pipe_group[pipe_id].SetId_CS_In(cs_id_in);
						pipe_group[pipe_id].SetId_CS_Out(cs_id_out);
						graph[cs_id_out].push_back(AddConnection(pipe_id, cs_id_in));
					}
				}
				fin.close();
			}
			else cout << "Файл не открыт" << endl;
			break;
		}
		case 9:
		{
			bool rep;
			cout << "Repair filter(1 or 0): ";
			rep = checking(0, 1, "Repair filter(1 or 0): ");
			if (pipe_group.size() != 0)
			{
				for (int i : Find_PipeOrCS_ByFilter(pipe_group, CheckByRepair, rep))
					cout << pipe_group[i];
			}
			else
				cout << "Забыли добавить трубы" << endl;
			system("pause");
			break;
		}
		case 10:
		{
			float perc;
			cout << "Введите процент незадействованных КС для поиска:";
			cin >> perc;
			if (cs_group.size() != 0)
			{

				for (int i : Find_PipeOrCS_ByFilter(cs_group, CheckBy_Notworking_CS, perc))
					cout << cs_group[i];
			}
			else
				cout << "Забыли добавить КС" << endl;
			system("pause");
			break;

		}
		case 11:
		{
			string name;
			cout << "Введите название КС для поиска: ";
			cin.ignore(1, '\n');
			getline(cin, name);
			if (cs_group.size() != 0)
			{
				for (int i : Find_PipeOrCS_ByFilter(cs_group, CheckByName, name))
					cout << cs_group[i];
			}
			else
				cout << "Забыли добавить КС" << endl;
			system("pause");
			break;

		}
		case 12:
		{
			if (pipe_group.size() > 0)
				delete_pipe(pipe_group); else cout << "Вы забыли ввести трубы!" << endl;
			break;
		}
		case 13:
		{
			if (cs_group.size() > 0)
				delete_cs(cs_group); else cout << "Вы забыли ввести КС!" << endl;
			break;
		}
		case 14:
		{
			unsigned int k;
			k = 0;
			bool rep;
			cout << "Repair filter(1 or 0): ";
			rep = checking(0, 1, "Repair filter(1 or 0): ");
			if (pipe_group.size() != 0)
			{
				for (int& i : Find_PipeOrCS_ByFilter(pipe_group, CheckByRepair, rep))
				{
					k = k + 1;
					cout << "Редактирование " << k << "-й найденной трубы" << endl;
					pipe_group[i].editing_pipe();
				}
			}
			else
				cout << "Забыли добавить трубы" << endl;
			system("pause");
			break;
		}
		case 15:
		{
			//Graph_add_menu
			bool next = 1;
			for (auto iter : pipe_group)
				used[iter.second.GetId()] = iter.second.GetId_CS_In() != 0;
			while (next && pipe_group.size() > 0 && cs_group.size() >= 2)
			{
				cout << "Введите id трубы, которая будет соединять 2 КС: ";
				int pipe_id = checking(1u, Pipe::GetMaxID(), "Введите id трубы, которая будет соединять 2 КС: ");
				while (pipe_group.find(pipe_id) == pipe_group.end() || pipe_group.find(pipe_id)->second.GetRepair() || used[pipe_id])
				{
					cout << "Ошибка! Попробуйте снова" << endl;
					cout << "Введите id трубы, которая будет соединять 2 КС: ";
					pipe_id = checking(1u, Pipe::GetMaxID(), "Введите id трубы, которая будет соединять 2 КС: ");
				}
				used[pipe_id] = true;
				cout << "Введите id КС, из которой выходит труба: ";
				int cs_id_out = checking(1u, CS::GetMaxID(), "Введите id КС, из которой выходит труба: ");
				while (cs_group.find(cs_id_out) == cs_group.end())
				{
					cout << "Ошибка! Попробуйте снова" << endl;
					cout << "Введите id КС, из которой выходит труба: ";
					cs_id_out = checking(1u, CS::GetMaxID(), "Введите id КС, из которой выходит труба: ");
				}
				cout << "Введите id КС, в которую входит труба: ";
				int cs_id_in = checking(1u, CS::GetMaxID(), "Введите id КС, в которую входит труба: ");
				while (cs_group.find(cs_id_in) == cs_group.end())
				{
					cout << "Ошибка! Попробуйте снова" << endl;
					cout << "Введите id КС, в которую входит труба: ";
					cs_id_in = checking(1u, CS::GetMaxID(), "Введите id КС, в которую входит труба: ");
				}
				cout << endl;
				cout << "Введите 1, чтобы продолжить; 0 - остановиться" << endl;
				next = checking(0, 1, "Введите 1, чтобы продолжить; 0 - остановиться");
				pipe_group.find(pipe_id)->second.in_Pipe_out(cs_id_out, cs_id_in);
				graph[cs_id_out].push_back(AddConnection(pipe_id, cs_id_in));
			}
			break;
		}
		case 16:
		{
			Print_Graph(graph);
			break;
		}
		case 17:
		{
			graph.clear();
			cout << "Граф удален!" << endl;
			for (auto& iter : pipe_group)
			{ 
				iter.second.SetId_CS_In(0);
				iter.second.SetId_CS_Out(0);
			}
			break;
		}
		case 18:
		{
			vector<int> ans;
			topological_sort(graph, ans);
			for (auto index = ans.begin(); index != ans.end(); index++)
			{
				cout << *index;
				if (index + 1 != ans.end())
					cout << " - ";
			}
			break;
		}
		case 19:
		{
			cout << "Введите id КС, которую хотите удалить из графа: ";
			int cs_id_delete = checking(1u, CS::GetMaxID(), "Введите id КС, которую хотите удалить из графа: ");
			cs_delete_fromGraph(graph, cs_group, cs_id_delete);
			break;
		}
		case 20:
		{
			find_shortest_path(graph, pipe_group);
			break;
		}
		case 21:
		{
			max_flow(graph);
			break;
		}
		}
	}
}

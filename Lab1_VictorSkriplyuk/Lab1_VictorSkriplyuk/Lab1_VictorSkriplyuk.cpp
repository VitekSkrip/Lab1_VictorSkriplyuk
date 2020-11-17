#include<iostream>
#include<fstream>
#include <string>
#include <vector>
#include "Pipe.h"
using namespace std;

struct CS
{
	int id;
	string name;
	int amount;
	int amount_work;
	float perfomance;
};


template <typename T>
bool IsCorrect(T& var, int left, int right)
{
	return var >= left && var <= right;
}

template <typename T>       // шаблон "template" - для работы с обобщенным типом данных
							//нашел по ссылке - http://cppstudio.com/post/5188/ 
void checking(T& var, string com, int left,int right)
{
	do
	{
		cin.clear();
		cin.ignore(10000, '\n');
		cout << com;
		cin >> var;
	} while (cin.fail() || !IsCorrect(var,left,right));
}

//int GetCorrectNumber(int left, int right)
//{
//	int x;
//	while (((cin >> x)).fail() || !IsCorrect(x, left, right))
//	{
//		cin.clear();
//		cin.ignore(10000, '\n');
//		cout << "Ошибка при вводе!" << endl << "Введите команду: ";
//	}
//	return x;
//}


void addpipe(Pipe& pipe)
{
	cin >> pipe;
}

void addcs(CS& cs)
{
	checking(cs.id, "Введите идентификатор: ",0, 10000);

	cout << "Введите название: ";
	cin.clear();
	cin.ignore();
	getline(cin, cs.name);			//нашел по ссылке: http://espressocode.top/getline-string-c/
									// нужно для того, чтобы считывало не одно слово - но не знаю, почему пропускает одну строчку в консоли

	checking(cs.amount, "Введите количество цехов: ",0,1000);
	checking(cs.amount_work, "Введите количество цехов в работе: ", 0, cs.amount);
	checking(cs.perfomance, "Введите эффективность: ", 0, 1);
}

void view_pipe(const Pipe& pipe)
{
	cout << endl;
	cout << pipe << endl;
}

void view_cs(const CS& cs)
	{
		cout << endl;
		cout << "Компрессорная станция" << endl;
		cout << "Идентификатор: " << cs.id << endl;
		cout << "Название: " << cs.name << endl;
		cout << "Количество цехов: " << cs.amount << endl;
		cout << "Количество рабочих цехов: " << cs.amount_work << endl;
		cout << "Эффективность: " << cs.perfomance << endl;
	}

void editing_pipe(Pipe& pipe)
	{
		checking(pipe.repair, "Ремонт: ",0,1);
	}

void editing_cs(CS& cs)
	{
		int x;
		checking(x, "Запуск цеха - 1; Остановка цеха - 0\n", 0, 1);
		if (x == 1)
		{
			if (cs.amount_work + 1 <= cs.amount)
			{
				cs.amount_work++;
				cout << "Новое количество рабочих цехов: " << cs.amount_work << endl;
			}
			else
			{
				cout << "Нельзя запустить цех!" << endl;
			}
		}
		else
		{
			if (cs.amount_work-1 >= 0)
			{
				cs.amount_work--;
				cout << "Новое количество рабочих цехов: " << cs.amount_work << endl;
			}
			else
			{
				cout << "Нельля прекратить работу цехов!" << endl;
			}
		}
	}
 
//void savePIPE_into_file(ofstream& fout, const Pipe& pipe)
//{
//	fout << pipe.id << ' ' << pipe.length << ' ' << pipe.diam << ' ' << pipe.repair;
//
//}


void saveCS_into_file(ofstream& fout, const CS& cs)
{
	fout << cs.id << endl;
	fout << cs.name << endl;
	fout << cs.amount << endl;
	fout << cs.amount_work << endl;
	fout << cs.perfomance << endl;
}

//Pipe loadPipe_from_file(ifstream& fin)
//{
//	Pipe pipe;
//	fin >> pipe.id >> pipe.length >> pipe.diam >> pipe.repair;
//	return pipe;
//}

CS loadCS_from_file(ifstream& fin)
{
	CS cs;
	fin >> cs.id >> cs.name >> cs.amount >> cs.amount_work >> cs.perfomance;
	return cs;
}

void menu()
{
	system("cls");
	cout << "1.Добавить трубу" << endl;
	cout << "2.Добавить КС" << endl;
	cout << "3.Просмотр информации о трубе" << endl;
	cout << "4.Просмотр информации о КС" << endl;
	cout << "5.Редактировать трубу" << endl;
	cout << "6.Редактировать КС" << endl;
	cout << "7.Сохранить трубу" << endl;
	cout << "8.Сохранить КС" << endl;
	cout << "9.Загрузить трубы" << endl;
	cout << "10.Загрузить КС" << endl;
	cout << "11. Поиск труб по признаку repair" << endl;
	cout << "0.Выход" << endl;
	cout << "Введите команду: ";
}

Pipe& SelectPipe(vector<Pipe>& g)
{
	unsigned int index;
	checking(index, "Введите идентификатор: ", 1u, g.size());
	return g[index-1];
}

CS& SelectCS(vector<CS>& g)
{
	unsigned int index;
	checking(index, "Введите идентификатор: ", 1u, g.size());
	return g[index - 1];
}

vector<int> FindPipesByRepair(const vector<Pipe>& pipe_group, bool rep="1")
{
	vector <int> res;
	int i = 0;
	for (auto& pipe : pipe_group)
	{
		if (pipe.repair == rep)
			res.push_back(i);
		i++;
	}
	return res;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	vector <Pipe> pipe_group;
	vector <CS> cs_group;




	bool pipe_exist = false;
	bool cs_exist = false;
	while (true)
	{
		menu();
		int command = 0;
		checking(command, "", 0, 11);
		switch (command)
		{
		case 0:
		{
			return 0;
		}
		case 1:
		{
			Pipe pipe;
			addpipe(pipe);
			pipe_exist = true;
			pipe_group.push_back(pipe);
			break;
		}
		case 2:
		{
			CS cs;
			addcs(cs);
			cs_exist = true;
			cs_group.push_back(cs);
			break;
			
		}
		case 3:
		{
			Pipe pipe;
			for (auto pipe:pipe_group)
				if (pipe_exist) view_pipe(pipe); else cout << "Вы забыли ввести данные трубы!\n";
			system("Pause");
			break;
		}
		case 4:
		{
			CS cs;
			for (auto cs:cs_group)
			if (cs_exist)  view_cs(cs); else cout << "Вы забыли ввести данные КС!\n";
			system("Pause");
			break;
		}
		case 5:
		{
			if (pipe_exist) editing_pipe(SelectPipe(pipe_group)); else cout << "Вы забыли ввести данные трубы!\n";
			system("Pause");
			break;
		}
		case 6:
		{
			if (cs_exist) editing_cs(SelectCS(cs_group)); else cout << "Вы забыли ввести данные КС!\n";
			system("Pause");
			break;
		}
	/*	case 7:
		{
			ofstream fout;
			fout.open("Data_Pipe.txt", ios::out);
			if (fout.is_open())
			{
				fout << pipe_group.size() << endl;
				for (Pipe pipe : pipe_group)
					if (pipe_exist)
						savePIPE_into_file(fout, pipe); else cout << "Вы забыли ввести данные для труб!\n";
				fout.close();
			}
			system("Pause");
			break;
		}*/
		case 8:
		{
			ofstream fout;
			fout.open("Data_CS.txt", ios::out);
			if (fout.is_open()) 
			{
				fout << cs_group.size() << endl;
				for (CS cs:cs_group)
					if (cs_exist) 
						saveCS_into_file(fout,cs); else cout << "Вы забыли ввести данные для КС!\n";
				fout.close();
			}	
			system("Pause");
			break;
		}
		/*case 9:
		{
			Pipe pipe;
			ifstream fin;
			fin.open("Data_Pipe.txt", ios::in);
				if (fin.is_open())
				{
					int count;
					fin >> count;
					pipe_group.reserve(count);
					for (count; count>0; count--) 
						pipe_group.push_back(loadPipe_from_file(fin));
					fin.close();
				}
			pipe_exist = true;
			break;
		}*/
		case 10:
		{
			CS cs;
			ifstream fin;
			fin.open("Data_CS.txt", ios::in);
				if (fin.is_open())
				{
					cs_group.push_back(loadCS_from_file(fin));
					fin.close();
				}
			cs_exist = true;
			break;
		}
		case 11:
		{
			for (int i : FindPipesByRepair(pipe_group))
				cout<<pipe_group[i];
			break;
		}
		}
	}
}


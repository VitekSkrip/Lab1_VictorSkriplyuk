#include<iostream>
#include<fstream>
#include <string>
#include <vector>
using namespace std;

struct Pipe
{
	int id;
	float length;
	float diam;
	bool repair;
};

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

int GetCorrectNumber(int left, int right)
{
	int x;
	while (((cin >> x)).fail() || !IsCorrect(x, left, right))
	{
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Ошибка при вводе!" << endl << "Введите команду: ";
	}
	return x;
}


void addpipe(Pipe& pipe)
{
	checking(pipe.id,"Введите идентификатор: ",0,100000);
	checking(pipe.length, "Введите длину: ",0,200);
	checking(pipe.diam, "Введите диаметр: ",0,200);
	checking(pipe.repair, "Ремонт: ",0,1);
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
	cout << "Труба" << endl;
	cout << "Идентификатор: " << pipe.id << endl;
	cout << "Длина: " << pipe.length << endl;
	cout << "Диаметр: " << pipe.diam << endl;
	cout << "Ремонт: " << pipe.repair << endl;
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
 
void savePIPE_into_file(ofstream& fout, const Pipe& pipe)
{
	fout << "Идентификатор: " << pipe.id << endl;
	fout << "Длина: " << pipe.length << endl;
	fout << "Диаметр: " << pipe.diam << endl;
	fout << "Ремонт: " << pipe.repair << endl;
}


void saveCS_into_file(ofstream& fout, const CS& cs)
{
	fout << "Идентификатор: " << cs.id << endl;
	fout << "Название: " << cs.name << endl;
	fout << "Количество цехов: " << cs.amount << endl;
	fout << "Количество рабочих цехов: " << cs.amount_work << endl;
	fout << "Эффективность: " << cs.perfomance << endl;
}

void loadPipe_from_file(ifstream& fin, Pipe& pipe)
{
	fin >> pipe.id >> pipe.length >> pipe.diam >> pipe.repair;
}

void loadCS_from_file(ifstream& fin, CS& cs)
{
	fin >> cs.id >> cs.name >> cs.amount >> cs.amount_work >> cs.perfomance;
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
	cout << "9.Загрузить" << endl;
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
		switch (GetCorrectNumber(0,9))
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
			if (pipe_exist) view_pipe(SelectPipe(pipe_group)); else cout << "Вы забыли ввести данные трубы!\n";
			system("Pause");
			break;
		}
		case 4:
		{

			if (cs_exist)  view_cs(SelectCS(cs_group)); else cout << "Вы забыли ввести данные КС!\n";
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
		case 7:
		{
			ofstream fout;
			fout.open("OutPut_Pipe.txt", ios::out);
			if (fout.is_open())
			{
				for (Pipe pipe : pipe_group)
					if (pipe_exist)
						savePIPE_into_file(fout, pipe); else cout << "Вы забыли ввести данные для труб!\n";
				fout.close();
			}
			system("Pause");
			break;
		}
		case 8:
		{
			ofstream fout;
			fout.open("OutPut_CS.txt", ios::out);
			if (fout.is_open())
			{
				for (CS cs:cs_group)
					if (cs_exist) 
						saveCS_into_file(fout,cs); else cout << "Вы забыли ввести данные для КС!\n";
				fout.close();
			}	
			system("Pause");
			break;
		}
		case 9:
		{
			Pipe pipe;
			ifstream fin;
			fin.open("InPutPipe.txt", ios::in);
				if (fin.is_open())
				{
					pipe_group.push_back(loadPipe_from_file(fin, pipe));
					fin.close();
				}
			pipe_exist = true;
			break;
		}
		case 10:
		{
			CS cs;
			ifstream fin;
			fin.open("InPutCS.txt", ios::in);
				if (fin.is_open())
				{
					cs_group.push_back(loadCS_from_file(fin,cs));
					fin.close();
				}
			cs_exist = true;
			break;
		}
		}
	}
}


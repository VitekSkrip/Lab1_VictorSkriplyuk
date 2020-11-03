#include<iostream>
#include<fstream>
#include <string>
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
	do
	{ 
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Введите название: ";
		getline(cin, cs.name);  //нашел по ссылке: http://espressocode.top/getline-string-c/
								// нужно для того, чтобы считывало не одно слово - но не знаю, почему пропускает одну строчку в консоли
	} while (cin.fail());

	checking(cs.amount, "Введите количество цехов: ",0,1000);
	checking(cs.amount_work, "Введите количество цехов в работе: ", 0, cs.amount);
	checking(cs.perfomance, "Введите эффективность: ", 0, 1);
}

void view_pipe(Pipe pipe)
{
		cout << endl;
		cout << "Труба" << endl;
		cout << "Идентификатор: " << pipe.id << endl;
		cout << "Длина: " << pipe.length << endl;
		cout << "Диаметр: " << pipe.diam << endl;
		cout << "Ремонт: " << pipe.repair << endl;
}

void view_cs(CS cs)
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
 
void savePIPE_into_file(Pipe pipe)
{
	ofstream outf("OutPut_Pipe.txt");
	if (!outf.is_open())
		cout << "Файл не может быть открыт!\n";
	else
	{ 
	outf << "Труба" << endl; 
	outf << "Идентификатор: " << pipe.id << endl;
	outf << "Длина: " << pipe.length << endl;
	outf << "Диаметр: " << pipe.diam << endl;
	outf << "Ремонт: " << pipe.repair << endl;
	outf.close();
	}
}

void saveCS_into_file(CS cs)
{
	ofstream outf("OutPut_CS.txt");
	if (!outf.is_open())
		cout << "Файл не может быть открыт!\n";
	else
	{
		outf << endl;
		outf << "Компрессорная станция" << endl;
		outf << "Идентификатор: " << cs.id << endl;
		outf << "Название: " << cs.name << endl;
		outf << "Количество цехов: " << cs.amount << endl;
		outf << "Количество рабочих цехов: " << cs.amount_work << endl;
		outf << "Эффективность: " << cs.perfomance << endl;
	}
}

void load_from_file(Pipe& pipe, CS& cs)
{
	ifstream fin("InPut.txt");
	if (!fin.is_open())
		cout << "Файл не может быть открыт!\n";
	else
	{
		fin >> pipe.id >> pipe.length >> pipe.diam >> pipe.repair;
		fin >> cs.id >> cs.name >> cs.amount >> cs.amount_work >> cs.perfomance;
		fin.close();
	}
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

int main()
{
	setlocale(LC_ALL, "Russian");
	Pipe pipe;
	CS cs;
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
			addpipe(pipe);
			pipe_exist = true;
			break;
		}
		case 2:
		{
			addcs(cs);
			cs_exist = true;
			break;
			
		}
		case 3:
		{
			view_pipe(pipe);
			system("Pause");
			pipe_exist = true;
			break;
		}
		case 4:
		{
			view_cs(cs);
			system("Pause");
			cs_exist = true;
			break;
		}
		case 5:
		{
			if (pipe_exist) editing_pipe(pipe); else cout << "Вы забыли ввести данные трубы!";
			system("Pause");
			break;
		}
		case 6:
		{
			if (cs_exist) editing_cs(cs); else cout << "Вы забыли ввести данные КС!";
			system("Pause");
			break;
		}
		case 7:
		{
			if (pipe_exist) savePIPE_into_file(pipe); else cout << "Вы забыли ввести данные для трубы! \n";
			system("Pause");
			break;
		}
		case 8:
		{
			if (cs_exist) saveCS_into_file(cs); else cout << "Вы забыли ввести данные для КС! \n";
			system("Pause");
			break;
		}
		case 9:
		{
			load_from_file(pipe, cs);
			pipe_exist = true;
			cs_exist = true;
			break;
		}
		}
	}
}


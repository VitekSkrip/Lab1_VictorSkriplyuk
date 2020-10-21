#include<iostream>
#include<fstream>
using namespace std;

struct Pipe
{
	int id;
	float length;
	float diam;
	bool repair;
	bool exist = false;
};

struct CS
{
	int id;
	string name;
	int amount;
	int amount_work;
	float perfomance;
	bool exist = false;
};

template <typename T>       // шаблон "template" - для работы с обобщенным типом данных
//нашел по ссылке - http://cppstudio.com/post/5188/ 
void checking(T& var, string com)
{
	do
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << com;
		cin >> var;
	} while (var < 0 || cin.fail());
}

void addpipe(Pipe& pipe1)
{
	string x;

	x = "Введите идентификатор: ";
	checking(pipe1.id,x);

	x = "Введите длину: ";
	checking(pipe1.length,x);

	x = "Введите диаметр: ";
	checking(pipe1.diam,x);

	x = "Ремонт: ";
	checking(pipe1.repair, x);

	pipe1.exist = true;

}

void addcs(CS& cs1)
{
	string x;

	x = "Введите идентификатор: ";
	checking(cs1.id,x);

	cout << "Введите название: ";
	cin >> cs1.name;

	x = "Введите количество цехов: ";
	checking(cs1.amount,x);

	do {
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Введите количество цехов в работе: ";
		cin >> cs1.amount_work;
	} while (cs1.amount_work>cs1.amount || cs1.amount_work< 0 || cin.fail());

	x = "Введите показатель эффективности: ";
	checking(cs1.perfomance,x);
	
	cs1.exist = true;


}

void view(Pipe pipe1, CS cs1)
{
	if (pipe1.exist == true)
	{
		cout << endl;
		cout << "Труба" << endl;
		cout << "Идентификатор: " << pipe1.id << endl;
		cout << "Длина: " << pipe1.length << endl;
		cout << "Диаметр: " << pipe1.diam << endl;
		cout << "Ремонт: " << pipe1.repair << endl;
	}
	else
	{
		cout << "Вы забыли ввести данные для трубы!" << endl;
	}
	if (cs1.exist == true)
	{
		cout << endl;
		cout << "Компрессорная станция" << endl;
		cout << "Идентификатор: " << cs1.id << endl;
		cout << "Название: " << cs1.name << endl;
		cout << "Количество цехов: " << cs1.amount << endl;
		cout << "Количество рабочих цехов: " << cs1.amount_work << endl;
		cout << "Эффективность: " << cs1.perfomance << endl;
	}
	else
	{
		cout << "Вы забыли ввести данные для КС!" << endl;
	}
}

void editing(Pipe& pipe1)
{
	if (pipe1.exist == true)
	{
		string x;
		cout << endl;

		x = "Ремонт: ";
		checking(pipe1.repair, x);
	}
	else
	{
		cout << "Вы забыли ввести данные для трубы" << endl;
	}
}

void ceh(CS& cs1)
{
	if (cs1.exist == true)
	{
		cout << "Запуск цеха - 1; Остановка цеха - 0" << endl;
		int x;
		cin >> x;
		if (x == 1)
		{
			if (cs1.amount <= cs1.amount_work)
			{
				cout << "Ошибка" << endl;
			}
			else
			{
				cs1.amount_work++;
				cout << "Новое количество рабочих цехов: " << cs1.amount_work << endl;
			}
		}
		else
		{
			if (cs1.amount < cs1.amount_work)
			{
				cout << "Ошибка" << endl;
			}
			else
			{
				if (cs1.amount_work > 0)
				{
					cs1.amount_work--;
					cout << "Новое количество рабочих цехов: " << cs1.amount_work << endl;
				}
				else
				{
					cout << "Ошибка" << endl;
				}
			}
		}
	}
	else
	{
		cout << "Вы забыли ввести данные для КС!" << endl;
	}

}

void output(Pipe pipe1, CS cs1)
{
	ofstream outf("OutPut.txt");
	if (pipe1.exist == true)
	{
		outf << "Труба" << endl;
		outf << "Идентификатор: " << pipe1.id << endl;
		outf << "Длина: " << pipe1.length << endl;
		outf << "Диаметр: " << pipe1.diam << endl;
		outf << "Ремонт: " << pipe1.repair << endl;
	}
	else
	{
		cout << "Вы забыли ввести данные для трубы!" << endl;
		outf << "Вы забыли ввести данные для трубы!" << endl;
	}
	if (cs1.exist == true)
	{
		outf << endl;
		outf << "Компрессорная станция" << endl;
		outf << "Идентификатор: " << cs1.id << endl;
		outf << "Название: " << cs1.name << endl;
		outf << "Количество цехов: " << cs1.amount << endl;
		outf << "Количество рабочих цехов: " << cs1.amount_work << endl;
		outf << "Эффективность: " << cs1.perfomance << endl;
	}
	else
	{
		cout << "Вы забыли ввести данные для КС!" << endl;
		outf << "Вы забыли ввести данные для КС!";
	}
}

void input(Pipe& pipe1, CS& cs1)
{
	ifstream fin("InPut.txt");
	pipe1.exist = true;
	cs1.exist = true;
	if (!fin.is_open())
		cout << "Файл не может быть открыт!\n";
	else
	{
		fin >> pipe1.id >> pipe1.length >> pipe1.diam >> pipe1.repair;
		fin >> cs1.id >> cs1.name >> cs1.amount >> cs1.amount_work >> cs1.perfomance;
	}
}



void menu()
{
	system("cls");
	cout << "1.Добавить трубу" << endl;
	cout << "2.Добавить КС" << endl;
	cout << "3.Просмотр всех объектов" << endl;
	cout << "4.Редактировать трубу" << endl;
	cout << "5.Редактировать КС" << endl;
	cout << "6.Сохранить" << endl;
	cout << "7.Загрузить" << endl;
	cout << "0.Выход" << endl;
	cout << "Введите команду: ";

}

int GetCorrectNumber(int left, int right)
{
	int x;
	while (((cin >> x)).fail() || x<left || x>right)
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Ошибка при вводе!" << endl << "Введите команду: ";
	}
	return x;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	Pipe pipe1;
	CS cs1;
	while (true)
	{
		menu();
		switch (GetCorrectNumber(0,7))
		{
		case 0:
		{
			return 0;
		}
		case 1:
		{
			addpipe(pipe1);
			break;
		}
		case 2:
		{
			addcs(cs1);
			break;
		}
		case 3:
		{
			view(pipe1, cs1);
			system("Pause");
			break;
		}
		case 4:
		{
			editing(pipe1);
			system("Pause");
			break;
		}
		case 5:
		{
			ceh(cs1);
			system("Pause");
			break;
		}
		case 6:
		{
			output(pipe1, cs1);
			system("Pause");
			break;
		}
		case 7:
		{
			input(pipe1, cs1);
			break;
		}
		}
	}
}


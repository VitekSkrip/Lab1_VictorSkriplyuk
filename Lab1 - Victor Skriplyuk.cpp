#include<iostream>
#include<fstream>
using namespace std;

struct Pipe
{
	int id;
	float length;
	float diam;
	bool repair = false;
	bool exist = false;
};

struct CS
{
	
	int id;
	string name;
	int amount;
	int amount_work;
	float perfomance;
	bool exist=false;
};

void addpipe(Pipe& pipe1)
{
	cout << "Введите идентификатор: ";
	cin >> pipe1.id;
	cout << "Введите длину: ";
	cin >> pipe1.length;
	cout << "Введите диаметр: ";
	cin >> pipe1.diam;
	cout << "HZ: ";
	cin >> pipe1.repair;
	pipe1.exist= true;

}

void addcs(CS& cs1)
{
	cout << "Введите идентификатор: ";
	cin >> cs1.id;
	cout << "Введите название: ";
	cin >> cs1.name;
	cout << "Введите количество цехов: ";
	cin >> cs1.amount;
	cout << "Введите количество цехов в работе: ";
	cin >> cs1.amount_work;
	cout << "Введите эффективность: ";
	cin >> cs1.perfomance;
	cs1.exist = true;


}

void view(Pipe pipe1, CS cs1)
{
	cout << endl;
	cout << "Труба" << endl;
	cout << "Идентификатор: " << pipe1.id << endl;
	cout << "Длина: " << pipe1.length << endl;
	cout << "Диаметр: " << pipe1.diam << endl;
	cout << "HZ: " << pipe1.repair << endl;
	cout << endl;
	cout << "Компрессорная станция" << endl;
	cout << "Идентификатор: " << cs1.id << endl;
	cout << "Название: " << cs1.name << endl;
	cout << "Количество цехов: " << cs1.amount << endl;
	cout << "Количество рабочих цехов: " << cs1.amount_work << endl;
	cout << "Эффективность: " << cs1.perfomance << endl;
	

}

void editing(Pipe& pipe1)
{
	cout << endl;
	cout << "HZ: ";
	cin >> pipe1.repair;
	
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
				cout << "Новое количество цехов: " << cs1.amount_work << endl;
			}
		}
		else
		{
			if (cs1.amount <= cs1.amount_work)
			{
				cout << "Ошибка" << endl;
			}
			else
			{
				if (cs1.amount_work > 0)
				{
					cs1.amount_work--;
					cout <<"Новое количество цехов: "<< cs1.amount_work << endl;
				}
				else
				{
					cout << "Ошибка" << endl;
				}
			}
		}


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
		outf << "HZ: " << pipe1.repair << endl;
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

	if (!fin.is_open())
		cout << "Файл не может быть открыт!\n"; 
	else
	{
		fin >> pipe1.id >> pipe1.length >> pipe1.diam >> pipe1.repair;
		fin >> cs1.id >> cs1.name >> cs1.amount >> cs1.amount_work >> cs1.perfomance;
	}
}


void check()
{
	do
	{
		cin.clear();
		cin.ignore(1000, '\n');
		int number;
		cin >> number;
	}
		while (cin.fail());
	
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



int main()
{
	setlocale(LC_ALL, "Russian");
	Pipe pipe1;
	CS cs1; 

	while (true)
	{
		menu();
		int number;
		cin >> number;
		switch (number)
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
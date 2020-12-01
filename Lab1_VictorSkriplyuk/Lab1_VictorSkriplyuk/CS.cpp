#include "CS.h"
#include "utils.h"
#include <string>
using namespace std;

int CS::MaxID = 0;

CS::CS()
{
	id = ++MaxID;
}

int CS::GetId()
{
	return id;
}

void CS::editing_cs()
{
	cout << "Введите новое количество рабочих цехов: ";
	amount_work = checking(0, amount, "Введите новое количество рабочих цехов: ");
}
		
ostream& operator << (ostream& out, const CS& cs)
{
	//out << "MaxID" << CS::MaxID << endl;
	out << "Идентификатор: " << cs.id << endl;
	out << "Название: " << cs.name << endl;
	out << "Количество цехов: " << cs.amount << endl;
	out << "Количество цехов в работе: " << cs.amount_work << endl;
	out << "Эффективность: " << cs.perfomance << endl;
	return out;
}


istream& operator >> (istream& in, CS& cs)
{
	cout << "Введите название: ";
	cin.ignore(1, '\n');
	getline(cin, cs.name);
	cout << "Введите количество цехов: ";
	cs.amount = checking(0, 1000, "Введите количество цехов: ");
	cout << "Введите количество цехов в работе: ";
	cs.amount_work=checking(0, cs.amount, "Введите количество цехов в работе: ");
	cout << "Введите эффективность: ";
	cs.perfomance=checking(0, 1, "Введите эффективность: ");
	return in;
}

ofstream& operator << (ofstream& fout, const CS& cs)
{
	fout << endl << cs.id << endl << cs.name << endl << cs.amount << endl << cs.amount_work << endl << cs.perfomance;
	return fout;
}

ifstream& operator >> (ifstream& fin, CS& cs)
{
	fin >> cs.id;
	fin.ignore(1, '\n');
	getline(fin, cs.name);
	fin >> cs.amount >> cs.amount_work >> cs.perfomance;
	return fin;
}


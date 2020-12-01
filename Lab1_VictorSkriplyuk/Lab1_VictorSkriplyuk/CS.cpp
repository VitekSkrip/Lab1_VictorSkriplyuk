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
	cout << "������� ����� ���������� ������� �����: ";
	amount_work = checking(0, amount, "������� ����� ���������� ������� �����: ");
}
		
ostream& operator << (ostream& out, const CS& cs)
{
	//out << "MaxID" << CS::MaxID << endl;
	out << "�������������: " << cs.id << endl;
	out << "��������: " << cs.name << endl;
	out << "���������� �����: " << cs.amount << endl;
	out << "���������� ����� � ������: " << cs.amount_work << endl;
	out << "�������������: " << cs.perfomance << endl;
	return out;
}


istream& operator >> (istream& in, CS& cs)
{
	cout << "������� ��������: ";
	cin.ignore(1, '\n');
	getline(cin, cs.name);
	cout << "������� ���������� �����: ";
	cs.amount = checking(0, 1000, "������� ���������� �����: ");
	cout << "������� ���������� ����� � ������: ";
	cs.amount_work=checking(0, cs.amount, "������� ���������� ����� � ������: ");
	cout << "������� �������������: ";
	cs.perfomance=checking(0, 1, "������� �������������: ");
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


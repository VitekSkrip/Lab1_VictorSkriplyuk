#include "Pipe.h"
#include "utils.h"
using namespace std;

unsigned int Pipe::MaxID = 0;

Pipe::Pipe()
{
	id = ++MaxID;
}

int Pipe::GetId()
{
	return id;
}

unsigned int Pipe::GetMaxID()
{
	return MaxID;
}

bool Pipe::GetRepair()
{
	return repair;
}


void Pipe::editing_pipe()
{
	repair = !repair;
	cout << "Successful editing to " << repair << endl;
}
ostream& operator << (ostream& out, const Pipe& pipe)
{
	//out << "MaxID" << Pipe::MaxID << endl;
	out << "Идентификатор: " << pipe.id << endl;
	out << "Длина: " << pipe.length << endl;
	out << "Диаметр: " << pipe.diam << endl;
	out << "Ремонт: " << pipe.repair << endl;
	return out;
}
istream& operator >> (istream& in, Pipe& pipe)
{
	cout << "Введите длину: ";
	pipe.length=checking(0, 200, "Введите длину: ");
	cout << "Введите диаметр: ";
	pipe.diam=checking(0, 200, "Введите диаметр: ");
	cout<<"Ремонт: ";
	pipe.repair=checking(0, 1, "Ремонт: ");
	return in;
}


ofstream& operator << (ofstream& fout, const Pipe& pipe)
{
	fout << endl << pipe.id << endl << pipe.length << endl << pipe.diam << endl << pipe.repair;
	return fout;
}

ifstream& operator >> (ifstream& fin, Pipe& pipe)
{
	fin >> pipe.id >> pipe.length >> pipe.diam >> pipe.repair;
	return fin;
}



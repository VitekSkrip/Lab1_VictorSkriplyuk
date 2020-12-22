#include "Pipe.h"
#include "utils.h"
using namespace std;

unsigned int Pipe::MaxID = 0;


Pipe::Pipe()
{
	id = ++MaxID;
	id_cs_in = 0;
	id_cs_out = 0;
}

int Pipe::GetId()
{
	return id;
}

int Pipe::GetId_CS_In()
{
	return id_cs_in;
}

int Pipe::GetId_CS_Out()
{
	return id_cs_out;
}

void Pipe::SetId_CS_Out(int id_cs_out)
{
	this->id_cs_out=id_cs_out;
}

void Pipe::SetId_CS_In(int id_cs_in)
{
	this->id_cs_in = id_cs_in;
}

void Pipe::in_Pipe_out(int cs_out, int cs_in)
{
	id_cs_out = cs_out;
	id_cs_in = cs_in;
}

unsigned int Pipe::GetMaxID()
{
	return MaxID;
}

bool Pipe::GetRepair()
{
	return repair;
}

int Pipe::GetCapacity() const
{
	return (int)sqrt(pow(diam, 5) / length);
}

int Pipe::GetWeight() const
{
	return (int)length;
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



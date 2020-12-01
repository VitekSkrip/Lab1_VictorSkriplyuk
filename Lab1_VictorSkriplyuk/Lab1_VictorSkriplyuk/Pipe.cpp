#include "Pipe.h"
#include "utils.h"
using namespace std;

int Pipe::MaxID = 0;

Pipe::Pipe()
{
	id = ++MaxID;
}

ostream& operator << (ostream& out, const Pipe& pipe)
{
	//out << "MaxID" << Pipe::MaxID << endl;
	out << "�������������: " << pipe.id << endl;
	out << "�����: " << pipe.length << endl;
	out << "�������: " << pipe.diam << endl;
	out << "������: " << pipe.repair << endl;
	return out;
}
istream& operator >> (istream& in, Pipe& pipe)
{
	cout << "������� �����: ";
	pipe.length=checking(0, 200, "������� �����: ");
	cout << "������� �������: ";
	pipe.diam=checking(0, 200, "������� �������: ");
	cout<<"������: ";
	pipe.repair=checking(0, 1, "������: ");
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



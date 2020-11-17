#include "Pipe.h"
#include "utils.h"
using namespace std;

int ID = 0;

Pipe::Pipe()
{
	id = ID++;
}

ostream& operator << (ostream& out, const Pipe& pipe)
{
	out << "�������������: " << pipe.id << endl;
	out << "�����: " << pipe.length << endl;
	out << "�������: " << pipe.diam << endl;
	out << "������: " << pipe.repair << endl;
	return out;
}
istream& operator >> (istream& in, const Pipe& pipe)
{
	//checking(pipe.id, in, "������� �������������: ", 0, 100000);
	checking(pipe.length, "������� �����: ", 0, 200);
	checking(pipe.diam,"������� �������: ", 0, 200);
	checking(pipe.repair,"������: ", 0, 1);
	return in;
}



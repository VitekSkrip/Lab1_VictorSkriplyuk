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
	out << "Идентификатор: " << pipe.id << endl;
	out << "Длина: " << pipe.length << endl;
	out << "Диаметр: " << pipe.diam << endl;
	out << "Ремонт: " << pipe.repair << endl;
	return out;
}
istream& operator >> (istream& in, const Pipe& pipe)
{
	//checking(pipe.id, in, "Введите идентификатор: ", 0, 100000);
	checking(pipe.length, "Введите длину: ", 0, 200);
	checking(pipe.diam,"Введите диаметр: ", 0, 200);
	checking(pipe.repair,"Ремонт: ", 0, 1);
	return in;
}



#include "Pipe.h"
#include "utils.h"
using namespace std;

int Pipe::MaxID = 0;

Pipe::Pipe()
{
	id = MaxID++;
}

ostream& operator << (ostream& out, const Pipe& pipe)
{
	out << "MaxID: " << Pipe::MaxID << endl;
	out << "Идентификатор: " << pipe.id << endl;
	out << "Длина: " << pipe.length << endl;
	out << "Диаметр: " << pipe.diam << endl;
	out << "Ремонт: " << pipe.repair << endl;
	return out;
}
istream& operator >> (istream& in, Pipe& pipe)
{
	checking(pipe.length,"Введите длину: ", 0, 200);
	checking(pipe.diam,"Введите диаметр: ", 0, 200);
	checking(pipe.repair,"Ремонт: ", 0, 1);
	return in;
}
//void savePIPE_into_file(ofstream& fout, const Pipe& pipe)
//{//	fout << pipe.id << ' ' << pipe.length << ' ' << pipe.diam << ' ' << pipe.repair;
//}

//Pipe loadPipe_from_file(ifstream& fin)
//{
//	Pipe pipe;
//	fin >> pipe.id >> pipe.length >> pipe.diam >> pipe.repair;
//	return pipe;
//}


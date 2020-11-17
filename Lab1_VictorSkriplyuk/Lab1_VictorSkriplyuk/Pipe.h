#pragma once 
#include <iostream>
class Pipe
{
	int id;
public:
	Pipe();
	static int MaxID;
	float length;
	float diam;
	bool repair;
	
	friend std::ostream& operator << (std::ostream& out, const Pipe& pipe);
	friend std::istream& operator >> (std::istream& in, const Pipe& pipe);
	template <typename T>
	friend void checking(T& var, std::string com, int left, int right);
	/*friend void savePIPE_into_file(ofstream& fout, const Pipe& pipe);
	friend Pipe loadPipe_from_file(ifstream& fin);*/
};


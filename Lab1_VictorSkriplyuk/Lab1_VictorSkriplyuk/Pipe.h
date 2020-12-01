#pragma once 
#include <iostream>
#include <fstream>
class Pipe
{
	int id;
public:
	Pipe();
	static int MaxID;
	float length;
	float diam;
	bool repair;
	void editing_pipe();
	int GetId();
	
	friend std::ostream& operator << (std::ostream& out, const Pipe& pipe);
	friend std::istream& operator >> (std::istream& in, Pipe& pipe);
	friend std::ofstream& operator << (std::ofstream& fout, const Pipe& pipe);
	friend std::ifstream& operator >> (std::ifstream& fin, Pipe& pipe);
	
};


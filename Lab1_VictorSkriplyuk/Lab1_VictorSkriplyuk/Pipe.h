#pragma once 
#include <iostream>
#include <fstream>
class Pipe
{
	
	int id;
	static unsigned int MaxID;
	float length;
	float diam;
	bool repair;
public:
	Pipe();
	void editing_pipe();
	int GetId();
	static unsigned int GetMaxID();
	bool GetRepair();
	
	friend std::ostream& operator << (std::ostream& out, const Pipe& pipe);
	friend std::istream& operator >> (std::istream& in, Pipe& pipe);
	friend std::ofstream& operator << (std::ofstream& fout, const Pipe& pipe);
	friend std::ifstream& operator >> (std::ifstream& fin, Pipe& pipe);
	
};


#pragma once
#include <iostream>
#include <fstream>
class CS
{
	int id;
public:
	CS();
	static int MaxID;
	std::string name;
	int amount;
	int amount_work;
	float perfomance;

	friend std::ostream& operator << (std::ostream & out, const CS & cs);
	friend std::istream& operator >> (std::istream & in, CS & cs);
	friend std::ofstream& operator << (std::ofstream& fout, const CS& cs);
	friend std::ifstream& operator >> (std::ifstream& fin, CS& cs);
};


#pragma once
#include <iostream>
#include <fstream>
class CS
{
	static unsigned int MaxID;
	int id;
	int amount;
	int amount_work;
	float perfomance;
	std::string name;

public:
	CS();
	void editing_cs();
	int GetId();
	static unsigned int GetMaxID();
	int Get_amount();
	int Get_amount_work();
	std::string Get_Name();
	


	friend std::ostream& operator << (std::ostream & out, const CS & cs);
	friend std::istream& operator >> (std::istream & in, CS & cs);
	friend std::ofstream& operator << (std::ofstream& fout, const CS& cs);
	friend std::ifstream& operator >> (std::ifstream& fin, CS& cs);
};


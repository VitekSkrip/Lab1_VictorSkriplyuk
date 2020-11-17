#pragma once 
#include <iostream>
class Pipe
{
	int id;
	
public:
	Pipe();
	float length;
	float diam;
	bool repair;

	friend std::ostream& operator << (std::ostream& out, const Pipe& pipe);
	friend std::istream& operator >> (std::istream& in, const Pipe& pipe);
};


#pragma once 
#include <iostream>
#include <fstream>
class Pipe
{
	int id;
	static unsigned int MaxID;
	bool repair;
	float length;
	float diam;
public:
	Pipe();
	void editing_pipe();
	int id_cs_in;
	int id_cs_out;
	int GetId();
	int GetId_CS_In();
	int GetId_CS_Out();
	void SetId_CS_Out(int id_cs_out);
	void SetId_CS_In(int id_cs_in);
	void in_Pipe_out(int cs_out,int cs_in);
	static unsigned int GetMaxID();
	bool GetRepair();
	int GetCapacity() const;
	int GetWeight() const;
	
	friend std::ostream& operator << (std::ostream& out, const Pipe& pipe);
	friend std::istream& operator >> (std::istream& in, Pipe& pipe);
	friend std::ofstream& operator << (std::ofstream& fout, const Pipe& pipe);
	friend std::ifstream& operator >> (std::ifstream& fin, Pipe& pipe);
	
};


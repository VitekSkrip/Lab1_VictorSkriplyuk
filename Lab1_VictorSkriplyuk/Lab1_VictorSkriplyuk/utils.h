#pragma once
#include <iostream>

//template <typename T>
//bool IsCorrect(T& var, int left, int right)
//{
//	return var >= left && var <= right;
//}

template <typename T>
void checking(T& var, std::string com, int left, int right)
{
	do
	{
		std::cin.clear();
		std::cin.ignore(10000, '\n');
		std::cout << com;
		std::cin >> var;
	} while (std::cin.fail() || var < left || var > right);
}

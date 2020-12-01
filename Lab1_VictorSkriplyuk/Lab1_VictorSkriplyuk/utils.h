#pragma once
#include <iostream>
#include <string>

template <typename T>
bool IsCorrect(T var, T left, T right)
{
	return var >= left && var <= right;
}

template <typename T>
T checking(T left, T right, std::string message)
{
	T var;
	while ((std::cin >> var).fail() || !IsCorrect(var, left, right))
	{
		std::cin.clear();
		std::cin.ignore(1000, '\n');
		std::cout << message;
	} 
	return var;
}

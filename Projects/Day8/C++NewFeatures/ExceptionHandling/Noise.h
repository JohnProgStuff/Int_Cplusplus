#pragma once
#include <string>
#include <iostream>


class Noise {
private:
	std::string _soundMake;
public:
	Noise(std::string sim) : _soundMake{ sim }
	{
		std::cout << "Constructing noise " << _soundMake << std::endl;
	}
	~Noise()
	{
		std::cout << "Destructing noise " << _soundMake << std::endl;
	}
};
#pragma once
#include "OutputManager.h"
#include "SmartPtr.h"

class ConsoleOutputManager
	: public OutputManager<SmartPtr<StorageDevice>>
{
public:
	ConsoleOutputManager() {}
	~ConsoleOutputManager() {}
	void operator<<(SmartPtr<StorageDevice>& obj) const;
};

void ConsoleOutputManager::operator<<(SmartPtr<StorageDevice>& obj) const
{
	std::cout << "Nomination:\t" << obj->GetNomination() << std::endl;
	std::cout << "Manufacturer:\t" << obj->GetManufacturer() << std::endl;
	std::cout << "Model:\t\t" << obj->GetModel() << std::endl;
	std::cout << "Volume:\t\t" << obj->GetVolume() << " GB" << std::endl;
	std::cout << obj->WhatSpeed() << ":\t" << obj->GetSpeed() << ' ' << obj->WhatSpeedMetering() << std::endl << std::endl;
}
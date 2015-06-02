#pragma once
#include <iostream>
#include <fstream>
#include "DataManager.h"
using namespace std;

#define ENUM_USB "USB"
#define ENUM_HDD "Hard Drive Disk"
#define ENUM_DVD "Digital Video Disk"

class StorageDevice
{
protected:
	char *Manufacturer;
	char *Model;
	char *Nomination;
	unsigned int Volume;
public:
	//virtual void Edit() = 0;
	StorageDevice(const char* Manufact, const char* model,
		const char* nomination, const unsigned volume);
	virtual ~StorageDevice()
	{
	}

	virtual const char *WhatSpeed() const = 0;
	virtual const char *WhatSpeedMetering() const = 0;
	virtual unsigned int GetSpeed() const = 0;
	virtual void SetSpeed(const unsigned int) = 0;
	char *GetManufacturer() const { return Manufacturer; }
	void SetManufacturer(const char* str);
	char *GetModel() const { return Model; }
	void SetModel(const char *str);
	char *GetNomination() const { return Nomination; }
	unsigned int GetVolume() const { return Volume; }
	void SetVolume(const unsigned int);
};

typedef class UniversalSerialBus : public StorageDevice
{
protected:
	unsigned int usb_speed;
public:
	const char *WhatSpeed() const { return "Usb speed"; }
	const char *WhatSpeedMetering() const { return "MB/s"; }
	unsigned int GetSpeed() const { return usb_speed; }
	void SetSpeed(const unsigned int speed) { usb_speed = speed; }
	UniversalSerialBus();
	UniversalSerialBus(const char* Manufact, const char* model,
		const unsigned volume, const unsigned speed);
	~UniversalSerialBus();
} USB;

typedef class HardDriveDisk : public StorageDevice
{
protected:
	unsigned int spindel_speed;
public:
	const char *WhatSpeed() const { return "Spindel speed"; }
	const char *WhatSpeedMetering() const { return "rpm"; }
	unsigned int GetSpeed() const { return spindel_speed; }
	void SetSpeed(const unsigned int speed) { spindel_speed = speed; }
	HardDriveDisk();
	HardDriveDisk(const char* Manufact, const char* model,
		const unsigned volume, const unsigned speed);
	~HardDriveDisk();
} HDD;

typedef class DigitalVideoDisk : public StorageDevice
{
protected:
	unsigned int write_speed;
public:
	const char *WhatSpeed() const { return "Write speed"; }
	const char *WhatSpeedMetering() const { return "MB/s"; }
	unsigned int GetSpeed() const { return write_speed; }
	void SetSpeed(const unsigned int speed) { write_speed = speed; }
	DigitalVideoDisk();
	DigitalVideoDisk(const char* Manufact, const char* model,
		const unsigned volume, const unsigned speed);
	~DigitalVideoDisk();
} DVD;

#pragma region StorageDevice

StorageDevice::StorageDevice(const char* manufact, const char* model,
	const char* nomination, const unsigned volume) : Manufacturer(new char[strlen(manufact) + 1]),
	Model(new char[strlen(model) + 1]),
	Nomination(new char[strlen(nomination) + 1]),
	Volume(volume)
{
	strcpy_s(Manufacturer, strlen(manufact) + 1, manufact);
	strcpy_s(Model, strlen(model) + 1, model);
	strcpy_s(Nomination, strlen(nomination) + 1, nomination);
}

void StorageDevice::SetManufacturer(const char *str)
{
	delete[] Manufacturer;
	Manufacturer = new char[strlen(str) + 1];
	strcpy_s(Manufacturer, strlen(str) + 1, str);
}

void StorageDevice::SetModel(const char *str)
{
	delete[] Model;
	Model = new char[strlen(str) + 1];
	strcpy_s(Model, strlen(str) + 1, str);
}

void StorageDevice::SetVolume(const unsigned int volume)
{
	Volume = volume;
}

#pragma endregion

#pragma region UniversalSerialBus

UniversalSerialBus::UniversalSerialBus() : StorageDevice("Unknown", "Unknown", ENUM_USB, 0U), usb_speed(0U)
{
}

UniversalSerialBus::UniversalSerialBus(const char* Manufact, const char* model,
	const unsigned volume, const unsigned speed) : StorageDevice(Manufact, model, ENUM_USB, volume), usb_speed(speed)
{
}

UniversalSerialBus::~UniversalSerialBus()
{
	delete[] Manufacturer;
	delete[] Model;
	delete[] Nomination;
}

#pragma endregion

#pragma region HardDriveDisk

HDD::HardDriveDisk() : StorageDevice("Unknown", "Unknown", ENUM_HDD, 0U), spindel_speed(0U)
{
}

HDD::HardDriveDisk(const char* Manufact, const char* model,
	const unsigned volume, const unsigned speed) : StorageDevice(Manufact, model, ENUM_HDD, volume), spindel_speed(speed)
{
}

HDD::~HardDriveDisk()
{
	delete[] Manufacturer;
	delete[] Model;
	delete[] Nomination;
}

#pragma endregion

#pragma region DigitalVideoDisk

DigitalVideoDisk::DigitalVideoDisk() : StorageDevice("Unknown", "Unknown", ENUM_DVD, 0U), write_speed(0U)
{
}

DigitalVideoDisk::DigitalVideoDisk(const char* Manufact, const char* model,
	const unsigned volume, const unsigned speed) : StorageDevice(Manufact, model, ENUM_DVD, volume), write_speed(speed)
{
}

DVD::~DigitalVideoDisk()
{
	delete[] Manufacturer;
	delete[] Model;
	delete[] Nomination;
}

#pragma endregion
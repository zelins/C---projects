#pragma once
#include "SmartPtr.h"
#include "StorageDevice.h"
#include "Vector.h"
#include "BinaryDataManagerDevice.h"
#include "ConsoleOutputManager.h"
#include <conio.h>

typedef SmartPtr<StorageDevice> StorageDevicePtr;

typedef SmartPtr<BaseDataManager> DataManagerPtr;

class Application
{
private:

	Vector<StorageDevicePtr> repository;
	DataManagerPtr manage;
	OutputManager<StorageDevicePtr> *out;

public:
	Application();
	~Application() { delete out; }
	void Main();
	void ShowMenu() const;
	void AddElem();
	void DeleteElem();
	void ShowRepository() const;
	int input();
};

#pragma region Application

Application::Application()
{
	manage = new BinaryDataManagerDevice("Data.txt", repository);
	out = new ConsoleOutputManager;
	Main();
}

void Application::Main()
{
	while (true)
	{
		ShowMenu();
		int control = input();
		system("cls");
		if (control == 1)
		{
			AddElem();
		}
		else if (control == 2)
		{
			DeleteElem();
		}
		else if (control == 3)
		{
			ShowRepository();
		}
		else if (control == 4)
		{
			manage->Save();
		}
		else if (control == 5)
		{
			manage->Load();
		}
		else
		{
			break;
		}
		cout << "\n\nPress any key to continue";
		_getch();
		system("cls");
	}
}

void Application::ShowMenu() const
{
	cout << "1) Add element to repository\n";
	cout << "2) Delete element from repository\n";
	cout << "3) Show repository\n";
	cout << "4) Save\n";
	cout << "5) Load\n";
	cout << "6) Exit\n";
}

int Application::input()
{
	int command = 0;
	cout << "Enter a command: ";
	cin >> command;
	return command;
}

void Application::ShowRepository() const
{
	unsigned int size = repository.GetSize();
	for (unsigned int i = 0U; i < size; ++i)
	{
		cout << i + 1 << ")\n";
		*out << repository[i];
	}
}

void Application::AddElem()
{
	cout << "What type of device storage do you want add?\n\n";
	cout << "1) USB;\n";
	cout << "2) HDD;\n";
	cout << "3) DVD.\n";
	cout << "4) back\n";

	int control = input();
	cin.sync();

	char manuf[100];
	char model[100];
	unsigned int volume = 0U;
	unsigned int speed = 0U;

	switch (control)
	{
	case 1:
		{
			  cout << "Enter the Manufacturer: ";
			  cin.getline(manuf, 100);
			  cin.sync();
			  cout << "Enter the model: ";
			  cin.getline(model, 100);
			  cin.sync();
			  cout << "Enter the volume: ";
			  cin >> volume;
			  cout << "Enter usb speed(MB/s): ";
			  cin >> speed;
			  repository.Add(new USB(manuf, model, volume, speed));
		}
		break;
	case 2:
		{
			  cout << "Enter the Manufacturer: ";
			  cin.getline(manuf, 100);
			  cin.sync();
			  cout << "Enter the model: ";
			  cin.getline(model, 100);
			  cin.sync();
			  cout << "Enter the volume: ";
			  cin >> volume;
			  cout << "Enter spindel speed(rpm): ";
			  cin >> speed;
			  repository.Add(new HDD(manuf, model, volume, speed));
		}
		break;
	case 3:
		{
			  cout << "Enter the Manufacturer: ";
			  cin.getline(manuf, 100);
			  cin.sync();
			  cout << "Enter the model: ";
			  cin.getline(model, 100);
			  cin.sync();
			  cout << "Enter the volume: ";
			  cin >> volume;
			  cout << "Enter write speed(MB/s): ";
			  cin >> speed;
			  repository.Add(new DVD(manuf, model, volume, speed));
		}
		break;
	case 4:
	default:
		break;
	}
}

void Application::DeleteElem()
{
	unsigned int index = 0U;
	cout << "Enter index of the element: ";
	cin >> index;
	repository.Remove(index - 1);
}

#pragma endregion
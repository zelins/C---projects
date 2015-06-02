#pragma once
#include "StorageDevice.h"
#include "Vector.h"
#include "SmartPtr.h"

class BinaryDataManagerDevice : public BaseDataManager
{
	Vector<SmartPtr<StorageDevice>>& repository;
public:
	explicit BinaryDataManagerDevice(Vector<SmartPtr<StorageDevice>>& repos) : repository(repos)
	{
	}
	BinaryDataManagerDevice(const char *path, Vector<SmartPtr<StorageDevice>>& repos) : BaseDataManager(path), repository(repos)
	{
	}
	~BinaryDataManagerDevice() 
	{
	}
	void Save() const;
	void Load();
};

void BinaryDataManagerDevice::Save() const
{
	unsigned int r_size = repository.GetSize();
	ofstream out(FileName, ios::out | ios::trunc | ios::binary);

	if (out)
	{
		out.write((char *)&r_size, sizeof(r_size));

		for (unsigned int i = 0U; i < r_size; ++i)
		{
			unsigned int size = 0U;

			size = strlen(repository[i]->GetNomination()) + 1;
			out.write((char *)&size, sizeof(size));
			out.write(repository[i]->GetNomination(), size);
			////////////////////////////////////////////////////
			size = strlen(repository[i]->GetManufacturer()) + 1;
			out.write((char *)&size, sizeof(size));
			out.write(repository[i]->GetManufacturer(), size);
			////////////////////////////////////////////////////
			size = strlen(repository[i]->GetModel()) + 1;
			out.write((char *)&size, sizeof(size));
			out.write(repository[i]->GetModel(), size);
			////////////////////////////////////////////////////
			unsigned volume = repository[i]->GetVolume();
			out.write((char *)&volume, sizeof(volume));
			////////////////////////////////////////////////////
			unsigned speed = repository[i]->GetSpeed();
			out.write((char *)&speed, sizeof(speed));
		}

		out.close();
	}
}

void BinaryDataManagerDevice::Load()
{
	if (repository.GetSize()) repository.Clear();

	unsigned int r_size = 0U;
	ifstream in(FileName, ios::in | ios::binary);

	if (in)
	{
		in.read((char *)&r_size, sizeof(r_size));

		for (unsigned int i = 0U; i < r_size; ++i)
		{
			unsigned int size = 0U;
			char str[100];
			/////////////////////////////////////
			in.read((char *)&size, sizeof(size));
			in.read(str, size);
			/////////////////////////////////////
			if (!strcmp(str, ENUM_USB))	repository.Add(new USB);
			else if (!strcmp(str, ENUM_DVD)) repository.Add(new DVD);
			else if (!strcmp(str, ENUM_HDD)) repository.Add(new HDD);
			/////////////////////////////////////
			in.read((char *)&size, sizeof(size));
			in.read(str, size);
			repository[i]->SetManufacturer(str);
			/////////////////////////////////////
			in.read((char *)&size, sizeof(size));
			in.read(str, size);
			repository[i]->SetModel(str);
			/////////////////////////////////////
			in.read((char *)&size, sizeof(size));
			repository[i]->SetVolume(size);
			/////////////////////////////////////
			in.read((char *)&size, sizeof(size));
			repository[i]->SetSpeed(size);
		}

		in.close();
	}
}
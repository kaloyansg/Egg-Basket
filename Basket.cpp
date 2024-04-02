#include "Basket.h"
#include <iostream>
#pragma warning (disable : 4996)

Basket::Basket(const char* name) : name(nullptr), eggs(nullptr), size(0), capacity(0)
{
	this->name = new (std::nothrow) char[strlen(name) + 1];
	if (this->name)
		strcpy(this->name, name);
	eggs = new (std::nothrow) Egg[2];
	if (eggs)
		capacity = 2;
}

Basket::~Basket()
{
	delete[] name;
	name = nullptr;
	delete[] eggs;
	eggs = nullptr;
}

void Basket::resize()
{
	if (size < capacity)
		return;

	Egg* tempEggs = new (std::nothrow) Egg[capacity * 2];
	if (!tempEggs)
		return;
	for (size_t i = 0; i < size; ++i)
	{
		tempEggs[i] = eggs[i];
	}
	delete[] this->eggs;
	eggs = tempEggs;
	capacity *= 2;
}

void Basket::add(const Egg& egg)
{
	resize();
	if (!eggs)
		return;
	eggs[size] = egg;
	++size;
}

void Basket::remove(unsigned id)
{
	size_t i;
	for (i = 0; i < size; ++i)
	{
		if (eggs[i].getId() == id)
			break;
	}

	--size;

	for (i; i < size; ++i)
	{
		eggs[i] = eggs[i + 1];
	}
}

const char* Basket::getName() const
{
	return name;
}

size_t Basket::getSize() const
{
	return size;
}

const Egg& Basket::operator[](size_t index) const
{
	if (index >= size)
		throw "Invalid index";

	return eggs[index];
}

Egg& Basket::operator[](size_t index)
{
	if (index >= size)
		throw "Invalid index";

	return eggs[index];
}

void Basket::saveAsBinary(const char* fileName) const
{
	std::ofstream file(fileName, std::ios::binary);
	if (!file)
		return;
	size_t nameSize = strlen(name) + 1;
	file.write(reinterpret_cast<const char*>(&nameSize), sizeof(nameSize));
	file.write(name, nameSize);
	for (size_t i = 0; i < size; ++i)
	{
		eggs[i].saveAsBinary(file);
	}
	file.close();
}

void Basket::getFromBinary(const char* fileName)
{
	std::ifstream file(fileName, std::ios::binary);
	if (!file)
		return;

	size_t nameSize = 0;
	file.read(reinterpret_cast<char*>(&nameSize), sizeof(nameSize));
	if (!file)
	{
		file.close();
		return;
	}
	char* tempName = nullptr;
	tempName = new (std::nothrow) char[nameSize];
	file.read(tempName, nameSize);
	if (!file)
	{
		file.close();
		return;
	}
	if (tempName)
	{
		delete[] name;
		name = tempName;
	}
	Egg currEgg;
	currEgg.getFromBinary(file);
	while (file)
	{
		this->add(currEgg);
		currEgg.getFromBinary(file);
	}

	file.close();
}

#include "Egg.h"
#include <iostream>
#pragma warning (disable : 4996)

unsigned Egg::idRecord = 0;

Egg::Egg() : name(nullptr), size(0)
{
	this->setName("Egg");
	id = idRecord;
	++idRecord;
}

Egg::Egg(const char* name, size_t size) : name(nullptr)
{
	this->setName(name);
	this->setSize(size);
	id = idRecord;
	++idRecord;
}

Egg::Egg(const Egg& other) : name(nullptr)
{
	this->setName(other.name);
	this->setSize(other.size);
	id = idRecord;
	++idRecord;
}

Egg& Egg::operator=(const Egg& other)
{
	if (this == &other)
		return *this;

	char* tempName = new (std::nothrow) char[strlen(other.name) + 1];
	if (!tempName)
		return *this;
	strcpy(tempName, other.name);
	delete[] this->name;
	this->name = tempName;
	this->size = other.size;

	return *this;
}

Egg::~Egg()
{
	delete[] name;
}

const char* Egg::getName() const
{
	return name;
}

size_t Egg::getSize() const
{
	return size;
}

unsigned Egg::getId() const
{
	return id;
}

void Egg::setName(const char* name)
{
	if (!name || this->name==name)
		return;

	char* tempName = new (std::nothrow) char[strlen(name) + 1];
	if (!tempName)
		return;
	strcpy(tempName, name);
	delete[] this->name;
	this->name = tempName;
}

void Egg::setSize(size_t size)
{
	this->size = size;
}

void Egg::saveAsBinary(std::ofstream& file) const
{
	size_t nameSize = strlen(name) + 1;
	file.write(reinterpret_cast<const char*>(&nameSize), sizeof(nameSize));
	file.write(name, nameSize);
	file.write(reinterpret_cast<const char*>(this), sizeof(Egg));
}

void Egg::getFromBinary(std::ifstream& file)
{
	size_t nameSize = 0;
	file.read(reinterpret_cast<char*>(&nameSize), sizeof(nameSize));
	if (!file)
		return;
	char* tempName = nullptr;
	tempName = new (std::nothrow) char[nameSize];
	file.read(tempName, nameSize);
	if (!file)
		return;
	file.read(reinterpret_cast<char*>(this), sizeof(Egg));
	this->name = tempName;
	id = idRecord;
	++idRecord;
}

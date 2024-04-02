#pragma once
#include "Egg.h"

class Basket
{
public:
	Basket(const char*);
	Basket(const Basket&) = delete;
	Basket& operator=(const Basket&) = delete;
	~Basket();

	void resize();
	void add(const Egg&);
	void remove(unsigned);
	const char* getName()const;
	size_t getSize()const;

	const Egg& operator[](size_t) const;
	Egg& operator[](size_t);

	void saveAsBinary(const char*)const;
	void getFromBinary(const char*);

private:
	char* name;
	Egg* eggs;
	size_t size;
	size_t capacity;
};
#pragma once
#include <fstream>
class Egg
{
public:
	Egg();
	Egg(const char*, size_t);
	Egg(int);
	Egg(const Egg&);
	Egg& operator=(const Egg&);
	~Egg();

	const char* getName()const;
	size_t getSize()const;
	unsigned getId()const;
	void setName(const char*);
	void setSize(size_t);

	void saveAsBinary(std::ofstream&)const;
	void getFromBinary(std::ifstream&);

private:
	char* name;
	size_t size;
	unsigned id;

	static unsigned idRecord;
};
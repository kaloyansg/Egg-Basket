#include <iostream>
#include <fstream>
#include "Egg.h"
#include "Basket.h"
#pragma warning (disable:4996)

void report(const Basket& basket)
{
	char* fileName = new char[12 + strlen(basket.getName())];
	strcpy(fileName, "reprt_");
	strcat(fileName, basket.getName());
	strcat(fileName, ".txt");

	std::ofstream file(fileName);
	file << basket.getName() << ":" << '\n';
	size_t size = basket.getSize();
	for (size_t i = 0; i < size; ++i)
	{
		file << basket[i].getName() << " - " << basket[i].getSize() << '\n';
	}
	file.close();
}

int main()
{
	Egg o("ostrich", 6);
	Egg c("chiken", 3);
	Egg d("dinosaur", 10);

	Basket basket("Stavri");
	basket.add(o);
	basket.add(c);
	basket.add(d);

	basket.saveAsBinary("basket.dat");

	Basket b2("");
	b2.getFromBinary("basket.dat");
	size_t size = b2.getSize();
	std::cout << b2.getName() << " - " << size << ": \n";
	for (size_t i = 0; i < size; ++i)
	{
		std::cout << b2[i].getName() << " ";
	}

	report(b2);
}

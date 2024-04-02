#include <iostream>
#include "Egg.h"
#include "Basket.h"

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
}
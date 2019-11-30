#include "DGV.h"
#include "View.h"
#include <algorithm>

DGV::DGV()
{
	
}

DGV::~DGV()
{
	//todo libertar memoria dos vetores

	int pilotVectorSize = pilotNames.size();

	if (pilotVectorSize > 0)
		for (int i = pilotVectorSize; i >= 0; i--)
			delete pilotNames[i];

	pilotNames.clear();


	int carVectorSize = carNames.size();

	if (carVectorSize > 0)
		for(int i = carVectorSize - 1; i >= 0; i--)
			delete carNames[i];

	carNames.clear();
	
	
}

bool DGV::addCar(const Car newCar)
{
	carNames.push_back(new Car(newCar));
	Car* tmpCar = carNames.back();

	
	if(tmpCar==newCar)
	{
		return true;
	}
	return false;
}


bool DGV::addPilot(const Pilot newPilot)
{
	return false;
}

void DGV::printPosition()
{
	for (int i = 0; i < static_cast<int>(carNames.size()); i++)
		std::cout << *carNames[i] << std::endl;
}

bool DGV::sortFunc(Car *lhs, Car *rhs)
{
	return lhs->getPosition() > rhs->getPosition();
}

void DGV::sortCarsByPosition()
{
	printPosition();
	std::vector<Car*> vectorCopy = carNames;

	std::sort(vectorCopy.begin(),vectorCopy.end(), sortFunc);
	View::printMessage("Vector Sorted.", View::SuccessTypeMessage);
	
	carNames = vectorCopy;
	printPosition();
}
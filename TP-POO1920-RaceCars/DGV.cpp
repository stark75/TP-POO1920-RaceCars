#include "DGV.h"
#include "View.h"
#include <algorithm>

DGV::DGV()
{
	
}

DGV::~DGV()
{
	//todo libertar memoria dos vetores

	int pilotVectorSize = pilotList.size();

	if (pilotVectorSize > 0)
		for (int i = pilotVectorSize - 1; i >= 0; i--)
			delete pilotList[i];

	pilotList.clear();


	int carVectorSize = carList.size();

	if (carVectorSize > 0)
		for(int i = carVectorSize - 1; i >= 0; i--)
			delete carList[i];

	carList.clear();
	
	
}

bool DGV::addCar(const Car newCar)
{
	carList.push_back(new Car(newCar));
	return true;
}


bool DGV::addPilot(const Pilot newPilot)
{
	pilotList.push_back(new Pilot(newPilot));
	return true;
}

void DGV::printCars()
{
	int vectorSize = carList.size();
	for (int i = 0; i < vectorSize; i++)
		std::cout << *carList[i] << std::endl;
}

void DGV::printPilots()
{
	int vectorSize = pilotList.size();
	for (int i = 0; i < vectorSize; i++)
		std::cout << *pilotList[i] << std::endl;
}

Car* DGV::getCarById(char wantedID)
{
	int vectorSize = carList.size();
	for(int i = 0; i < vectorSize; i++)
	{
		char tmpChar=carList[i]->getID();
		if (tmpChar == wantedID)
			return carList[i];
	}
	return nullptr;
}

Pilot* DGV::getPilotByName(std::string wantedName)
{
	int vectorSize = pilotList.size();
	for(int i = 0; i < vectorSize; i++)
	{
		std::string tmpString = pilotList[i]->getName();
		if (tmpString == wantedName)
			return pilotList[i];
	}
	return nullptr;
}

bool DGV::attach(char id, std::string name)
{
	Car*   tmpCar   = getCarById(id);
	Pilot* tmpPilot = getPilotByName(name);

	if(tmpCar!=nullptr && tmpPilot!=nullptr)
	{
		if (tmpCar->getDriver() != nullptr)
			return false;
		if (tmpPilot->getCurrentCar() != nullptr)
			return false;
		if (!tmpCar->attach(tmpPilot))
			return false;
		if(!tmpPilot->attach(tmpCar))
		{
			tmpCar->detach();
			return false;
		}
		return true;
	}
	return false;
}

bool DGV::detach(char id)
{
	Car* tmpCar = getCarById(id);

	if (tmpCar != nullptr)
	{
		Pilot* tmpPilot = tmpCar->getDriver();
		if (tmpPilot == nullptr)
		{
			if(tmpPilot->detach())
			{
				return tmpCar->detach();
			}
		}
	}
	return false;
}


bool DGV::sortFunc(Car *lhs, Car *rhs)
{
	return lhs->getPosition() > rhs->getPosition();
}

void DGV::sortCarsByPosition()
{
	printCars();
	std::vector<Car*> vectorCopy = carList;

	std::sort(vectorCopy.begin(),vectorCopy.end(), sortFunc);
	View::printMessage("Vector Sorted.", View::SuccessTypeMessage);
	
	carList = vectorCopy;
	printCars();
}
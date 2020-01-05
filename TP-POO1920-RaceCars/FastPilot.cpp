#include "FastPilot.h"
#include "Car.h"
#include "Racetrack.h"
#include <cstdlib>
#include <ctime>

FastPilot::FastPilot(const std::string& newName) : Pilot(newName)
{
}

FastPilot::FastPilot(const Pilot& src) : Pilot(src)
{
}

bool FastPilot::generatePanicAttack()
{
	std::srand(static_cast<unsigned>(time(0)));

	int num = (rand() % 10) + 1;

	std::string tmpString = "O piloto rapido ";
	tmpString += getName();
	tmpString += " gerou o numero ";
	tmpString += std::to_string(num);
	tmpString += "para gerar um ataque de panico. ";
	if(num == 7)
	{
		tmpString += "O piloto teve um ataque de panico.";
		setLog(tmpString);
		return true;
	}
	tmpString += "O piloto nao teve nenhum ataque de panico.";
	setLog(tmpString);
	return false;
}

std::string FastPilot::getAsString() const
{
	std::string tmpString;

	tmpString += "[Fast Pilot ";
	tmpString += getName();
	tmpString += " | Carro: ";

	Car* tmpCar = getCurrentCar();

	if (tmpCar != nullptr)
	{
		tmpString += "(";
		std::string carID = std::string(1, tmpCar->getID());
		tmpString += carID;
		tmpString += ") - ";
		tmpString += tmpCar->getBrand();
		tmpString += " ";
		tmpString += tmpCar->getModel();
	}
	else
	{
		tmpString += "Nenhum";
	}
	tmpString += "]";

	return tmpString;
}

std::string FastPilot::getTypeAsString() const
{
	return "rapido";
}

bool FastPilot::movement(Racetrack* r)
{
	int tmpTime = r->getTime();
	Car* c = getCurrentCar();

	double currentEnergy = c->getEnergy();
	double maxEnergy = c->getMaxEnergy();
	
	
	double energyRatio = currentEnergy / maxEnergy;

	if (!getStopOrder())
	{
		if (energyRatio > .5)
		{
			if (!c->pressAccelerate(2))
			{
				c->pressBrake(-2);
			}
		}
		else
		{
			if (c->getAccelerationPedal() > 0)
				c->pressBrake(-2);
			else
			{
				if (tmpTime % 3 == 0)
				{
					c->pressAccelerate(1);
				}
			}
		}
	}
	else
	{
		c->resetPedals();
		if (c->getSpeed() > 0)
			c->pressBrake();
	}

	if (tmpTime % 10 == 0)
	{
		if (generatePanicAttack())
		{
			c->turnOnEmergencySignal();
		}
	}
	
	return true;
}

void FastPilot::reset()
{
	setStop(false);
	setLog("");
}

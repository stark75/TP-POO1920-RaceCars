#include "Championship.h"

Championship::Championship(Racetrack* location, std::vector<Car* > newParticipants):participants(newParticipants)
{
	int vectorSize = newParticipants.size();
	
	for (int i = 0; i < vectorSize; i++)
	{
		location->addCarToGarage(newParticipants[i]);
	}

	races.push_back(location);
	
}
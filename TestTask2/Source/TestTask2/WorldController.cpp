

#include "WorldController.h"



void AWorldController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
}

void AWorldController::SpawnCreatureNest(int index)
{
	if(Spawn.IsBound())
	{
		Spawn.Broadcast(index);
	}
}




	


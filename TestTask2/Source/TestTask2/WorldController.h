#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "WorldController.generated.h"


UCLASS()
class TESTTASK2_API AWorldController : public APlayerController
{
	GENERATED_BODY()

	DECLARE_EVENT_OneParam(ACreatureNest, FSpawn, int);

	virtual void SetupInputComponent() override;

	

public:

	UFUNCTION(BlueprintCallable)
	void SpawnCreatureNest(int index);
	
	FSpawn Spawn;
};

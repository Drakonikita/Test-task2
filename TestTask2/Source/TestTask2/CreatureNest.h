
#pragma once

#include "CoreMinimal.h"
#include "Creature1.h"
#include "WorldController.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/Actor.h"
#include "CreatureNest.generated.h"

UCLASS()
class TESTTASK2_API ACreatureNest : public AActor
{
	GENERATED_BODY()

		
public:	

	ACreatureNest();

	UFUNCTION()
	void SpawnedCreatureDespawned();

	UFUNCTION()
	void SpawnCreature(int index);

	
protected:

	virtual void BeginPlay() override;

	UPROPERTY()
	AWorldController* WorldController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* BodyMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UArrowComponent* CreatureSpawnPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TSubclassOf<ACreature1> SpawnCreatureClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (MakeEditWidget = true))
	AActor* destinationPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	int nestIndex;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	UParticleSystemComponent* CreatureSpawnEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	UAudioComponent* CantSpawnSound;
	
private:

	bool bHasSpawnedCreature = false;

};

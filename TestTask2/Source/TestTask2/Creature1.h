#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Creature1.generated.h"

UCLASS()
class TESTTASK2_API ACreature1 : public ACharacter
{
	GENERATED_BODY()

public:
	ACreature1();

	virtual FVector GetVelocity() const override;

	void SetDestination(AActor* newDestination);


protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UParticleSystemComponent* SpawnEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UParticleSystemComponent* DisappearEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UAudioComponent* SpawnSound;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UAudioComponent* DisappearSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MoveSpeed = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float TurnSpeed = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float timeToMoveForward = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float timeToMoveBackward = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float timeToStop = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	FVector MovePosition;

	void ChangeDestination();

	void Disappear();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float DestinationAccurency = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug")
	bool showDebug = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float InterpolationKey = 0.2f;

public:
	virtual void Tick(float DeltaTime) override;

private:
	AActor* DestinationPoint;

	void Die();

	FVector StartPoint;
	FVector CurrentMoveDirection;
	FTimerHandle moveForwardTimer;
	FTimerHandle moveBackwardTimer;
	FTimerHandle stopTimer;

	bool bDisappearFlag;
};



#include "Creature1.h"

#include "CreatureNest.h"
#include "Components/AudioComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Particles/ParticleSystemComponent.h"

ACreature1::ACreature1()
{
	PrimaryActorTick.bCanEverTick = true;
	
	SpawnEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("SpawnEffect"));
	SpawnEffect->SetupAttachment(RootComponent);
	SpawnEffect->SetAutoActivate(false);
	
	DisappearEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("DisappearEffect"));
	DisappearEffect->SetupAttachment(RootComponent);
	DisappearEffect->SetAutoActivate(false);
	
	SpawnSound = CreateDefaultSubobject<UAudioComponent>(TEXT("SpawnSound"));
	SpawnSound->SetupAttachment(RootComponent);	
	SpawnSound->SetAutoActivate(false);
	
	DisappearSound = CreateDefaultSubobject<UAudioComponent>(TEXT("DisappearSound"));	
	DisappearSound->SetupAttachment(RootComponent);
	DisappearSound->SetAutoActivate(false);	
}

FVector ACreature1::GetVelocity() const
{
	return MovePosition;
}

void ACreature1::SetDestination(AActor* newDestination)
{
	DestinationPoint = newDestination;	
}

void ACreature1::BeginPlay()
{
	Super::BeginPlay();

	if(SpawnEffect)
	{
		SpawnEffect->ActivateSystem();
	}
	if(SpawnSound)
	{
		SpawnSound->Play();
	}
	
	StartPoint = GetActorLocation();

	CurrentMoveDirection = DestinationPoint->GetActorLocation();

	FRotator CurrentRotation = GetActorRotation();
	FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), CurrentMoveDirection);

	TargetRotation.Pitch = CurrentRotation.Pitch;
	TargetRotation.Roll = CurrentRotation.Roll;

	SetActorRotation(FMath::Lerp(CurrentRotation, TargetRotation, TurnSpeed));

	if(timeToMoveBackward > 0.0f && timeToStop == 0.0f && timeToMoveForward > 0.0f)
	{
		GetWorldTimerManager().SetTimer(moveBackwardTimer,
			this,
			&ACreature1::ChangeDestination,
			timeToMoveBackward+timeToMoveForward,
			true,
			timeToMoveForward);
		GetWorldTimerManager().SetTimer(moveForwardTimer,
			this,
			&ACreature1::ChangeDestination,
			timeToMoveBackward+timeToMoveForward,
			true,
			timeToMoveForward+timeToMoveBackward);
		
	}
	else if(timeToStop > 0.0f && timeToMoveBackward == 0.0f && timeToMoveForward > 0.0f)
	{
		GetWorldTimerManager().SetTimer(stopTimer,
			this,
			&ACreature1::ChangeDestination,
			timeToStop+timeToMoveForward,
			true,
			timeToMoveForward);
		GetWorldTimerManager().SetTimer(moveForwardTimer,
			this,
			&ACreature1::ChangeDestination,
			timeToStop+timeToMoveForward,
			true,
			timeToMoveForward+timeToStop);
	}
}

void ACreature1::ChangeDestination()
{
	if(CurrentMoveDirection == DestinationPoint->GetActorLocation() && timeToMoveBackward > 0.0f)
	{
		CurrentMoveDirection = StartPoint;
	}
	else if(CurrentMoveDirection == DestinationPoint->GetActorLocation() && timeToStop > 0.0f)
	{
		CurrentMoveDirection = GetActorLocation();
	}
	else
	{
		CurrentMoveDirection = DestinationPoint->GetActorLocation();
	}	
}

void ACreature1::Disappear()
{
	
	
	FTimerHandle destroyTimer;
	GetWorldTimerManager().SetTimer(destroyTimer, this,  &ACreature1::Die, 5.0f, false);
	//Destroy();
}

void ACreature1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// movement
	
	FVector CurrentLocation = GetActorLocation();
	if(FVector::Distance(CurrentLocation, CurrentMoveDirection) > DestinationAccurency)
	{
		FVector ForwardVector = GetActorForwardVector();
		MovePosition = FMath::Lerp(CurrentLocation, CurrentLocation + MoveSpeed * ForwardVector, InterpolationKey);
		SetActorLocation(MovePosition, true);		

	// rotation
	
		FRotator CurrentRotation = GetActorRotation();
		FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(CurrentLocation, CurrentMoveDirection);

		TargetRotation.Pitch = CurrentRotation.Pitch;
		TargetRotation.Roll = CurrentRotation.Roll;

		SetActorRotation(FMath::Lerp(CurrentRotation, TargetRotation, TurnSpeed));
	}
	if(showDebug)
	{
		UE_LOG(LogTemp, Warning, TEXT("Distance %f"), FVector::Distance(CurrentLocation, DestinationPoint->GetActorLocation()));
	}
	
	if(FVector::Distance(CurrentLocation, DestinationPoint->GetActorLocation()) <= DestinationAccurency)
	{
		if(DisappearEffect)
		{
			DisappearEffect->ActivateSystem();
		}
		if(DisappearSound)
		{
			DisappearSound->Play();
		}
		Disappear();
	}
}

void ACreature1::Die()
{
	ACreatureNest* nest = Cast<ACreatureNest>(GetOwner());
	if(nest)
	{
		nest->SpawnedCreatureDespawned();
	}
	
	Destroy();
}


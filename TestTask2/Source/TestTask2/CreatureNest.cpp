

#include "CreatureNest.h"

#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"


ACreatureNest::ACreatureNest()
{
	PrimaryActorTick.bCanEverTick = false;
	
	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = SceneComponent;

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
	BodyMesh->SetupAttachment(SceneComponent);

	CreatureSpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("SpawnPoint"));
	CreatureSpawnPoint->SetupAttachment(SceneComponent);

	CreatureSpawnEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("SpawnEffect"));
	CreatureSpawnEffect->SetupAttachment(SceneComponent);
	CreatureSpawnEffect->SetAutoActivate(false);

	CantSpawnSound = CreateDefaultSubobject<UAudioComponent>(TEXT("CantSpawnSound"));
	CantSpawnSound->SetupAttachment(SceneComponent);
	CantSpawnSound->SetAutoActivate(false);
	
}

void ACreatureNest::SpawnedCreatureDespawned()
{
	bHasSpawnedCreature = false;
}

void ACreatureNest::BeginPlay()
{
	Super::BeginPlay();

	WorldController = Cast<AWorldController>(GetWorld()->GetFirstPlayerController());
	if(WorldController)
	{
		WorldController->Spawn.AddUObject(this, &ACreatureNest::SpawnCreature);
	}
}

void ACreatureNest::SpawnCreature(int index)
{
	if(index != nestIndex)
	{
		return;
	}
	if(bHasSpawnedCreature)
	{
		CantSpawnSound->Play();
		return;
	}

	FTransform spawnTransform(
		CreatureSpawnPoint->GetComponentRotation(),
		CreatureSpawnPoint->GetComponentLocation(),
		FVector(1));

	ACreature1* newCreature = GetWorld()->SpawnActorDeferred<ACreature1>(SpawnCreatureClass,
		spawnTransform,
		this,
		nullptr,
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	
	newCreature->SetDestination(destinationPoint);

	UGameplayStatics::FinishSpawningActor(newCreature, spawnTransform);

	bHasSpawnedCreature = true;
	
}


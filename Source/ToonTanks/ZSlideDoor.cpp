// Fill out your copyright notice in the Description page of Project Settings.


#include "ZSlideDoor.h"
#include "ToonTanks/Pawns/PawnTurret.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UZSlideDoor::UZSlideDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UZSlideDoor::BeginPlay()
{
	Super::BeginPlay();
	
	//Intialize Z variables 
	InitialZ = GetOwner()->GetActorLocation().Z;
	CurrentZ = InitialZ;
	TargetZ += InitialZ;

	//Finds Audio Component Attached
	FindAudioComponent();
}

void UZSlideDoor:: FindAudioComponent()
{
	//Finds Audio Component based on class
	DoorAudio = GetOwner()->FindComponentByClass<UAudioComponent>();
	
	//Protect from null pointer
	if(!DoorAudio) 
	{
		//Debug
		UE_LOG(LogTemp, Error, TEXT("%s does not have an Audio Component"), *GetOwner()->GetName());
		return;
	}
}

// Called every frame
void UZSlideDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GetTargetTurretCount() == 1)
	{
		OpenDoor(DeltaTime);
	}
}

void UZSlideDoor::OpenDoor(float DeltaTime)
{
	//Open Door
	CurrentZ = FMath::Lerp(CurrentZ, TargetZ, OpenSpeed *DeltaTime);
	FVector DoorLocation = GetOwner()->GetActorLocation();
	DoorLocation.Z = CurrentZ;
	GetOwner()->SetActorLocation(DoorLocation);

	//Play Open Door sound 
	if(!DoorAudio) {return;}
	if (!OpenSound)
	{
		DoorAudio->Play();
		OpenSound = true;
	}
}

int32 UZSlideDoor::GetTargetTurretCount() 
{
    TArray<AActor*> TurretActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawnTurret::StaticClass(), TurretActors);
    return TurretActors.Num();
}
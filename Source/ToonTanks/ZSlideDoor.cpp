// Fill out your copyright notice in the Description page of Project Settings.


#include "ZSlideDoor.h"
#include "ToonTanks/Pawns/PawnTurret.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
/*! \brief Constructor
 *
 *
 *  This Function will construct the component based on the default values
 */
UZSlideDoor::UZSlideDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
/*! \brief Game Start
 *
 *
 *  This Function will Begin this components existance
 */
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

/*! \brief Plays audio
 *
 *
 *  This Function will play audio based on its owners audio component
 */
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
/*! \brief Called every frame
 *
 *
 *  This Function will run every frame and it will check if the door has been opened
 *  @param DeltaTime The time between frames
 *  @param TickType
 *  @param ThisTickFunction
 */
void UZSlideDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GetTargetTurretCount() == 1)
	{
		OpenDoor(DeltaTime);
	}
}

/*! \brief Opens the door
 *
 *
 *  This Function will open the door
 *  @param DeltaTime Time Between frames
 */
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

/*! \brief Finds all sentry guns
 *
 *
 *  This Function will Find how many sentry guns are currently in the map and return that number.
 */
int32 UZSlideDoor::GetTargetTurretCount() 
{
    TArray<AActor*> TurretActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawnTurret::StaticClass(), TurretActors);
    return TurretActors.Num();
}
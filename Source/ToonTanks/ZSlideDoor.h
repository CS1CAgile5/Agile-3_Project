// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Components/AudioComponent.h"
#include "ZSlideDoor.generated.h"

class APawnTurret;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOONTANKS_API UZSlideDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UZSlideDoor();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void FindAudioComponent();
	void OpenDoor(float DeltaTime);
	void CloseDoor(float DeltaTime);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	float InitialZ;
	float CurrentZ;

	UPROPERTY(EditAnywhere)
	float TargetZ = -90.f;

	UPROPERTY(EditAnywhere)
	float OpenSpeed = .5f;

	bool OpenSound = false;

	UPROPERTY()
	UAudioComponent* DoorAudio = nullptr;

	int32 GetTargetTurretCount();
};

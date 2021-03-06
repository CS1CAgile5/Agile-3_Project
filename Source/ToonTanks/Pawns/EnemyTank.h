// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnTurret.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "EnemyTank.generated.h"

class APawnTank;

UCLASS()
class TOONTANKS_API AEnemyTank : public APawnTurret
{
	GENERATED_BODY()
public: 
	bool CheckAllDead();

private: 
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void CheckFireCondition() override;

	FTimerHandle FireRateTimerHandle;
	APawnTank* PlayerPawn; 

};

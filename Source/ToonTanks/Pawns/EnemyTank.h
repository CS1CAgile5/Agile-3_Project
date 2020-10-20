// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnTurret.h"
#include "Engine/World.h"
#include "EnemyTank.generated.h"

class APawnTank;

UCLASS()
class TOONTANKS_API AEnemyTank : public APawnTurret
{
	GENERATED_BODY()

private: 
	virtual void BeginPlay() override;
	virtual void CheckFireCondition() override;

	FTimerHandle FireRateTimerHandle;
	APawnTank* PlayerPawn; 

	int32 GetTargetTurretCount();
};

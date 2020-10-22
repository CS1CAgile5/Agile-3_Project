// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyTank.h"
#include "Kismet/GameplayStatics.h"
#include "PawnTank.h"

void AEnemyTank::BeginPlay()
{
	Super::BeginPlay();
	
    GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &AEnemyTank::CheckFireCondition, GetFireRate(), true);

    PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

// Called every frame
void AEnemyTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    if (!PlayerPawn || ReturnDistanceToPlayer() > GetFireRange())
    {
        return;
    }
    RotateTurret(PlayerPawn->GetActorLocation());

    if(CheckAllDead())
        Move();
}

void AEnemyTank::CheckFireCondition() 
{
    // If Player == null || is Dead THEN BAIL!!
    if(!PlayerPawn || !PlayerPawn->GetIsPlayerAlive())
    {
        return;
    }

    // If Player IS in range THEN FIRE!!
    if((ReturnDistanceToPlayer() <= GetFireRange()) && CheckAllDead())
    {
        Fire();
    }
}

bool AEnemyTank::CheckAllDead() 
{
    TArray<AActor*> TurretActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawnTurret::StaticClass(), TurretActors);

    if (TurretActors.Num() == 1)
    {
        return true;
    }
    else
    {
        return false; 
    }
}
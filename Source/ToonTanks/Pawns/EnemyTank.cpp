// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyTank.h"
#include "Kismet/GameplayStatics.h"
#include "PawnTank.h"
/*! \brief Game Start
 *
 *
 *  This Function will Begin this components existance
 */
void AEnemyTank::BeginPlay()
{
	Super::BeginPlay();
	
    GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &AEnemyTank::CheckFireCondition, GetFireRate(), true);

    PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

// Called every frame
/*! \brief Called every frame
 *
 *
 *  This Function will run every frame, it checks if the player is in range of the tank and will rotate the turret if it is.
 */
void AEnemyTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    if (!PlayerPawn || ReturnDistanceToPlayer() > GetFireRange())
    {
        return;
    }
    RotateTurret(PlayerPawn->GetActorLocation());
}

/*! \brief Checks if it can fire
 *
 *
 *  This Function will check if the tank can fire, and if it can, run the code to shoot.
 */
void AEnemyTank::CheckFireCondition() 
{
    // If Player == null || is Dead THEN BAIL!!
    if(!PlayerPawn || !PlayerPawn->GetIsPlayerAlive())
    {
        return;
    }

    // If Player IS in range THEN FIRE!!
    if(CheckAllDead())
    {
        Fire();
    }
}

/*! \brief Gets player status
 *
 *
 *  This Function will return whether the player is alive or dead
 */
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
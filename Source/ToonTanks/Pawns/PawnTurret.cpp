// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTurret.h"
#include "Kismet/GameplayStatics.h"
#include "PawnTank.h"

// Called when the game starts or when spawned
/*! \brief Game Start
 *
 *
 *  This Function will Begin this components existance
 */
void APawnTurret::BeginPlay()
{
	Super::BeginPlay();
	
    GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &APawnTurret::CheckFireCondition, FireRate, true);

    PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

/*! \brief Destructor
 *
 *
 *  This Function will end this components existance
 */
void APawnTurret::HandleDestruction() 
{
    // Call base pawn class HandleDestruction to play effects.
    Super::HandleDestruction();
    Destroy();
}

// Called every frame
/*! \brief Called every frame
 *
 *
 *  This Function will run every frame, it will check if the player is in its range, and rotates its turret to look towards them
 *  @param DeltaTime The time between frames
 */
void APawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (!PlayerPawn || ReturnDistanceToPlayer() > FireRange)
    {
        return;
    }
    
    RotateTurret(PlayerPawn->GetActorLocation());
}

/*! \brief Checks if it can fire
 *
 *
 *  This Function will check if the turret is in range of the player, if so, it will fire
 */
void APawnTurret::CheckFireCondition() 
{
    // If Player == null || is Dead THEN BAIL!!
    if(!PlayerPawn || !PlayerPawn->GetIsPlayerAlive())
    {
        return;
    }

    // If Player IS in range THEN FIRE!!
    if(ReturnDistanceToPlayer() <= FireRange)
    {
        Fire();
    }
}

/*! \brief Gets distance
 *
 *
 *  This Function will return the distance between it and the player
 */
float APawnTurret::ReturnDistanceToPlayer() 
{
    if(!PlayerPawn)
    {
        return 0.0f;
    }

    return FVector::Dist(PlayerPawn->GetActorLocation(), GetActorLocation());
}

/*! \brief Gets FireRate
 *
 *
 *  This Function will return the FireRate of the turret
 */
float APawnTurret::GetFireRate() const
{
    return FireRate;
}

/*! \brief Gets Fire Range
 *
 *
 *  This Function will return the fire range of the turret
 */
float APawnTurret::GetFireRange() const
{
    return FireRange;
}
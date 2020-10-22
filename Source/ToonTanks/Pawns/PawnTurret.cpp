// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTurret.h"
#include "Kismet/GameplayStatics.h"
#include "PawnTank.h"

// Called when the game starts or when spawned
/*! \brief Begins the game
 *
 *
 *  This component will be initialized in this funciton when the game starts.
 */
void APawnTurret::BeginPlay()
{
	Super::BeginPlay();
	
    GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &APawnTurret::CheckFireCondition, FireRate, true);

    PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

/*! \brief Destroys the sentry
 *
 *
 *  This component will Handle the destruction of the sentry gun
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
 *  This component will be called every frame the game is running: It will rotate the turret toward the player if they are in range
 *  @param DeltaTime tracks the time between frames
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

/*! \brief Handle firing
 *
 *
 *  This component will fire the sentry gun at the player if the player is in range
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

/*! \brief Checks for range
 *
 *
 *  This component will return the distance between the turret and the player, so long as the player is alive
 */
float APawnTurret::ReturnDistanceToPlayer() 
{
    if(!PlayerPawn)
    {
        return 0.0f;
    }

    return FVector::Dist(PlayerPawn->GetActorLocation(), GetActorLocation());
}

/*! \brief Gets Firerate
 *
 *
 *  This component will return the fire rate of the turret
 */
float APawnTurret::GetFireRate() const
{
    return FireRate;
}

/*! \brief Gets fire range
 *
 *
 *  This component will return the range of the turret
 */
float APawnTurret::GetFireRange() const
{
    return FireRange;
}

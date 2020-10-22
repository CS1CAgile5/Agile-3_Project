// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnBase.h"
#include "Components/CapsuleComponent.h"
#include "ToonTanks/Pawns/ProjectileBase.h"
#include "ToonTanks/HealthComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
/*! \brief Sets default Values
 *
 *
 *  This component sets all the default values for the pawn
 */
APawnBase::APawnBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(RootComponent);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
}

/*! \brief Rotate the turret
 *
 *
 *  This component allows a turret to rotate based on its current target
 *  @Param LookAtTarget The target that we want to rotate to
 */
void APawnBase::RotateTurret(FVector LookAtTarget) 
{
	// Update TurretMesh rotation to face towards the LookAtTarget passed in from Child Classes
	// TurretMesh->SetWorldRotation()...
	FVector LookAtTargetCleaned = FVector(LookAtTarget.X, LookAtTarget.Y, TurretMesh->GetComponentLocation().Z);
	FVector StartLocation = TurretMesh->GetComponentLocation();

	FRotator TurretRotation = FVector(LookAtTargetCleaned - StartLocation).Rotation();
	TurretMesh->SetWorldRotation(TurretRotation);
}


/*! \brief Fires a projectile
 *
 *
 *  This component will allow a tank/sentry gun to fire a projectile at its target
 */
void APawnBase::Fire() 
{
	// Get ProjectileSpawnPoint && Rotation -> Spawn Projectile class at Location firing towards rotation
	if (ProjectileClass)
	{
		FVector SpawnLocation = ProjectileSpawnPoint->GetComponentLocation();
		FRotator SpawnRotation = ProjectileSpawnPoint->GetComponentRotation();
		AProjectileBase* TempProjectile = GetWorld()->SpawnActor<AProjectileBase>(ProjectileClass, SpawnLocation, SpawnRotation);
		TempProjectile->SetOwner(this);
	}
	
}

/*! \brief Handels Destruction
 *
 *
 *  This component will Handle the destruction of this pawn.
 */
void APawnBase::HandleDestruction() 
{
	// --- Universal Functionality ---
	// Play death effects particle, sound and camera shake

	UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticle, GetActorLocation());
	UGameplayStatics::SpawnSoundAtLocation(this, DeathSound, GetActorLocation());

	// --- Then do Child overrides ---
	// --- PawnTurret - Inform GameMode Turret died -> The Destroy() self.

	// --- PawnTank - Inform GameMode Player died -> Then hide() all components && stop movement input
	// --- PawnEnemy - Infrom GameMode Enemy died -> Destroy() self. 
}



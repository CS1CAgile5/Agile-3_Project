// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

/*! \brief Sets default values
 *
 *
 *  This component will set the default value for its properties
 */
APawnTank::APawnTank()
{
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    SpringArm->SetupAttachment(RootComponent);

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
/*! \brief Begins the game
 *
 *
 *  This component will initialize the player control when the game starts.
 */
void APawnTank::BeginPlay()
{
	Super::BeginPlay();

    PlayerControllerRef = Cast<APlayerController>(GetController());
	
}

/*! \brief Destroys the tank
 *
 *
 *  This component will halde the destruciton of the tank
 */
void APawnTank::HandleDestruction() 
{
    Super::HandleDestruction();
    // Hide Player. TODO - Create new function to handle this
    bIsPlayerAlive = false;

    SetActorHiddenInGame(true);
    SetActorTickEnabled(false);
}

/*! \brief Checks if the player is alive
 *
 *
 *  This component will return whether or not the player is alive
 */
bool APawnTank::GetIsPlayerAlive() 
{
    return bIsPlayerAlive;
}

// Called every frame
/*! \brief Called every frame
 *
 *
 *  This component will run every frame that the game is running: it handles the movment, rotation, and damage taken by the tank
 *  @param DeltaTime Tracks the time between frames
 */
void APawnTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    Rotate();
    Move();

    if (PlayerControllerRef)
    {
        FHitResult TraceHitResult;
        PlayerControllerRef->GetHitResultUnderCursor(ECC_Visibility, false, TraceHitResult);
        FVector HitLocation = TraceHitResult.ImpactPoint;

        RotateTurret(HitLocation);
    }
    
}

// Called to bind functionality to input
/*! \brief Bind functionality to input
 *
 *
 *  This component will bind inputs to certain actions in the game
 *  @param PlayerInputComponent
 */
void APawnTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent->BindAxis("MoveForward", this, &APawnTank::CalculateMoveInput);
    PlayerInputComponent->BindAxis("Turn", this, &APawnTank::CalculateRotateInput);
    PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APawnTank::Fire);
}

/*! \brief Moves the tank
 *
 *
 *  This component will Move the tank forward or backward depending on player input
 *  @param Value how much we want to move the player
 */
void APawnTank::CalculateMoveInput(float Value) 
{
    MoveDirection = FVector(Value * MoveSpeed * GetWorld()->DeltaTimeSeconds, 0, 0);
}

/*! \brief Rotates the turret
 *
 *
 *  This component will rotate the turret depending on player input
 *  @param Value how much we want to move the turret
 */
void APawnTank::CalculateRotateInput(float Value) 
{
    float RotateAmount = Value * RotateSpeed * GetWorld()->DeltaTimeSeconds;
    FRotator Rotation = FRotator(0, RotateAmount, 0);
    RotationDirection = FQuat(Rotation);
}
/*! \brief Move
 *
 *
 *  This component will move the tank as determined in CalculateMoveInput
 */
void APawnTank::Move() 
{
    AddActorLocalOffset(MoveDirection, true);
}

/*! \brief Rotate
 *
 *
 *  This component will Rotate the turret as determined in CalculateRoatateInput
 */
void APawnTank::Rotate() 
{
    AddActorLocalRotation(RotationDirection, true);
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
/*! \brief Constructor
 *
 *
 *  This Function will construct the component based on the default values
 */
APawnTank::APawnTank()
{
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    SpringArm->SetupAttachment(RootComponent);

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
/*! \brief Game Start
 *
 *
 *  This Function will Begin this components existance
 */
void APawnTank::BeginPlay()
{
	Super::BeginPlay();

    PlayerControllerRef = Cast<APlayerController>(GetController());
	
}

/*! \brief Destructor
 *
 *
 *  This Function will end this components existance
 */
void APawnTank::HandleDestruction() 
{
    Super::HandleDestruction();
    // Hide Player. TODO - Create new function to handle this
    bIsPlayerAlive = false;

    SetActorHiddenInGame(true);
    SetActorTickEnabled(false);
}

/*! \brief Get player status
 *
 *
 *  This Function will return whether the player is alive or dead
 */
bool APawnTank::GetIsPlayerAlive() 
{
    return bIsPlayerAlive;
}

// Called every frame
/*! \brief Called every frame
 *
 *
 *  This Function will run every frame, it will move the player, rotate the players turret, and fire the cannon based on the players input
 *  @param DeltaTime The time between frames
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
/*! \brief Bind input functionality
 *
 *
 *  This Function will bind functionality to the players input
 *  @param PlayerInputComponent The keybindings
 */
void APawnTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent->BindAxis("MoveForward", this, &APawnTank::CalculateMoveInput);
    PlayerInputComponent->BindAxis("Turn", this, &APawnTank::CalculateRotateInput);
    PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APawnTank::Fire);
}

/*! \brief Calculates velocity
 *
 *
 *  This Function will calculate the veloctity of the player based on their input
 */
void APawnTank::CalculateMoveInput(float Value) 
{
    MoveDirection = FVector(Value * MoveSpeed * GetWorld()->DeltaTimeSeconds, 0, 0);
}

/*! \brief Calculates rotation
 *
 *
 *  This Function will calculate the rotation speed of the player based on their input
 */
void APawnTank::CalculateRotateInput(float Value) 
{
    float RotateAmount = Value * RotateSpeed * GetWorld()->DeltaTimeSeconds;
    FRotator Rotation = FRotator(0, RotateAmount, 0);
    RotationDirection = FQuat(Rotation);
}

/*! \brief Moves the player
 *
 *
 *  This Function will move the player
 */
void APawnTank::Move() 
{
    AddActorLocalOffset(MoveDirection, true);
}

/*! \brief Rotates the player
 *
 *
 *  This Function will rotate the player as specified in CalculateRoatateInput
 */
void APawnTank::Rotate() 
{
    AddActorLocalRotation(RotationDirection, true);
}

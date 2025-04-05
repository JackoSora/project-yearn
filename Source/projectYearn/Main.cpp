// Fill out your copyright notice in the Description page of Project Settings.

#include "Main.h"
#include "GameFramework/Character.h"

// Sets default values
AMain::AMain()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMain::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		UE_LOG(LogTemp, Warning, TEXT("EnhancedInputComponent Valid"));
		// Bind the move action
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMain::Move);
		UE_LOG(LogTemp, Warning, TEXT("Move Action Bound"));
	} else {
		UE_LOG(LogTemp, Warning, TEXT("EnhancedInputComponent Invalid"));
	}
}

// Called every frame
void AMain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
void AMain::BeginPlay()
{
	Super::BeginPlay();
    
	// Setup Enhanced Input for the player controller
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController Valid"));
		EnableInputMove(PlayerController);
	} else {
		UE_LOG(LogTemp, Warning, TEXT("PlayerController Invalid"));
	}
}

// Called to bind functionality to input


void AMain::EnableInputMove(APlayerController* PlayerController)
{
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
	{
		UE_LOG(LogTemp, Warning, TEXT("AMain::EnableInputMove"));
		Subsystem-> RemoveMappingContext(DefaultMappingContext);
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
		UE_LOG(LogTemp, Warning, TEXT("Mapping Context Added"));
	}
}

void AMain::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

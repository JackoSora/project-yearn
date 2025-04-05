#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Main.generated.h"

UCLASS()
class PROJECTYEARN_API AMain : public ACharacter
{
	GENERATED_BODY()

public:
	AMain();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,   BlueprintReadWrite, Category = "Enahnced Input") 
	class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enhanced Input")
	class UInputAction* MoveAction;

protected:
	void EnableInputMove(class APlayerController* PlayerController);
	
	void Move(const FInputActionValue& value);

public: 
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
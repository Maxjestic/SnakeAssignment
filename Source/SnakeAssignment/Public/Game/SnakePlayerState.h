// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SnakePlayerState.generated.h"

UENUM()
enum class ESnakeControllerType : uint8
{
	Keyboard1	UMETA(DisplayName = "Keyboard 1"),
	Keyboard2	UMETA(DisplayName = "Keyboard 2"),
	AI			UMETA(DisplayName = "AI")
};

/**
 * 
 */
UCLASS()
class SNAKEASSIGNMENT_API ASnakePlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	UFUNCTION()
	FORCEINLINE float GetSnakeSpeed() const { return SnakeSpeed; }

	UFUNCTION( Blueprintcallable )
	FORCEINLINE ESnakeControllerType GetControllerType() const { return ControllerType; }

	UFUNCTION( BlueprintCallable )
	void SetControllerType( const ESnakeControllerType NewControllerType );

	UFUNCTION()
	void IncreaseSnakeSpeed( const float ExtraSpeed );

	UFUNCTION()
	void AppleEaten();

	FORCEINLINE bool IsDead() const { return bIsDead; };
	
	FORCEINLINE int32 AppleScore() const { return ApplesEaten; };

	void Died();

	void StopSnake() const;
	
protected:
	UPROPERTY( EditAnywhere )
	float SnakeSpeed = 500.f;

	int32 ApplesEaten = 0;

	bool bIsDead = false;

	UPROPERTY()
	ESnakeControllerType ControllerType = ESnakeControllerType::AI;
};

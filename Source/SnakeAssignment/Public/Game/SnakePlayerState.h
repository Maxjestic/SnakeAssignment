// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SnakePlayerState.generated.h"

UENUM()
enum class ESnakeControllerType : uint8
{
	Keyboard1,
	Keyboard2,
	AI
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
	FORCEINLINE void AppleEaten();

protected:
	UPROPERTY( EditAnywhere )
	float SnakeSpeed = 500.f;

	int32 ApplesEaten = 0;

	UPROPERTY()
	ESnakeControllerType ControllerType = ESnakeControllerType::AI;
};

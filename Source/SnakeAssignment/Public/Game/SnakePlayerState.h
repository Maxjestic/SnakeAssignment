// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SnakePlayerState.generated.h"

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

	UFUNCTION()
	void IncreaseSnakeSpeed( const float ExtraSpeed );

	UFUNCTION()
	FORCEINLINE void AppleEaten();

protected:
	UPROPERTY( EditAnywhere )
	float SnakeSpeed = 500.f;

	int ApplesEaten = 0;
};

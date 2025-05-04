// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "SnakeGameMode.generated.h"

class ASnakePlayerState;
/**
 * 
 */
UCLASS()
class SNAKEASSIGNMENT_API ASnakeGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	void AppleEaten ( ASnakePlayerState* SnakePlayerState ) const;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "SnakeGameState.generated.h"

class ASnakePlayerState;

UENUM( BlueprintType )
enum class ESnakeGameMode : uint8
{
	Cooperative,
	Battle
};

/**
 * 
 */
UCLASS()
class SNAKEASSIGNMENT_API ASnakeGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	UFUNCTION( BlueprintCallable )
	FORCEINLINE ESnakeGameMode GetSnakePlayMode() const { return SnakeGameMode; }

	UFUNCTION( BlueprintCallable )
	void SetSnakePlayMode( const ESnakeGameMode NewSnakePlayMode );

	TArray<TObjectPtr<ASnakePlayerState>> GetAliveSnakes() const;

	TArray<TObjectPtr<ASnakePlayerState>> GetAllSnakes() const;

private:
	ESnakeGameMode SnakeGameMode = ESnakeGameMode::Cooperative;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SnakeGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SNAKEASSIGNMENT_API ASnakeGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual APlayerController* SpawnPlayerController( ENetRole InRemoteRole, const FString& Options ) override;

	UPROPERTY( EditAnywhere )
	int32 ApplesAmount = 10;

	void AppleAte();

	void PlayerDied();

protected:
	UFUNCTION( BlueprintImplementableEvent )
	void OnGameOver();
	
private:
	void CheckForGameOver();
	
	bool WinConditionMet() const;

	int32 ApplesEatenSoFar = 0;

	int32 NumberOfPlayers = 0;
};

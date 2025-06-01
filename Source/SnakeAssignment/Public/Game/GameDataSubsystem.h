// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SnakeGameState.h"
#include "SnakePlayerState.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameDataSubsystem.generated.h"

USTRUCT()
struct FGameData
{
	GENERATED_BODY()
	
	UPROPERTY()
	ESnakeGameMode SnakeGameMode;
};

/**
 * 
 */
UCLASS()
class SNAKEASSIGNMENT_API UGameDataSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION( BlueprintCallable )
	FORCEINLINE int32 GetNumPlayers() const { return NumPlayers; }

	UFUNCTION( BlueprintCallable )
	void SetNumPlayers( const int32 NewNumPlayers );

	UFUNCTION( BlueprintCallable )
	bool GetPlayerControllerType(const int32 Index, ESnakeControllerType& OutControllerType) const;

	UFUNCTION( BlueprintCallable )
	bool SetPlayerControllerType( const int32 Index, const ESnakeControllerType NewControllerType );

	UFUNCTION( BlueprintCallable )
	void SaveGameData();

	UFUNCTION( BlueprintCallable )
	void LoadGameData() const;
	
private:
	UPROPERTY()
	int32 NumPlayers = 1;
	
	UPROPERTY()
	TArray<ESnakeControllerType> SnakeControllerTypes;
	
	UPROPERTY()
	FGameData GameData;
};

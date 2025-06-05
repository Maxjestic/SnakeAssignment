// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SnakeGameState.h"
#include "SnakePlayerState.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameDataSubsystem.generated.h"

USTRUCT( BlueprintType )
struct FGameData
{
	GENERATED_BODY()

	UPROPERTY()
	ESnakeGameMode SnakeGameMode = ESnakeGameMode::Cooperative;

	UPROPERTY( BlueprintReadWrite )
	int32 Level = 0;
};

USTRUCT( BlueprintType )
struct FScoreData
{
	GENERATED_BODY()

	UPROPERTY( BlueprintReadWrite )
	FString Name;

	UPROPERTY( BlueprintReadWrite )
	int32 Score;
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
	bool GetPlayerControllerType( const int32 Index, ESnakeControllerType& OutControllerType ) const;

	UFUNCTION( BlueprintCallable )
	bool SetPlayerControllerType( const int32 Index, const ESnakeControllerType NewControllerType );

	UFUNCTION( BlueprintCallable )
	void SaveGameData();

	UFUNCTION( BlueprintCallable )
	void SaveLevelNumber( const int32 InLevel );

	UFUNCTION( BlueprintCallable )
	FORCEINLINE int32 GetLevelNumber() const { return GameData.Level; }

	UFUNCTION( BlueprintCallable )
	void LoadGameData() const;

	UFUNCTION( BlueprintCallable )
	void SaveScoreData();

	UFUNCTION( BlueprintCallable )
	TArray<FScoreData> GetScoreData() const;

private:
	UPROPERTY()
	int32 NumPlayers = 1;

	UPROPERTY()
	TArray<ESnakeControllerType> SnakeControllerTypes;

	UPROPERTY()
	TArray<FScoreData> Scores;

	UPROPERTY()
	FGameData GameData = FGameData();

	void SaveScoresForCooperative();

	void SaveScoresForBattle();
};

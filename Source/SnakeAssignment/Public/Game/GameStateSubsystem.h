// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameStateSubsystem.generated.h"

UENUM( BlueprintType )
enum class EGameState : uint8
{
	Init,
	Menu,
	Intro,
	Play,
	Pause,
	Outro
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FOnGameStateChanged, EGameState, OldGameState, EGameState, NewGameState );

/**
 * 
 */
UCLASS()
class SNAKEASSIGNMENT_API UGameStateSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UPROPERTY( BlueprintAssignable, Category = "GameState" )
	FOnGameStateChanged OnGameStateChanged;

	UFUNCTION()
	FORCEINLINE EGameState GetGameState() const { return GameState; }

	UFUNCTION( BlueprintCallable )
	void SetGameState( const EGameState NewGameState );

private:
	EGameState GameState = EGameState::Init;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "StateMachineSubsystem.generated.h"

UENUM( BlueprintType )
enum class EGlobalState : uint8
{
	Init,
	Menu,
	Intro,
	Play,
	Pause,
	Outro,
	Quit
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FOnGlobalStateChanged, EGlobalState, OldGlobalState, EGlobalState, NewGlobalState );

/**
 * 
 */
UCLASS()
class SNAKEASSIGNMENT_API UStateMachineSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UPROPERTY( BlueprintAssignable, Category = "GlobalState" )
	FOnGlobalStateChanged OnGlobalStateChanged;

	UFUNCTION()
	FORCEINLINE EGlobalState GetGameState() const { return GameState; }

	UFUNCTION( BlueprintCallable )
	void SetGameState( const EGlobalState NewGlobalState );

private:
	EGlobalState GameState = EGlobalState::Init;
};

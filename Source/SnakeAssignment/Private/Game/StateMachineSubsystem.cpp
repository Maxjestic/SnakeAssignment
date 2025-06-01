// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/StateMachineSubsystem.h"

void UStateMachineSubsystem::SetGameState( const EGlobalState NewGlobalState )
{
	if (GameState == NewGlobalState)
	{
		return;
	}
	const EGlobalState OldGameState = GameState;
	GameState = NewGlobalState;
	OnGlobalStateChanged.Broadcast( OldGameState, NewGlobalState );
}

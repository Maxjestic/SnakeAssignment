// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/GameStateSubsystem.h"

void UGameStateSubsystem::SetGameState( const EGameState NewGameState )
{
	if (GameState == NewGameState)
	{
		return;
	}
	const EGameState OldGameState = GameState;
	GameState = NewGameState;
	OnGameStateChanged.Broadcast( OldGameState, NewGameState );
}

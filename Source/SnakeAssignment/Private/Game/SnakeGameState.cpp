// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/SnakeGameState.h"

#include "Game/SnakePlayerState.h"

void ASnakeGameState::SetSnakePlayMode( const ESnakeGameMode NewSnakePlayMode )
{
	SnakeGameMode = NewSnakePlayMode;
}

TArray<TObjectPtr<ASnakePlayerState>> ASnakeGameState::GetAliveSnakes() const
{
	TArray<TObjectPtr<ASnakePlayerState>> AliveSnakes;
	for ( TObjectPtr<APlayerState> PlayerState : PlayerArray )
	{
		if ( ASnakePlayerState* SnakePlayerState = Cast<ASnakePlayerState>( PlayerState ) )
		{
			if ( !SnakePlayerState->IsDead() )
			{
				AliveSnakes.Add( SnakePlayerState );
			}
		}
	}
	return AliveSnakes;
}

TArray<TObjectPtr<ASnakePlayerState>> ASnakeGameState::GetAllSnakes() const
{
	TArray<TObjectPtr<ASnakePlayerState>> Snakes;
	for ( TObjectPtr<APlayerState> PlayerState : PlayerArray )
	{
		if ( ASnakePlayerState* SnakePlayerState = Cast<ASnakePlayerState>( PlayerState ) )
		{
			Snakes.Add( SnakePlayerState );
		}
	}
	return Snakes;
}

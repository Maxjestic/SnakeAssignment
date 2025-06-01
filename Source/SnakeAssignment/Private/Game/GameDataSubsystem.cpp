// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/GameDataSubsystem.h"

void UGameDataSubsystem::SetNumPlayers( const int NewNumPlayers )
{
	NumPlayers = NewNumPlayers;

	SnakeControllerTypes.SetNum( NumPlayers );
}

bool UGameDataSubsystem::GetPlayerControllerType( const int32 Index, ESnakeControllerType& OutControllerType ) const
{
	if ( !SnakeControllerTypes.IsValidIndex( Index ) )
	{		
		return false;
	}
	OutControllerType = SnakeControllerTypes[Index];
	return true;
}

bool UGameDataSubsystem::SetPlayerControllerType( const int32 Index, const ESnakeControllerType NewControllerType )
{
	if ( !SnakeControllerTypes.IsValidIndex( Index ) )
	{
		return false;
	}
	SnakeControllerTypes[Index] = NewControllerType;
	return true;
}

void UGameDataSubsystem::SaveGameData()
{
	const UWorld* World = GetWorld();
	if ( !IsValid( World ) )
	{
		UE_LOG( LogTemp, Error, TEXT("World is invalid") );
		return;
	}

	if ( const ASnakeGameState* SnakeGameState = World->GetGameState<ASnakeGameState>() )
	{
		GameData.SnakeGameMode = SnakeGameState->GetSnakePlayMode();
	}
}

void UGameDataSubsystem::LoadGameData() const
{
	const UWorld* World = GetWorld();
	if ( !IsValid( World ) )
	{
		UE_LOG( LogTemp, Error, TEXT("World is invalid") );
		return;
	}

	if ( ASnakeGameState* SnakeGameState = World->GetGameState<ASnakeGameState>() )
	{
		SnakeGameState->SetSnakePlayMode( GameData.SnakeGameMode );
	}
}

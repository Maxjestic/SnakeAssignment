// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/GameDataSubsystem.h"

void UGameDataSubsystem::SetNumPlayers( const int NewNumPlayers )
{
	NumPlayers = NewNumPlayers;

	SnakeControllerTypes.SetNum( NumPlayers );

	// Temp code
	for ( int i = 0; i < NumPlayers; i++ )
	{
		if ( i > 1 )
		{
			SnakeControllerTypes[i] = ESnakeControllerType::AI;
			continue;
		}

		SnakeControllerTypes[i] = i == 0 ? ESnakeControllerType::Keyboard1 : ESnakeControllerType::Keyboard2;
	}
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

void UGameDataSubsystem::SaveLevelNumber( const int32 InLevel )
{
	GameData.Level = InLevel;
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

void UGameDataSubsystem::SaveScoreData()
{
	const UWorld* World = GetWorld();
	if ( !IsValid( World ) )
	{
		UE_LOG( LogTemp, Error, TEXT("World is invalid") );
		return;
	}

	if ( ASnakeGameState* SnakeGameState = World->GetGameState<ASnakeGameState>() )
	{
		if ( SnakeGameState->GetSnakePlayMode() == ESnakeGameMode::Cooperative )
		{
			SaveScoresForCooperative();
		}
		else
		{
			SaveScoresForBattle();
		}
	}
}

TArray<FScoreData> UGameDataSubsystem::GetScoreData() const
{
	return Scores;
}

void UGameDataSubsystem::SaveScoresForCooperative()
{
	const UWorld* World = GetWorld();
	if ( !IsValid( World ) )
	{
		UE_LOG( LogTemp, Error, TEXT("World is invalid") );
		return;
	}

	if ( const ASnakeGameState* SnakeGameState = World->GetGameState<ASnakeGameState>() )
	{
		int32 PlayersScore = 0;
		int32 AIScore = 0;
		for ( const TObjectPtr<ASnakePlayerState> Snake : SnakeGameState->GetAllSnakes() )
		{
			if ( Snake->GetControllerType() == ESnakeControllerType::AI )
			{
				AIScore += Snake->AppleScore();
			}
			else
			{
				PlayersScore += Snake->AppleScore();
			}
		}
		Scores.Empty();
		Scores.Add( FScoreData( "Players", PlayersScore ) );
		Scores.Add( FScoreData( "AI", AIScore ) );
	}
}

void UGameDataSubsystem::SaveScoresForBattle()
{
	const UWorld* World = GetWorld();
	if ( !IsValid( World ) )
	{
		UE_LOG( LogTemp, Error, TEXT("World is invalid") );
		return;
	}

	if ( const ASnakeGameState* SnakeGameState = World->GetGameState<ASnakeGameState>() )
	{
		int32 AI = 1;
		Scores.Empty();
		for ( const TObjectPtr<ASnakePlayerState> Snake : SnakeGameState->GetAllSnakes() )
		{
			switch ( Snake->GetControllerType() )
			{
			case ESnakeControllerType::AI:
				Scores.Add( FScoreData( "AI" + AI, Snake->AppleScore() ) );
				AI++;
				break;
			case ESnakeControllerType::Keyboard1:
				Scores.Add( FScoreData( "Player 1", Snake->AppleScore() ) );
				break;
			case ESnakeControllerType::Keyboard2:
				Scores.Add( FScoreData( "Player 2", Snake->AppleScore() ) );
				break;
			default:
				break;
			}
		}
	}
}

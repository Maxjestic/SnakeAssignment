// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/SnakePlayerState.h"

#include "Game/SnakeGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Player/SnakePawn.h"

void ASnakePlayerState::SetControllerType( const ESnakeControllerType NewControllerType )
{
	ControllerType = NewControllerType;
}

void ASnakePlayerState::IncreaseSnakeSpeed( const float ExtraSpeed )
{
	SnakeSpeed += ExtraSpeed;
}

void ASnakePlayerState::AppleEaten()
{
	ApplesEaten++;	

	if ( ASnakeGameModeBase* GameMode = Cast<ASnakeGameModeBase>( UGameplayStatics::GetGameMode( GetWorld() ) ))
	{
		GameMode->AppleAte();
	}
}

void ASnakePlayerState::Died()
{
	bIsDead = true;
	if (ControllerType == ESnakeControllerType::AI)
	{
		return;
	}
	
	if ( ASnakeGameModeBase* GameMode = Cast<ASnakeGameModeBase>( UGameplayStatics::GetGameMode( GetWorld() ) ))
	{
		GameMode->PlayerDied();
	}
}

void ASnakePlayerState::StopSnake() const
{
	if (ASnakePawn* SnakePawn = GetPawn<ASnakePawn>())
	{
		SnakePawn->StopSnake();
	}
}

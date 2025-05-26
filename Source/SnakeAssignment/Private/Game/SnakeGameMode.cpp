// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/SnakeGameMode.h"

#include "Game/SnakePlayerState.h"

void ASnakeGameMode::AppleEaten( ASnakePlayerState* SnakePlayerState ) const
{
	SnakePlayerState->IncreaseSnakeSpeed( 5.f );
}

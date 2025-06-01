// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/SnakePlayerState.h"

#include "Game/SnakeGameMode.h"
#include "Kismet/GameplayStatics.h"

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

	if ( const ASnakeGameMode* GameMode = Cast<ASnakeGameMode>( UGameplayStatics::GetGameMode( GetWorld() ) ))
	{
		GameMode->AppleEaten(this);
	}
}

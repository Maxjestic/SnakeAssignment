// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/SnakeGameModeBase.h"

#include "AI/SnakeAIController.h"
#include "Game/GameDataSubsystem.h"

APlayerController* ASnakeGameModeBase::SpawnPlayerController( ENetRole InRemoteRole, const FString& Options )
{
	const int32 PlayerIndex = GetNumPlayers();
	
	const UGameInstance* GameInstance = GetGameInstance();
	ESnakeControllerType ControllerType = ESnakeControllerType::AI;
	GameInstance->GetSubsystem<UGameDataSubsystem>()->GetPlayerControllerType( PlayerIndex, ControllerType );
	
	if (ControllerType == ESnakeControllerType::AI)
	{
		return GetWorld()->SpawnActor<APlayerController>(ASnakeAIController::StaticClass());
	}
	
	return Super::SpawnPlayerController( InRemoteRole, Options );	
}

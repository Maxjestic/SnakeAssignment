// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SnakePlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Player/SnakePawn.h"

void ASnakePlayerController::BeginPlay()
{
	Super::BeginPlay();

	InitializeInput();
}

void ASnakePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if ( UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>( InputComponent ) )
	{
		Input->BindAction( MoveAction, ETriggerEvent::Triggered, this, &ASnakePlayerController::Move );
	}
}

void ASnakePlayerController::Move( const FInputActionValue& Value )
{
	if (ASnakePawn* SnakePawn = Cast<ASnakePawn>( GetPawn() ))
	{
		SnakePawn->SetNextDirection( ESnakeDirection::Up );
	}
}

void ASnakePlayerController::InitializeInput()
{
	checkf( DefaultMappingContext, TEXT("No Default Mapping Context") )
	checkf( MoveAction, TEXT("No Move Action") )

	if ( UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<
		UEnhancedInputLocalPlayerSubsystem>( GetLocalPlayer() ) )
	{
		SubSystem->AddMappingContext( DefaultMappingContext, 0 );
	}
}

// Fill out your copyright notice in the Description page of Project Settings.

// ReSharper disable CppMemberFunctionMayBeConst

#include "Player/SnakePlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"
#include "Player/SnakePawn.h"

void ASnakePlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void ASnakePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	ensureMsgf( UpActionP1, TEXT("Invalid UpActionP1") );
	ensureMsgf( UpActionP1, TEXT("Invalid DownActionP1") );
	ensureMsgf( UpActionP1, TEXT("Invalid LeftActionP1") );
	ensureMsgf( UpActionP1, TEXT("Invalid RightActionP1") );

	ensureMsgf( UpActionP2, TEXT("Invalid UpActionP2") );
	ensureMsgf( UpActionP2, TEXT("Invalid DownActionP2") );
	ensureMsgf( UpActionP2, TEXT("Invalid LeftActionP2") );
	ensureMsgf( UpActionP2, TEXT("Invalid RightActionP2") );

	if ( UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>( InputComponent ) )
	{
		Input->BindAction( UpActionP1, ETriggerEvent::Triggered, this, &ASnakePlayerController::MoveUpP1 );
		Input->BindAction( DownActionP1, ETriggerEvent::Triggered, this, &ASnakePlayerController::MoveDownP1 );
		Input->BindAction( LeftActionP1, ETriggerEvent::Triggered, this, &ASnakePlayerController::MoveLeftP1 );
		Input->BindAction( RightActionP1, ETriggerEvent::Triggered, this, &ASnakePlayerController::MoveRightP1 );

		Input->BindAction( UpActionP2, ETriggerEvent::Triggered, this, &ASnakePlayerController::MoveUpP2 );
		Input->BindAction( DownActionP2, ETriggerEvent::Triggered, this, &ASnakePlayerController::MoveDownP2 );
		Input->BindAction( LeftActionP2, ETriggerEvent::Triggered, this, &ASnakePlayerController::MoveLeftP2 );
		Input->BindAction( RightActionP2, ETriggerEvent::Triggered, this, &ASnakePlayerController::MoveRightP2 );
	}
}

void ASnakePlayerController::OnPossess( APawn* InPawn )
{
	Super::OnPossess( InPawn );	

	SnakePawn = Cast<ASnakePawn>( GetPawn() );
	if ( !IsValid( SnakePawn ) )
	{
		UE_LOG( LogTemp,
				Error,
				TEXT("%s [%s:%d] - SnakePawn is not valid!"),
				TEXT(__FUNCTION__),
				TEXT(__FILE__),
				__LINE__ )

		return;
	}

	SnakePlayerState = GetPlayerState<ASnakePlayerState>();
	if ( !IsValid( SnakePlayerState ) )
	{
		UE_LOG( LogTemp,
				Error,
				TEXT("%s [%s:%d] - SnakePlayerState is not valid!"),
				TEXT(__FUNCTION__),
				TEXT(__FILE__),
				__LINE__ )

		return;
	}

	InitializeInput();
}

void ASnakePlayerController::MoveUpP1( const FInputActionValue& Value )
{
	if ( ASnakePawn* UseSnakePawn = GetSnakePawnUsingKeyboard( 1 ) )
	{
		UseSnakePawn->SetNextDirection( ESnakeDirection::Up );
	}
}

void ASnakePlayerController::MoveDownP1( const FInputActionValue& Value )
{
	if ( ASnakePawn* UseSnakePawn = GetSnakePawnUsingKeyboard( 1 ) )
	{
		UseSnakePawn->SetNextDirection( ESnakeDirection::Down );
	}
}

void ASnakePlayerController::MoveLeftP1( const FInputActionValue& Value )
{
	if ( ASnakePawn* UseSnakePawn = GetSnakePawnUsingKeyboard( 1 ) )
	{
		UseSnakePawn->SetNextDirection( ESnakeDirection::Left );
	}
}

void ASnakePlayerController::MoveRightP1( const FInputActionValue& Value )
{
	if ( ASnakePawn* UseSnakePawn = GetSnakePawnUsingKeyboard( 1 ) )
	{
		UseSnakePawn->SetNextDirection( ESnakeDirection::Right );
	}
}

void ASnakePlayerController::MoveUpP2( const FInputActionValue& Value )
{
	if ( ASnakePawn* UseSnakePawn = GetSnakePawnUsingKeyboard( 2 ) )
	{
		UseSnakePawn->SetNextDirection( ESnakeDirection::Up );
	}
}

void ASnakePlayerController::MoveDownP2( const FInputActionValue& Value )
{
	if ( ASnakePawn* UseSnakePawn = GetSnakePawnUsingKeyboard( 2 ) )
	{
		UseSnakePawn->SetNextDirection( ESnakeDirection::Down );
	}
}

void ASnakePlayerController::MoveLeftP2( const FInputActionValue& Value )
{
	if ( ASnakePawn* UseSnakePawn = GetSnakePawnUsingKeyboard( 2 ) )
	{
		UseSnakePawn->SetNextDirection( ESnakeDirection::Left );
	}
}

void ASnakePlayerController::MoveRightP2( const FInputActionValue& Value )
{
	if ( ASnakePawn* UseSnakePawn = GetSnakePawnUsingKeyboard( 2 ) )
	{
		UseSnakePawn->SetNextDirection( ESnakeDirection::Right );
	}
}

void ASnakePlayerController::InitializeInput()
{
	ensureMsgf( InputMappingContextP1, TEXT("Invalid InputMappingContextP1") );

	ensureMsgf( InputMappingContextP2, TEXT("Invalid InputMappingContextP2") );

	if ( UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<
		UEnhancedInputLocalPlayerSubsystem>( GetLocalPlayer() ) )
	{
		SubSystem->AddMappingContext( InputMappingContextP1, 0 );
		SubSystem->AddMappingContext( InputMappingContextP2, 0 );
	}
}

ASnakePawn* ASnakePlayerController::GetSnakePawnUsingKeyboard( const int KeyboardId ) const
{
	TArray<AActor*> Controllers;
	UGameplayStatics::GetAllActorsOfClass( GetWorld(), ASnakePlayerController::StaticClass(), Controllers );

	for ( AActor* Actor : Controllers )
	{
		if (const ASnakePlayerController* SnakePlayerController = Cast<ASnakePlayerController>( Actor ))
		{
			const ESnakeControllerType SnakeControllerType = SnakePlayerController->SnakePlayerState->GetControllerType();
			if (SnakeControllerType == ESnakeControllerType::Keyboard1 && KeyboardId == 1 ||
				SnakeControllerType == ESnakeControllerType::Keyboard2 && KeyboardId == 2)
			{
				return SnakePlayerController->SnakePawn;
			}	
		}		
	}

	return nullptr;
}

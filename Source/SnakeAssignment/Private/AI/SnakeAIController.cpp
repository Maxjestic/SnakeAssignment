// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SnakeAIController.h"

#include "Actors/Apple.h"
#include "Game/SnakeWorld.h"
#include "Kismet/GameplayStatics.h"
#include "Player/SnakePawn.h"

void ASnakeAIController::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> OutActors;

	UGameplayStatics::GetAllActorsOfClass( GetWorld(), ASnakeWorld::StaticClass(), OutActors );

	if ( OutActors.Num() == 0 )
	{
		UE_LOG( LogTemp,
		        Error,
		        TEXT("%s [%s:%d] - No SnakeWorlds found!"),
		        TEXT(__FUNCTION__),
		        TEXT(__FILE__),
		        __LINE__ );
	}

	SnakeWorld = Cast<ASnakeWorld>( OutActors[0] );

	OutActors.Empty();

	UGameplayStatics::GetAllActorsOfClass( GetWorld(), AApple::StaticClass(), OutActors );

	if ( OutActors.Num() == 0 )
	{
		UE_LOG( LogTemp,
		        Error,
		        TEXT("%s [%s:%d] - No Apples found!"),
		        TEXT(__FUNCTION__),
		        TEXT(__FILE__),
		        __LINE__ );
	}

	if ( AApple* Apple = Cast<AApple>( OutActors[0] ) )
	{
		AppleX = -OutActors[0]->GetActorLocation().X / TileSize;
		AppleY = OutActors[0]->GetActorLocation().Y / TileSize;
		Apple->OnAppleEaten.AddDynamic( this, &ASnakeAIController::ResetAppleXY );
	}
}

void ASnakeAIController::Tick( float DeltaSeconds )
{
	Super::Tick( DeltaSeconds );

	if ( !IsValid( SnakePawn ) || !IsValid( SnakeWorld ) )
	{
		return;
	}

	SnakePawn->SetNextDirection( FindTheBestDirection() );
}

void ASnakeAIController::ResetAppleXY( const int32 NewX, const int32 NewY )
{
	AppleX = NewX;
	AppleY = NewY;
}

void ASnakeAIController::OnPossess( APawn* InPawn )
{
	Super::OnPossess( InPawn );

	SnakePawn = Cast<ASnakePawn>( InPawn );
}

ESnakeDirection ASnakeAIController::FindTheBestDirection() const
{
	const FVector Location = SnakePawn->GetActorLocation();
	const int32 X = -Location.X / TileSize;
	const int32 Y = Location.Y / TileSize;

	int32 LowestRating = MAX_int32;
	ESnakeDirection BestDirection = ESnakeDirection::None;

	constexpr int Directions[8] = {
		-1, 0,
		1, 0,
		0, -1,
		0, 1
	};

	for ( int32 Direction = 0; Direction < 4; Direction++ )
	{
		UE_LOG( LogTemp,
		        Warning,
		        TEXT( "X: %d, Y: %d" ),
		        X + Directions[Direction * 2],
		        Y + Directions[Direction * 2 + 1] );
		const int32 Rating = RateTile( X + Directions[Direction * 2], Y + Directions[Direction * 2 + 1] );
		if ( BestDirection == ESnakeDirection::None || Rating < LowestRating )
		{
			LowestRating = Rating;
			BestDirection = static_cast<ESnakeDirection>(Direction);
		}
	}

	return BestDirection;
}

int32 ASnakeAIController::RateTile( const int32 InX, const int32 InY ) const
{
	if ( SnakeWorld->IsWall( InX, InY ) )
	{
		return 10000;
	}

	return FMath::Abs( AppleX - InX ) + FMath::Abs( AppleY - InY );
}

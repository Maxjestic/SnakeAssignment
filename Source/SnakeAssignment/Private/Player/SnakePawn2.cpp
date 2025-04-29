// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SnakePawn2.h"

#include "Components/SphereComponent.h"

// Sets default values
ASnakePawn2::ASnakePawn2()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>( TEXT( "SceneComponent" ) );
	RootComponent = SceneComponent;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>( TEXT( "CollisionComponent" ) );
	CollisionComponent->SetupAttachment( RootComponent );
}

// Called when the game starts or when spawned
void ASnakePawn2::BeginPlay()
{
	Super::BeginPlay();

	GEngine->AddOnScreenDebugMessage( -1, 5.f, FColor::Red, TEXT( "Hello World" ) );
}

// Called every frame
void ASnakePawn2::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	UpdateFalling( DeltaTime );
	UpdateMovement( DeltaTime );
}

void ASnakePawn2::Jump()
{
	if ( !bInAir )
	{
		VelocityZ = 5.f;
	}
}

void ASnakePawn2::SetNextDirection( const ESnakeDirection NewDirection )
{
	DirectionsQueue.Add( NewDirection );
}

void ASnakePawn2::UpdateDirection()
{
	if ( DirectionsQueue.IsEmpty() )
	{
		return;
	}

	Direction = DirectionsQueue[0];
	DirectionsQueue.RemoveAt( 0 );

	switch ( Direction )
	{
	case ESnakeDirection::Up:
		ForwardRotation = FRotator( 0.f, 0.f, 0.f );
		break;
	case ESnakeDirection::Down:
		ForwardRotation = FRotator( 0.f, 180.f, 0.f );
		break;
	case ESnakeDirection::Left:
		ForwardRotation = FRotator( 0.f, 270.f, 0.f );
		break;
	case ESnakeDirection::Right:
		ForwardRotation = FRotator( 0.f, 90.f, 0.f );
		break;
	case ESnakeDirection::None:
		break;
	default: ;
	}
}

void ASnakePawn2::UpdateMovement( const float DeltaTime )
{
	float TotalMoveDistance = Speed * DeltaTime;
	float MoveDistance = TotalMoveDistance;

	while (MovedTileDistance + MoveDistance >= TileSize)
	{
		MoveDistance = TileSize - MovedTileDistance;
		MoveSnake( MoveDistance );

		UpdateDirection();
		
		TotalMoveDistance -= MoveDistance;
		MoveDistance = TotalMoveDistance;
		MovedTileDistance -= TileSize;
	}

	if (MoveDistance > 0.f)
	{
		MoveSnake( MoveDistance );
	}
}

void ASnakePawn2::MoveSnake( float Distance )
{
	FVector Position = GetActorLocation();
	switch ( Direction )
	{
	case ESnakeDirection::Up:
		Position.X += Distance;
		break;
	case ESnakeDirection::Down:
		Position.X -= Distance;
		break;
	case ESnakeDirection::Left:
		Position.Y -= Distance;
		break;
	case ESnakeDirection::Right:
		Position.Y += Distance;
		break;
	case ESnakeDirection::None:
	default:
		break;
	}
	
	SetActorLocation( Position );

	MovedTileDistance += Distance;
}

void ASnakePawn2::UpdateFalling( const float DeltaTime )
{
	FVector Position = GetActorLocation();

	VelocityZ -= 10.f * DeltaTime;

	Position.Z += VelocityZ;
	if ( Position.Z <= 0.f )
	{
		Position.Z = -Position.Z;
		VelocityZ = -VelocityZ * .5f;

		if ( FMath::Abs( VelocityZ ) < .1f )
		{
			VelocityZ = 0.f;
			Position.Z = 0.f;
			bInAir = false;
		}
	}
	else
	{
		bInAir = true;
	}

	SetActorLocation( Position );
}

// Called to bind functionality to input
void ASnakePawn2::SetupPlayerInputComponent( UInputComponent* PlayerInputComponent )
{
	Super::SetupPlayerInputComponent( PlayerInputComponent );
}

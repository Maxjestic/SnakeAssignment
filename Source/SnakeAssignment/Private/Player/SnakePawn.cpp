// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SnakePawn.h"

#include "Actors/Apple.h"
#include "Components/SphereComponent.h"
#include "Game/SnakePlayerState.h"
#include "Player/SnakeBodyPart.h"

// Sets default values
ASnakePawn::ASnakePawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>( TEXT( "SceneComponent" ) );
	RootComponent = SceneComponent;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>( TEXT( "CollisionComponent" ) );
	CollisionComponent->SetupAttachment( RootComponent );
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ASnakePawn::OnOverlapBegin);
}

// Called when the game starts or when spawned
void ASnakePawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASnakePawn::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	if (bIsStopped)
	{
		return;
	}
	
	UpdateFalling( DeltaTime );
	UpdateMovement( DeltaTime );
}

// Called to bind functionality to input
void ASnakePawn::SetupPlayerInputComponent( UInputComponent* PlayerInputComponent )
{
	Super::SetupPlayerInputComponent( PlayerInputComponent );
}

void ASnakePawn::PossessedBy( AController* NewController )
{
	Super::PossessedBy( NewController );

	SnakePlayerState = GetPlayerState<ASnakePlayerState>();
	check( SnakePlayerState );
}

void ASnakePawn::Jump()
{
	if ( !bInAir )
	{
		VelocityZ = 5.f;
	}
}

void ASnakePawn::SetNextDirection( const ESnakeDirection NewDirection )
{
	DirectionsQueue.Empty();

	DirectionsQueue.Add( NewDirection );
}

void ASnakePawn::OnOverlapBegin( UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult )
{
	if (AApple* Apple = Cast<AApple>(OtherActor))
	{
		AteApple();
		Apple->Relocate();
		return;
	}

	Death();
}

void ASnakePawn::UpdateDirection()
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

void ASnakePawn::UpdateMovement( const float DeltaTime )
{
	const float Speed = SnakePlayerState->GetSnakeSpeed();
	float TotalMoveDistance = Speed * DeltaTime;
	float MoveDistance = TotalMoveDistance;

	while ( MovedTileDistance + MoveDistance >= TileSize )
	{
		MoveDistance = TileSize - MovedTileDistance;
		MoveSnake( MoveDistance );

		UpdateDirection();

		TotalMoveDistance -= MoveDistance;
		MoveDistance = TotalMoveDistance;
		MovedTileDistance -= TileSize;

		if ( IsValid( ChildBodyPart ) )
		{
			ChildBodyPart->SetNextPosition( GetActorLocation() );
		}
		
	}

	if ( MoveDistance > 0.f )
	{
		MoveSnake( MoveDistance );
	}
}

void ASnakePawn::MoveSnake( const float Distance )
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

void ASnakePawn::UpdateFalling( const float DeltaTime )
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

void ASnakePawn::AteApple()
{
	UE_LOG( LogTemp, Warning, TEXT( "Ate apple" ) );

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = this;
	SpawnParameters.Instigator = this;

	ASnakeBodyPart* SnakeBodyPart = GetWorld()->SpawnActor<ASnakeBodyPart>( SnakeBodyPartClass,
	                                                                        GetActorLocation(),
	                                                                        GetActorRotation(),
	                                                                        SpawnParameters );
	if ( IsValid( ChildBodyPart ) )
	{
		ChildBodyPart->AddChildBodyPart( SnakeBodyPart );
	}
	else
	{
		ChildBodyPart = SnakeBodyPart;
	}

	SnakePlayerState->AppleEaten();
}

void ASnakePawn::Death()
{
	UE_LOG( LogTemp, Warning, TEXT( "Died" ) );

	StopSnake();
	
	SnakePlayerState->Died();
}

void ASnakePawn::StopSnake()
{
	if (IsValid( ChildBodyPart ) )
	{
		ChildBodyPart->StopMovement();
	}

	bIsStopped = true;
	DirectionsQueue.Empty();
	Direction = ESnakeDirection::None;
}

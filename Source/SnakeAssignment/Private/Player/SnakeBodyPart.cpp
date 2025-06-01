// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SnakeBodyPart.h"

#include "Components/SphereComponent.h"
#include "Player/SnakePawn.h"

// Sets default values
ASnakeBodyPart::ASnakeBodyPart()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>( TEXT( "SceneComponent" ) );
	RootComponent = SceneComponent;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>( TEXT( "CollisionComponent" ) );
	CollisionComponent->SetupAttachment( RootComponent );
}

// Called when the game starts or when spawned
void ASnakeBodyPart::BeginPlay()
{
	Super::BeginPlay();

	SnakeOwner = GetOwner<ASnakePawn>();
	check( SnakeOwner );
}

// Called every frame
void ASnakeBodyPart::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	
	if ( NextPosition != FVector::ZeroVector )
	{
		const float Speed = SnakeOwner->GetSnakeSpeed();
		FVector Position = GetActorLocation();
		const FVector Forward = (NextPosition - Position).GetSafeNormal();
		Position += Forward * Speed * DeltaTime;
		SetActorLocation( Position );
	}
}

void ASnakeBodyPart::AddChildBodyPart( ASnakeBodyPart* InChildBodyPart )
{
	if ( IsValid( ChildBodyPart ) )
	{
		ChildBodyPart->AddChildBodyPart( InChildBodyPart );
	}
	else
	{
		ChildBodyPart = InChildBodyPart;
		ChildBodyPart->SetActorLocation( GetActorLocation() );
	}
}

void ASnakeBodyPart::SetNextPosition( const FVector& InPosition )
{
	if ( IsValid( ChildBodyPart ) )
	{
		ChildBodyPart->SetNextPosition( NextPosition );
	}

	NextPosition = InPosition;
}

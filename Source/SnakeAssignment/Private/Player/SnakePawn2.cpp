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
}

// Called every frame
void ASnakePawn2::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

// Called to bind functionality to input
void ASnakePawn2::SetupPlayerInputComponent( UInputComponent* PlayerInputComponent )
{
	Super::SetupPlayerInputComponent( PlayerInputComponent );
}

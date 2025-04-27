// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/InstancedStaticMeshComponent.h"
#include "Game/SnakeWorld.h"

// Sets default values
ASnakeWorld::ASnakeWorld()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>( TEXT( "SceneComponent" ) );
	
	WallMeshInstances = CreateDefaultSubobject<UInstancedStaticMeshComponent>( TEXT( "WallMeshes" ) );
	WallMeshInstances->SetupAttachment( RootComponent );

	for ( int x = 0; x < 5000; x += 200 )
	{
		WallMeshInstances->AddInstance(FTransform(FRotator::ZeroRotator, FVector(x, 200.f, 0.f)));
	}
}

// Called when the game starts or when spawned
void ASnakeWorld::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASnakeWorld::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

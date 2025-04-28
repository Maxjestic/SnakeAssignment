// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Door.h"

#include "Components/BoxComponent.h"

// Sets default values
ADoor::ADoor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>( TEXT( "SceneComponent" ) );
	RootComponent = SceneComponent;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>( TEXT( "CollisionBox" ) );
	CollisionBox->SetupAttachment( RootComponent );
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();

	CollisionBox->OnComponentBeginOverlap.AddDynamic( this, &ADoor::OnBoxBeginOverlap );
}

// Called every frame
void ADoor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

void ADoor::OnBoxBeginOverlap( UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                               int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult )
{
	UE_LOG( LogTemp, Warning, TEXT( "Door Overlap" ) );
}

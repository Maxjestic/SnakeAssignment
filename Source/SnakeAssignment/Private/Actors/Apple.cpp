// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Apple.h"

#include "NiagaraFunctionLibrary.h"
#include "Components/PointLightComponent.h"
#include "Components/SphereComponent.h"
#include "Game/SnakeWorld.h"
#include "Kismet/GameplayStatics.h"
#include "SnakeAssignment/Definitions.h"


AApple::AApple()
{
	PrimaryActorTick.bCanEverTick = true;

	SphereCollider = CreateDefaultSubobject<USphereComponent>( FName( "SphereCollider" ) );
	SetRootComponent( SphereCollider );

	PointLight = CreateDefaultSubobject<UPointLightComponent>( FName( "PointLight" ) );
	PointLight->SetupAttachment( RootComponent );
}

void AApple::BeginPlay()
{
	Super::BeginPlay();

	Initialize();
	PointLight->SetIntensity( LightIntensityMin );
}

void AApple::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	const float CurrentIntensity = PointLight->Intensity;
	const float NewIntensity = FMath::FInterpTo( CurrentIntensity, LightIntensityMax, DeltaTime, InterpSpeed );
	PointLight->SetIntensity( NewIntensity );
}

void AApple::Relocate()
{
	int32 X = FMath::RandRange( 0, WorldHeight );
	int32 Y = FMath::RandRange( 0, WorldWidth );
	while ( SnakeWorld->IsWall( X, Y ) )
	{
		X = FMath::RandRange( 0, WorldHeight );
		Y = FMath::RandRange( 0, WorldWidth );
	}
	UE_LOG(LogTemp,Display,TEXT("X = %d,Y = %d\n"),X,Y);
	UNiagaraFunctionLibrary::SpawnSystemAtLocation( GetWorld(), EatVfx, GetActorLocation() );
	UGameplayStatics::PlaySoundAtLocation( this, EatSfx, GetActorLocation() );
	SetActorLocation( FVector( -X * TileSize, Y * TileSize, GetActorLocation().Z ) );
	PointLight->SetIntensity( LightIntensityMax );
	OnAppleEaten.Broadcast( X, Y );
}

void AApple::Initialize()
{
	TArray<AActor*> SnakeWorlds;
	UGameplayStatics::GetAllActorsOfClass( GetWorld(), ASnakeWorld::StaticClass(), SnakeWorlds );
	if ( SnakeWorlds.Num() > 0 )
	{
		SnakeWorld = Cast<ASnakeWorld>( SnakeWorlds[0] );
	}
	GetLevelWidthAndHeight();
}

void AApple::GetLevelWidthAndHeight()
{
	if ( SnakeWorld == nullptr )
	{
		return;
	}
	WorldHeight = SnakeWorld->GetLevelHeight();
	WorldWidth = SnakeWorld->GetLevelWidth();
}

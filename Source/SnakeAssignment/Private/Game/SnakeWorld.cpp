// Fill out your copyright notice in the Description page of Project Settings.

#include "Game/SnakeWorld.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Player/SnakePawn.h"
#include "SnakeAssignment/Definitions.h"
#include "StructUtils/PropertyBag.h"

// Sets default values
ASnakeWorld::ASnakeWorld()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>( TEXT( "SceneComponent" ) );
	SetRootComponent( SceneComponent );

	WallMeshInstances = CreateDefaultSubobject<UInstancedStaticMeshComponent>( TEXT( "WallMeshes" ) );
	WallMeshInstances->SetupAttachment( RootComponent );

	FloorMeshInstances = CreateDefaultSubobject<UInstancedStaticMeshComponent>( TEXT( "FloorMeshes" ) );
	FloorMeshInstances->SetupAttachment( RootComponent );
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

void ASnakeWorld::OnConstruction( const FTransform& Transform )
{
	Super::OnConstruction( Transform );

	WallMeshInstances->ClearInstances();
	FloorMeshInstances->ClearInstances();
	for ( auto Actor : Actors )
	{
		Actor->Destroy();
	}
	Actors.Empty();

	const FString FilePath = FPaths::ProjectDir() + TEXT( "/Levels/Level1.txt" );
	TArray<FString> Lines;

	if ( !FFileHelper::LoadFileToStringArray( Lines, *FilePath ) )
	{
		return;
	}

	int y = 0;
	for ( const FString& Line : Lines )
	{
		for ( int x = 0; x < Line.Len(); x++ )
		{
			FTransform Offset = FTransform( FRotator::ZeroRotator,
			                                FVector( (Lines.Num() - y) * 100.f, x * 100.f, 0.f ) );

			switch ( Line[x] )
			{
			case '#':
				WallMeshInstances->AddInstance( Offset );
				break;
			case '.':
				FloorMeshInstances->AddInstance( Offset );
				break;
			case '$':
				FloorMeshInstances->AddInstance( Offset );
				if ( IsValid( DoorActor ) )
				{
					if ( AActor* Actor = GetWorld()->SpawnActor<AActor>( DoorActor, Offset ); IsValid( Actor ) )
					{
						Actor->SetActorLabel( DoorActor->GetName() );
						Actor->AttachToActor( this, FAttachmentTransformRules::KeepRelativeTransform );
						Actors.Add( Actor );
					}
				}
				break;
			default:
				break;
			}
		}
		y++;
	}
}

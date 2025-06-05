// Fill out your copyright notice in the Description page of Project Settings.

#include "Game/SnakeWorld.h"
#include "Components/InstancedStaticMeshComponent.h"

// Sets default values
ASnakeWorld::ASnakeWorld()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>( TEXT( "SceneComponent" ) );
	SetRootComponent( SceneComponent );

	WallMeshInstances = CreateDefaultSubobject<UInstancedStaticMeshComponent>( TEXT( "WallMeshes" ) );
	WallMeshInstances->SetupAttachment( RootComponent );

	FloorMeshInstances = CreateDefaultSubobject<UInstancedStaticMeshComponent>( TEXT( "FloorMeshes" ) );
	FloorMeshInstances->SetupAttachment( RootComponent );
}

bool ASnakeWorld::IsWall( const int32 InX, const int32 InY )
{
	if ( InX < 0 || InX >= LevelWidth || InY < 0 || InY >= LevelHeight )
	{
		return false;
	}
	return LevelGrid[InX * LevelWidth + InY];
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
	for ( AActor* Actor : Actors )
	{
		Actor->Destroy();
	}
	Actors.Empty();

	const FString FilePath = FPaths::ProjectDir() + LevelName;
	TArray<FString> Lines;

	if ( !FFileHelper::LoadFileToStringArray( Lines, *FilePath ) )
	{
		return;
	}

	LevelHeight = Lines.Num() - 2;
	LevelWidth = Lines[0].Len() - 2;
	LevelGrid.Empty();
	LevelGrid.Reserve( LevelHeight * LevelWidth );
	
	int32 x = 0;
	for ( const FString& Line : Lines )
	{
		for ( int32 y = 0; y < Line.Len(); y++ )
		{
			FTransform Offset = FTransform( FRotator::ZeroRotator,
			                                FVector( -x * 100.f, y * 100.f, -50.f ) );

			bool bWall = false;
			switch ( Line[y] )
			{
			case '#':
				WallMeshInstances->AddInstance( Offset );
				bWall = true;
				break;
			case '.':
				FloorMeshInstances->AddInstance( Offset );
				break;
			case '$':
				FloorMeshInstances->AddInstance( Offset );
				if ( IsValid( DoorActor ) )
				{
					if ( AActor* Actor = GetWorld()->SpawnActor<AActor>( DoorActor, Offset ) )
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
			LevelGrid.Add( bWall );
		}
		x++;
	}
}

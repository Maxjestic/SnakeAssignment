// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SnakeWorld.generated.h"

UCLASS()
class SNAKEASSIGNMENT_API ASnakeWorld : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASnakeWorld();

	// Called every frame
	virtual void Tick( float DeltaTime ) override;

	virtual void OnConstruction(const FTransform& Transform) override;

	UPROPERTY( VisibleAnywhere )
	TObjectPtr<USceneComponent> SceneComponent;

	UPROPERTY( VisibleAnywhere )
	TObjectPtr<UInstancedStaticMeshComponent> WallMeshInstances;

	UPROPERTY( VisibleAnywhere )
	TObjectPtr<UInstancedStaticMeshComponent> FloorMeshInstances;

	UPROPERTY( EditDefaultsOnly )
	TSubclassOf<AActor> DoorActor;

	UFUNCTION( BlueprintCallable)
	FORCEINLINE int32 GetLevelWidth() const { return LevelWidth; }

	UFUNCTION( BlueprintCallable)
	FORCEINLINE int32 GetLevelHeight() const { return LevelHeight; }

	UFUNCTION( BlueprintCallable )
	bool IsWall( const int32 InX, const int32 InY );
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	TArray<AActor*> Actors;

	UPROPERTY()
	int32 LevelWidth = 0;
	
	UPROPERTY()
	int32 LevelHeight = 0;
	
	UPROPERTY()
	TArray<bool> LevelGrid;
};

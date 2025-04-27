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
	
	UPROPERTY( EditAnywhere )
	TObjectPtr<UInstancedStaticMeshComponent> WallMeshInstances;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

};

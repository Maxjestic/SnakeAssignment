// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SnakeBodyPart.generated.h"

class USphereComponent;

UCLASS()
class SNAKEASSIGNMENT_API ASnakeBodyPart : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASnakeBodyPart();

	UPROPERTY( VisibleAnywhere )
	TObjectPtr<USceneComponent> SceneComponent;

	UPROPERTY( VisibleAnywhere )
	TObjectPtr<USphereComponent> CollisionComponent;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SnakeBodyPart.generated.h"

class ASnakePawn2;
class USphereComponent;

UCLASS()
class SNAKEASSIGNMENT_API ASnakeBodyPart : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASnakeBodyPart();

	// Called every frame
	virtual void Tick( float DeltaTime ) override;

	UFUNCTION()
	void AddChildBodyPart(ASnakeBodyPart* InChildBodyPart);

	UFUNCTION()
	void SetNextPosition( const FVector& InPosition );

	UPROPERTY( VisibleAnywhere )
	TObjectPtr<USceneComponent> SceneComponent;

	UPROPERTY( VisibleAnywhere )
	TObjectPtr<USphereComponent> CollisionComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	TObjectPtr<ASnakeBodyPart> ChildBodyPart;

	UPROPERTY()
	TObjectPtr<ASnakePawn2> SnakeOwner;

	FVector NextPosition = FVector::ZeroVector;
};

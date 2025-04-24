// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SnakeAssignment/Definitions.h"
#include "SnakePawn2.generated.h"

class USphereComponent;

UCLASS()
class SNAKEASSIGNMENT_API ASnakePawn2 : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASnakePawn2();

	// Called every frame
	virtual void Tick( float DeltaTime ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent( UInputComponent* PlayerInputComponent ) override;

	UPROPERTY( VisibleAnywhere )
	TObjectPtr<USceneComponent> SceneComponent;

	UPROPERTY( VisibleAnywhere )
	TObjectPtr<USphereComponent> CollisionComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UFUNCTION( BlueprintCallable )
	void Jump();

	UFUNCTION( BlueprintCallable )
	void SetNextDirection( ESnakeDirection NewDirection );

	UFUNCTION()
	void UpdateDirection();

	UPROPERTY( VisibleAnywhere )
	float VelocityZ = 0.f;

	UPROPERTY( VisibleAnywhere )
	bool bInAir = false;

	UPROPERTY( VisibleAnywhere )
	ESnakeDirection Direction = ESnakeDirection::None;

	UPROPERTY( EditAnywhere )
	float Speed = 100.f;

	UPROPERTY()
	TArray<ESnakeDirection> DirectionsQueue;
};

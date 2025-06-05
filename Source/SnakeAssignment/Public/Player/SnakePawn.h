// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/SnakePlayerState.h"
#include "GameFramework/Pawn.h"
#include "SnakeAssignment/Definitions.h"
#include "SnakePawn.generated.h"

class ASnakePlayerState;
class ASnakeBodyPart;
class USphereComponent;

UCLASS()
class SNAKEASSIGNMENT_API ASnakePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASnakePawn();

	// Called every frame
	virtual void Tick( float DeltaTime ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent( UInputComponent* PlayerInputComponent ) override;

	virtual void PossessedBy( AController* NewController ) override;

	UPROPERTY( VisibleAnywhere )
	TObjectPtr<USceneComponent> SceneComponent;

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly )
	TObjectPtr<USphereComponent> CollisionComponent;

	UPROPERTY( EditDefaultsOnly )
	TSubclassOf<ASnakeBodyPart> SnakeBodyPartClass;

	FORCEINLINE float GetSnakeSpeed() const { return SnakePlayerState->GetSnakeSpeed(); }

	UFUNCTION( BlueprintCallable )
	void SetNextDirection( ESnakeDirection NewDirection );

	UFUNCTION( )
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	FORCEINLINE bool IsStopped() const {return bIsStopped;}

	void StopSnake();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY( BlueprintReadWrite )
	FRotator ForwardRotation = FRotator::ZeroRotator;

private:
	UFUNCTION( BlueprintCallable )
	void Jump();

	UFUNCTION()
	void UpdateDirection();

	UFUNCTION()
	void UpdateMovement( const float DeltaTime );

	UFUNCTION()
	void MoveSnake( const float Distance );

	UFUNCTION()
	void UpdateFalling( const float DeltaTime );

	UFUNCTION()
	void AteApple();

	void Death();
	
	UPROPERTY( VisibleAnywhere )
	float VelocityZ = 0.f;

	UPROPERTY( VisibleAnywhere )
	bool bInAir = false;

	bool bIsStopped = false;

	UPROPERTY( VisibleAnywhere )
	ESnakeDirection Direction = ESnakeDirection::None;

	UPROPERTY()
	float MovedTileDistance = 0.f;

	UPROPERTY()
	TArray<ESnakeDirection> DirectionsQueue;

	UPROPERTY()
	TObjectPtr<ASnakeBodyPart> ChildBodyPart;

	UPROPERTY()
	TObjectPtr<ASnakePlayerState> SnakePlayerState;
};

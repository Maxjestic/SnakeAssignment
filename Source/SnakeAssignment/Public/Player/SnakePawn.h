// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SnakePawn.generated.h"

class UCameraComponent;
class USpringArmComponent;
class USphereComponent;

UCLASS()
class SNAKEASSIGNMENT_API ASnakePawn : public APawn
{
	GENERATED_BODY()

public:
	/** Default constructor */
	ASnakePawn();

	//~ Begin AActor Interface
	virtual void Tick( float DeltaTime ) override;
	//~ End AActor Interface

	//~ Begin APawn Interface
	virtual void SetupPlayerInputComponent( UInputComponent* PlayerInputComponent ) override;
	//~ End APawn Interface

protected:
	//~ Begin AActor Interface
	virtual void BeginPlay() override;
	//~ End AActor Interface

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly )
	TObjectPtr<USphereComponent> CollisionSphere;

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly )
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly )
	TObjectPtr<UCameraComponent> Camera;
	
	UPROPERTY( VisibleAnywhere, BlueprintReadOnly )
	TObjectPtr<UStaticMeshComponent> MeshHead;

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly )
	TObjectPtr<UStaticMeshComponent> MeshEyeR;

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly )
	TObjectPtr<UStaticMeshComponent> MeshEyeL;

private:
};

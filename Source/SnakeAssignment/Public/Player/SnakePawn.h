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

	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	TObjectPtr<USphereComponent> CollisionSphere;

	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	TObjectPtr<UCameraComponent> Camera;
	
	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	TObjectPtr<UStaticMeshComponent> MeshHead;

	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	TObjectPtr<UStaticMeshComponent> MeshEyeR;

	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	TObjectPtr<UStaticMeshComponent> MeshEyeL;

private:
};

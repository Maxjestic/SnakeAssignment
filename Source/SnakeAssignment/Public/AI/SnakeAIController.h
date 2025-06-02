// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SnakeAssignment/Definitions.h"
#include "SnakeAIController.generated.h"

class ASnakeWorld;
class ASnakePawn;
/**
 * 
 */
UCLASS()
class SNAKEASSIGNMENT_API ASnakeAIController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void Tick(float DeltaSeconds) override;
	
protected:
	virtual void BeginPlay() override;
	
	virtual void OnPossess(APawn* InPawn) override;

	ESnakeDirection FindTheBestDirection() const;

	int32 RateTile(const int32 InX, const int32 InY) const;
	
	UPROPERTY()
	TObjectPtr<ASnakePawn> SnakePawn;

	UPROPERTY()
	TObjectPtr<ASnakeWorld> SnakeWorld;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Door.generated.h"

class UBoxComponent;

UCLASS()
class SNAKEASSIGNMENT_API ADoor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADoor();
	
	// Called every frame
	virtual void Tick( float DeltaTime ) override;

	UPROPERTY( VisibleAnywhere )
	TObjectPtr<USceneComponent> SceneComponent;

	UPROPERTY( EditAnywhere )
	TObjectPtr<UBoxComponent> CollisionBox;

	UFUNCTION()
	void OnBoxBeginOverlap( UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                        int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult );

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
};

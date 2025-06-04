// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Apple.generated.h"

class UPointLightComponent;
class UNiagaraSystem;
class ASnakeWorld;
class USphereComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FOnAppleEaten, const int32, X, const int32, Y );

UCLASS()
class SNAKEASSIGNMENT_API AApple : public AActor
{
	GENERATED_BODY()

public:
	AApple();

	FOnAppleEaten OnAppleEaten;
	
	virtual void Tick( float DeltaTime ) override;

	void Relocate();

protected:
	virtual void BeginPlay() override;

	UPROPERTY( VisibleAnywhere )
	TObjectPtr<USphereComponent> SphereCollider;

	UPROPERTY( VisibleAnywhere )
	TObjectPtr<UPointLightComponent> PointLight;

	UPROPERTY( EditAnywhere )
	TObjectPtr<UNiagaraSystem> EatVfx;

	UPROPERTY( EditAnywhere )
	TObjectPtr<USoundBase> EatSfx;

	UPROPERTY( EditAnywhere )
	float LightIntensityMax;

	UPROPERTY( EditAnywhere )
	float LightIntensityMin;

	UPROPERTY( EditAnywhere )
	float InterpSpeed;

private:
	void Initialize();

	void GetLevelWidthAndHeight();

	UPROPERTY()
	TObjectPtr<ASnakeWorld> SnakeWorld = nullptr;

	int32 WorldWidth = 0;
	int32 WorldHeight = 0;
};

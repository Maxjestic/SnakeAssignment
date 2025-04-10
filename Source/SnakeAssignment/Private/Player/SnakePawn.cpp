// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SnakePawn.h"

#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/SpringArmComponent.h"

ASnakePawn::ASnakePawn()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>( FName( "CollisionSphere" ) );
	SetRootComponent( CollisionSphere );

	SpringArm = CreateDefaultSubobject<USpringArmComponent>( FName( "SpringArm" ) );
	SpringArm->SetupAttachment( RootComponent );

	Camera = CreateDefaultSubobject<UCameraComponent>( FName( "Camera" ) );
	Camera->SetupAttachment( SpringArm );

	MeshHead = CreateDefaultSubobject<UStaticMeshComponent>( FName( "Head" ) );
	MeshHead->SetupAttachment( RootComponent );

	MeshEyeR = CreateDefaultSubobject<UStaticMeshComponent>( FName( "RightEye" ) );
	MeshEyeR->SetupAttachment( MeshHead );

	MeshEyeL = CreateDefaultSubobject<UStaticMeshComponent>( FName( "LeftEye" ) );
	MeshEyeL->SetupAttachment( MeshHead );
}

void ASnakePawn::BeginPlay()
{
	Super::BeginPlay();
}

void ASnakePawn::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

void ASnakePawn::SetupPlayerInputComponent( UInputComponent* PlayerInputComponent )
{
	Super::SetupPlayerInputComponent( PlayerInputComponent );
}

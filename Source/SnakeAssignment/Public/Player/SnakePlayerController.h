// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SnakePlayerController.generated.h"

class ASnakePlayerState;
class ASnakePawn;
struct FInputActionValue;
class UInputAction;
class UInputMappingContext;
/**
 * 
 */
UCLASS()
class SNAKEASSIGNMENT_API ASnakePlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
	virtual void SetupInputComponent() override;

	virtual void OnPossess(APawn* InPawn) override;
	
	void MoveUpP1(const FInputActionValue& Value);
	void MoveDownP1(const FInputActionValue& Value);
	void MoveLeftP1(const FInputActionValue& Value);
	void MoveRightP1(const FInputActionValue& Value);
	
	void MoveUpP2(const FInputActionValue& Value);
	void MoveDownP2(const FInputActionValue& Value);
	void MoveLeftP2(const FInputActionValue& Value);
	void MoveRightP2(const FInputActionValue& Value);
	
	UPROPERTY(EditDefaultsOnly, Category="Input|Player 1")
	TObjectPtr<UInputMappingContext> InputMappingContextP1;

	UPROPERTY(EditDefaultsOnly, Category="Input|Player 1")
	TObjectPtr<UInputAction> UpActionP1;

	UPROPERTY(EditDefaultsOnly, Category="Input|Player 1")
	TObjectPtr<UInputAction> DownActionP1;

	UPROPERTY(EditDefaultsOnly, Category="Input|Player 1")
	TObjectPtr<UInputAction> LeftActionP1;

	UPROPERTY(EditDefaultsOnly, Category="Input|Player 1")
	TObjectPtr<UInputAction> RightActionP1;
	
	UPROPERTY(EditDefaultsOnly, Category="Input|Player 2")
	TObjectPtr<UInputMappingContext> InputMappingContextP2;

	UPROPERTY(EditDefaultsOnly, Category="Input|Player 2")
	TObjectPtr<UInputAction> UpActionP2;

	UPROPERTY(EditDefaultsOnly, Category="Input|Player 2")
	TObjectPtr<UInputAction> DownActionP2;

	UPROPERTY(EditDefaultsOnly, Category="Input|Player 2")
	TObjectPtr<UInputAction> LeftActionP2;

	UPROPERTY(EditDefaultsOnly, Category="Input|Player 2")
	TObjectPtr<UInputAction> RightActionP2;

private:
	UFUNCTION()
	void InitializeInput();

	UFUNCTION()
	ASnakePawn* GetSnakePawnUsingKeyboard(const int KeyboardId) const;
	
	UPROPERTY()
	TObjectPtr<ASnakePawn> SnakePawn;
	
	UPROPERTY()
	TObjectPtr<ASnakePlayerState> SnakePlayerState;
};

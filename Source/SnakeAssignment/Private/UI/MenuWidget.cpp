// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MenuWidget.h"

UMenuWidget::UMenuWidget( const FObjectInitializer& ObjectInitializer )
	: UUserWidget( ObjectInitializer )
{
	bAutomaticallyRegisterInputOnConstruction = true;
}

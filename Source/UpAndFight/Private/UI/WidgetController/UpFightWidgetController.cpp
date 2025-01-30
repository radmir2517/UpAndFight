// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/UpFightWidgetController.h"


void UUpFightWidgetController::BindCalledDepends()
{
	
}

void UUpFightWidgetController::BroadcastInitialValues()
{
	
}

void UUpFightWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& Params)
{
	PlayerController = Params.PlayerController;
	PlayerState = Params.PlayerState;
	AbilitySystemComponent = Params.AbilitySystemComponent;
	AttributeSet = Params.AttributeSet;
}

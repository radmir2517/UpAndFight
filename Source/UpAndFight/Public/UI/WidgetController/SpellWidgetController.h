// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/UpFightWidgetController.h"
#include "SpellWidgetController.generated.h"

/**
 * 
 */
UCLASS()
class UPANDFIGHT_API USpellWidgetController : public UUpFightWidgetController
{
	GENERATED_BODY()

public:
	
	virtual void BindCallBacksToDependencies();
	
	virtual void BroadcastInitialValues();
	
};

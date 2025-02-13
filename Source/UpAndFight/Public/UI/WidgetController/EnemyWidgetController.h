// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/UpFightWidgetController.h"
#include "EnemyWidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttributeChangeSignature, float, AttributeValue);

UCLASS(Blueprintable,BlueprintType)
class UPANDFIGHT_API UEnemyWidgetController : public UUpFightWidgetController
{
	GENERATED_BODY()
	
public:
	virtual void BindCallBacksToDependencies() override;

	virtual void BroadcastInitialValues() override;

	UPROPERTY(BlueprintAssignable)
	FAttributeChangeSignature HeathChangedDelegate;
	UPROPERTY(BlueprintAssignable)
	FAttributeChangeSignature MaxHeathChangedDelegate;
};

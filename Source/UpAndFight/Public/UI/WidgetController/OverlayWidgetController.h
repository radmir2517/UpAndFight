// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/UpFightWidgetController.h"
#include "OverlayWidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttributeChandedSignature,float,AttributeValue);

UCLASS()
class UPANDFIGHT_API UOverlayWidgetController : public UUpFightWidgetController
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FAttributeChandedSignature HealthChangedDelegate;
	UPROPERTY(BlueprintAssignable)
	FAttributeChandedSignature MaxHealthChangedDelegate;
	UPROPERTY(BlueprintAssignable)
	FAttributeChandedSignature ManaChangedDelegate;
	UPROPERTY(BlueprintAssignable)
	FAttributeChandedSignature MaxManaChangedDelegate;
	
	virtual void BindCalledDepends() override;
	virtual void BroadcastInitialValues() override;

	
};

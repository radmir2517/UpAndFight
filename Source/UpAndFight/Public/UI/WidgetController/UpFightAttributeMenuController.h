// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Data/AttributeDataAsset.h"
#include "UI/WidgetController/UpFightWidgetController.h"
#include "UpFightAttributeMenuController.generated.h"
//делегат который вернет структуру с описанием и название атрибута
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttributeInfoSignature,const FAttributeInfo&, AttributeInfo);

UCLASS(Blueprintable, BlueprintType)
class UPANDFIGHT_API UUpFightAttributeMenuController : public UUpFightWidgetController
{
	GENERATED_BODY()
public:
	virtual void BindCallBacksToDependencies() override;
	
	virtual void BroadcastInitialValues() override;

	// экземпляр делегата который вернет структуру с описанием и название атрибута
	UPROPERTY(BlueprintAssignable)
	FAttributeInfoSignature AttributeInfoDelegate;
	
	// указатель на базу атрибутов с описанием в UE
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UAttributeDataAsset> AttributeInfo;

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Data/AttributeDataAsset.h"
#include "UI/WidgetController/UpFightWidgetController.h"
#include "UpFightAttributeMenuController.generated.h"
class AUpFightPlayerState;
//делегат который вернет структуру с описанием и название атрибута
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttributeInfoSignature,const FAttributeInfo&, AttributeInfo);

//делегат?который вернет свободные очки атрибутов
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttributePointsSignature,const int32, AttributeInfo);
UCLASS(Blueprintable, BlueprintType)
class UPANDFIGHT_API UUpFightAttributeMenuController : public UUpFightWidgetController
{
	GENERATED_BODY()
public:
	virtual void BindCallBacksToDependencies() override;
	virtual void BroadcastInitialValues() override;
	// функция прибавления атрибута
	UFUNCTION(BlueprintCallable)
	void UpgradeAttributes(const FGameplayTag& AttributeTag);

	// экземпляр делегата который вернет структуру с описанием и название атрибута
	UPROPERTY(BlueprintAssignable)
	FAttributeInfoSignature AttributeInfoDelegate;
	// экземпляр делегата который вернет очки атрибутов при изменения уровня
	UPROPERTY(BlueprintAssignable)
	FAttributePointsSignature AttributePointsDelegate;
	
	// указатель на базу атрибутов с описанием в UE
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UAttributeDataAsset> AttributeInfo;

private:
	TObjectPtr<AUpFightPlayerState> UpPlayerState;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/UpFightWidgetController.h"
#include "OverlayWidgetController.generated.h"

class UUpFightUserWidget;


USTRUCT(BlueprintType,Blueprintable)
struct FUIWidgetRow : public FTableRowBase
{
	GENERATED_BODY()
	// тег для нахождения нужной строки
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag MessageTag = FGameplayTag();
	// текст сообщения
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText Message = FText();
	// субкласс виджета
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UUpFightUserWidget> MessageWidget;
	// иконка
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UTexture2D* Image = nullptr;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttributeChandedSignature, float, AttributeValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEffectMessageSignature, FUIWidgetRow, Row);

UCLASS()
class UPANDFIGHT_API UOverlayWidgetController : public UUpFightWidgetController
{
	GENERATED_BODY()
public:
	virtual void BindCallBacksToDependencies() override;
	virtual void BroadcastInitialValues() override;
	// функиця получения строки из таблицы
	template<typename T>
	T* GetDataRowFromTable(UDataTable* Table, FGameplayTag Tag);
	
	UPROPERTY(BlueprintAssignable)
	FAttributeChandedSignature HealthChangedDelegate;
	UPROPERTY(BlueprintAssignable)
	FAttributeChandedSignature MaxHealthChangedDelegate;
	UPROPERTY(BlueprintAssignable)
	FAttributeChandedSignature ManaChangedDelegate;
	UPROPERTY(BlueprintAssignable)
	FAttributeChandedSignature MaxManaChangedDelegate;
	// делегат отправляющий строку из MessageWidgetDataTable в виджет
	UPROPERTY(BlueprintAssignable)
	FEffectMessageSignature EffectMessageDelegate;

protected:
	UPROPERTY(EditDefaultsOnly, Category="Widget Data")
	TObjectPtr<UDataTable> MessageWidgetDataTable;
};

template <typename T>
T* UOverlayWidgetController::GetDataRowFromTable(UDataTable* Table, FGameplayTag Tag)
{
	
	T* Row = Table->FindRow<T>(Tag.GetTagName(), TEXT(""));
	if(Row)
	{
		return Row;
	}
	return nullptr;
}

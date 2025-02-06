// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/UpFightAttributeMenuController.h"

#include "AbilitySystem/UpFightAttributeSet.h"

void UUpFightAttributeMenuController::BindCallBacksToDependencies()
{	// проверим указатель на DataAsset AttributeInfo
	check(AttributeInfo);
	UUpFightAttributeSet* UpFightAS = CastChecked<UUpFightAttributeSet>(AttributeSet);

	for(auto Pair : UpFightAS->TagToAttributeFunc)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value()).AddLambda([this, Pair, UpFightAS](const FOnAttributeChangeData&)
		{
			FAttributeInfo Info = AttributeInfo->GetAttributeInfoByTag(Pair.Key);
			// заменим значение на настоящее текущее
			Info.AttributeValue = Pair.Value().GetNumericValue(UpFightAS);
			// и отправим виджету строки со значением
			if(Info.AttributeTag.IsValid())
			{	
				AttributeInfoDelegate.Broadcast(Info);
			}
		});
	}

}

void UUpFightAttributeMenuController::BroadcastInitialValues()
{	// получим 

	UUpFightAttributeSet* UpFightAS = Cast<UUpFightAttributeSet>(AttributeSet);
	if(UpFightAS == nullptr || UpFightAS->TagToAttributeFunc.IsEmpty()) return;
	// пробежимся по карте с атрибутами и их функциями
	for(auto Pair :UpFightAS->TagToAttributeFunc)
	{	// найдем атрибут в DataAsset и вытащим структуру с его именем и пустым знаечнием
		FAttributeInfo Info = AttributeInfo->GetAttributeInfoByTag(Pair.Key);
		// заменим значение на настоящее текущее
		Info.AttributeValue = Pair.Value().GetNumericValue(UpFightAS);
		// и отправим виджету строки со значением
		if(Info.AttributeTag.IsValid())
		{
			AttributeInfoDelegate.Broadcast(Info);
		}
	}
}


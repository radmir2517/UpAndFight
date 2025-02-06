// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "AttributeDataAsset.generated.h"



USTRUCT(Blueprintable)
struct FAttributeInfo
{
	GENERATED_BODY()
	
	FAttributeInfo(){};
	// тег по которому мы будем искать его
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag AttributeTag = FGameplayTag();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText AttributeName = FText();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText AttributeDescription = FText();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float AttributeValue = 0.f;
	
};

UCLASS(Blueprintable,BlueprintType)
class UPANDFIGHT_API UAttributeDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TArray<FAttributeInfo> AttributesInfo;
	// найдем структуру атрибута по тегу
	FAttributeInfo GetAttributeInfoByTag(const FGameplayTag& Tag);
};

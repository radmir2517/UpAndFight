// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "AbilityDataAsset.generated.h"

class UGameplayAbility;

// структура которая хранит Абилки персонажа 
USTRUCT(BlueprintType,Blueprintable)
struct FAbilityInfo
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FGameplayTag AbilityTag;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FGameplayTag InputTag;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TSubclassOf<UGameplayAbility> AbilityClass;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TObjectPtr<UTexture2D> AbilityIcon = nullptr;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TObjectPtr<UMaterialInstance> BackgroundImage = nullptr;;
};


UCLASS()
class UPANDFIGHT_API UAbilityDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TArray<FAbilityInfo> AbilitiesInfo;
	// найдем из массива абилок нужный по его тегу
	UFUNCTION(BlueprintCallable)
	FAbilityInfo FindAbilityInfoByTag(const FGameplayTag AbilityTag, bool bLogNotFound = false);
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "UpFightGameplayAbility.generated.h"

struct FTaggedMontage;
/**
 * 
 */
UCLASS()
class UPANDFIGHT_API UUpFightGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
public:

	UUpFightGameplayAbility();
	// тег который проверяется в ASC в AbilityInputTagHeld и в AbilityInputTagReleased
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag SetupInputTag;
	
	// получим рандомный монтаж из массива структы сонтажа с тегом
	UFUNCTION(BlueprintCallable)
	FTaggedMontage GetRandomTaggedMontageFromArray(const TArray<FTaggedMontage>& TaggedMontages);

	virtual FString GetSpellDescription(int32 Level);
	virtual FString GetNextLevelSpellDescription(int32 Level);
	static  FString GetLockedSpellDescription(int32 Level);
};

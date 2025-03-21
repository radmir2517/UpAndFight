// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "WaitCooldownChange.generated.h"

struct FActiveGameplayEffectHandle;
struct FGameplayEffectSpec;
struct FGameplayTag;
class UAbilitySystemComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCooldownChangeSignature, float, TimeRemaining);

UCLASS(BlueprintType,meta=(ExposedAsyncProxy))
class UPANDFIGHT_API UWaitCooldownChange : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FCooldownChangeSignature CooldownStartDelegate;
	
	UPROPERTY(BlueprintAssignable)
	FCooldownChangeSignature CooldownEndDelegate;
	
	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly="true"))
	static UWaitCooldownChange* WaitCooldownChange(UAbilitySystemComponent* ASC, FGameplayTag InCooldownTag);
	
	UFUNCTION(BlueprintCallable)
	void EndTask();

private:

	void CooldownTagEvent(const FGameplayTag, int32 Count);

	void OnActiveEffectAdded(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& EffectSpec,
	FActiveGameplayEffectHandle EffectHandle);
	
	FGameplayTag CooldownTag;
	UAbilitySystemComponent* ASC;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "UpFightGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class UPANDFIGHT_API UUpFightGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
public:
	// тег который проверяется в ASC в AbilityInputTagHeld и в AbilityInputTagReleased
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag SetupInputTag;
};

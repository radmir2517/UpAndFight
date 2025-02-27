// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Interface.h"
#include "CombatInterface.generated.h"



UINTERFACE(MinimalAPI)
class UCombatInterface : public UInterface
{
	GENERATED_BODY()
};

class UPANDFIGHT_API ICombatInterface
{
	GENERATED_BODY()

public:
	// функция ICombatInterface по получению уровня
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	int32 GetPlayerLevel();
	
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	FVector GetSocketLocation();

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	void UpdateMotionWarping(const FVector& TargetLocation);

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	UAnimMontage* GetHitReactMontage();

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	UAnimMontage* GetAttackMontage(FGameplayTag Tag);


	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	void Die();

	
};

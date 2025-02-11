// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/UpFightGameplayAbility.h"
#include "UpFightProjectileSpell.generated.h"

/**
 * 
 */
UCLASS(Blueprintable,BlueprintType)
class UPANDFIGHT_API UUpFightProjectileSpell : public UUpFightGameplayAbility
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void SpawnProjectile(FVector InTargetLocation);
	
protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> ProjectileClass;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> DamageEffect;
	
};

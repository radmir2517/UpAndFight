// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DamageGameplayAbility.h"
#include "AbilitySystem/Abilities/UpFightGameplayAbility.h"
#include "UpFightProjectileSpell.generated.h"

/**
 * 
 */
UCLASS(Blueprintable,BlueprintType)
class UPANDFIGHT_API UUpFightProjectileSpell : public UDamageGameplayAbility
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void SpawnProjectile(const FVector InTargetLocation, const FGameplayTag SocketTag, const bool OverridePitch, const float InPitchOverride);
	
protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool ShouldPitchOverride = false;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float PitchOverride = 0.f;
		
};

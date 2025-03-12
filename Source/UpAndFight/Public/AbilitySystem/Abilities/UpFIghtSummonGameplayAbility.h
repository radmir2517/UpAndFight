// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/UpFightGameplayAbility.h"
#include "UpFIghtSummonGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class UPANDFIGHT_API UUpFIghtSummonGameplayAbility : public UUpFightGameplayAbility
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	TArray<FVector> GetSpawnLocations();

	UFUNCTION(BlueprintPure, Category="Summoning")
	TSubclassOf<APawn> GetRandomMinionClass();
	// кол-во миньонов которых нужно заспавнить в данный момент
	UPROPERTY(BlueprintReadOnly, Category = "Summoning")
	int32 DeltaNumMinions = 0;

	UPROPERTY(EditDefaultsOnly, Category = "Summoning")
	TArray<TSubclassOf<APawn>> MinionClasses;

	UPROPERTY(EditDefaultsOnly, Category = "Summoning")
	float MinSpawnDistance = 50.f;

	UPROPERTY(EditDefaultsOnly, Category = "Summoning")
	float MaxSpawnDistance = 250.f;

	UPROPERTY(EditDefaultsOnly, Category = "Summoning")
	float SpawnSpread = 90.f;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Interface.h"
#include "CombatInterface.generated.h"

class UNiagaraSystem;

USTRUCT(BlueprintType)
struct FTaggedMontage
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAnimMontage* Montage = nullptr;
	// тег для WaitGameplayEvent
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag MontageTag;
	// тег для SocketLocation
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag SocketLocationTag;
	// звуковой эффект удара
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USoundBase* ImpactSound;
};


UINTERFACE(MinimalAPI)
class UCombatInterface : public UInterface
{
	GENERATED_BODY()
};

class UPANDFIGHT_API ICombatInterface
{
	GENERATED_BODY()

public:
	
	/* Montage */
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	FVector GetSocketLocation(const FGameplayTag& SocketTag);
	
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	void UpdateMotionWarping(const FVector& TargetLocation);
	
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	UAnimMontage* GetHitReactMontage();

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	UNiagaraSystem* GetBloodEffect();
	
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	TArray<FTaggedMontage> GetAttackMontages();

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	FTaggedMontage GetTaggedMontageByTag(const FGameplayTag& InMontageTag);

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	int32 GetMinionsCount();
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	int32 GetMaxMinionsCount();
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	void IncreaseMinionsCount(int32 Amount);
	/* end Montage*/

	// функция ICombatInterface по получению уровня
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	int32 GetPlayerLevel();
	// проверка bool Dead, оно меняется когда Health = 0 в AttributeSet и применение функции Die
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	bool IsDead();
	
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	AActor* GetActor();
	
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	void Die(const FVector& DeathVector);

	
};

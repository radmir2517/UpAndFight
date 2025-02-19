// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActiveGameplayEffectHandle.h"
#include "GameFramework/Actor.h"
#include "UpFightEffectActor.generated.h"

class UAbilitySystemComponent;
class UGameplayEffect;
class USphereComponent;

UENUM(BlueprintType)
enum class EEffectApplicationPolicy :uint8
{
	ApplyOnOverlap,
	ApplyOnEndOverlap,
	DoNotApply
};
UENUM(BlueprintType)
enum class EEffectRemovalPolicy :uint8
{
	RemoveOnEndOverlap,
	DoNotRemove
};


UCLASS()
class UPANDFIGHT_API AUpFightEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AUpFightEffectActor();

	
protected:
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable)
	//Функция применения эффекта к цели
	void ApplyEffectToTarget(AActor* Target,TSubclassOf<UGameplayEffect>GameplayEffectClass);

	UFUNCTION(BlueprintCallable)
	void OnOverlap(AActor* Target);
	UFUNCTION(BlueprintCallable)
	void OnEndOverlap(AActor* Target);
	
	// класс мгновенного эффекта
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Applied Effect")
	TSubclassOf<UGameplayEffect> InstanceGameplayEffectClass;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Applied Effect")
	EEffectApplicationPolicy InstantEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;

	// класс мгновенного эффекта
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Applied Effect")
	TSubclassOf<UGameplayEffect> DurationGameplayEffectClass;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Applied Effect")
	EEffectApplicationPolicy DurationEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Applied Effect")
	TSubclassOf<UGameplayEffect> InfinityGameplayEffectClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Applied Effect")
	EEffectApplicationPolicy InfinityEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Applied Effect")
	EEffectRemovalPolicy InfinityEffectRemovalPolicy = EEffectRemovalPolicy::RemoveOnEndOverlap;

	
	TMap<FActiveGameplayEffectHandle, UAbilitySystemComponent*> ActiveEffectHandles;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Applied Effect")
	bool bDestroyOnEffectRemoval = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Applied Effect")
	bool bApplyEffectToEnemy = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Applied Effect")
	float ActorLevel = 1.f;
	
};

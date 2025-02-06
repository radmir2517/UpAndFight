// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "UPCharacterBase.generated.h"

class UGameplayAbility;
class UGameplayEffect;
class UUpFightAttributeSet;
class UUpFightSystemComponent;
class UAttributeSet;
// сделаем класс абстрактным, чтобы нельзя было его создать
UCLASS(Abstract)
class UPANDFIGHT_API AUPCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AUPCharacterBase();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	// функция вызова первичных для работы наших функции
	virtual void InitAbilityInfo();
	// включим эффект первичных, вторичных и Vital атрибутов
	virtual void InitializeDefaultAttributes();
protected:
	virtual void BeginPlay() override;

	// включим эффект атрибутов
	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level);
	// применения эффекта с атрибутами Primary and Secondary, Vital
	void InitializePrimaryAttributes();
	void InitializeSecondaryAttributes();
	void InitializeVitalAttributes();
	// функция которая GiveAbility нашим StartedGameplayAbilities
	void AddCharacterAbilities();
	
	// создадим оружие
	UPROPERTY(VisibleAnywhere, Category="Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	UPROPERTY(EditDefaultsOnly,Category="Attributes")
	TSubclassOf<UGameplayEffect> PrimaryAttributesEffectClass;
	UPROPERTY(EditDefaultsOnly,Category="Attributes")
	TSubclassOf<UGameplayEffect> SecondaryAttributesEffectClass;
	UPROPERTY(EditDefaultsOnly,Category="Attributes")
	TSubclassOf<UGameplayEffect> VitalAttributesEffectClass;
	// способности которые должны быть вначале у игрока/врага
	UPROPERTY(EditDefaultsOnly,Category="Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartedGameplayAbilities;
	
};

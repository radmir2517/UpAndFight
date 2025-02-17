// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "MotionWarpingComponent.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "Interaction/CombatInterface.h"
#include "UPCharacterBase.generated.h"


class UGameplayAbility;
class UGameplayEffect;
class UUpFightAttributeSet;
class UUpFightSystemComponent;
class UAttributeSet;



// сделаем класс абстрактным, чтобы нельзя было его создать
UCLASS(Abstract)
class UPANDFIGHT_API AUPCharacterBase : public ACharacter, public IAbilitySystemInterface, public ICombatInterface
{
	GENERATED_BODY()

public:
	AUPCharacterBase();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	// функция вызова первичных для работы наших функции
	virtual void InitAbilityInfo();
	// включим эффект первичных, вторичных и Vital атрибутов
	virtual void InitializeDefaultAttributes();
	/* ICombatInterface */\
	virtual FVector GetSocketWeapon_Implementation() override;
	virtual void UpdateMotionWarping_Implementation(const FVector& TargetLocation) override;
	virtual UAnimMontage* GetHitReactMontage_Implementation() override;
	
	virtual void Die_Implementation() override;
	/*end ICombatInterface*/
	
protected:
	virtual void BeginPlay() override;
	
	// применения эффекта с атрибутами Primary and Secondary, Vital
	// функция которая GiveAbility нашим StartedGameplayAbilities
	void AddCharacterAbilities();
	UFUNCTION(NetMulticast,Reliable)
	void MulticastHandleDeath();

	void Dissolve();
	UFUNCTION(BlueprintImplementableEvent)
	void StartBodyDissolveTimeline(UMaterialInstanceDynamic* BodyInstanceDynamic);
	UFUNCTION(BlueprintImplementableEvent)
	void StartWeaponDissolveTimeline(UMaterialInstanceDynamic* WeaponInstanceDynamic);

	float DissolveValue = -1.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Character Class Default")
	int32 Level = 1;
	// переменная которая будет переключать состояние аниммации на state Died
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bDied = false;

	ECharacterClass CharacterClass = ECharacterClass::Warrior;
	
	// создадим оружие
	UPROPERTY(VisibleAnywhere, Category="Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;
	
	UPROPERTY(VisibleAnywhere, Category="Combat")
	TObjectPtr<UMotionWarpingComponent> MotionWarping;
	
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

	UPROPERTY(EditDefaultsOnly,Category="Abilities")
	TObjectPtr<UAnimMontage> HitReactMontage;

	UPROPERTY(EditDefaultsOnly,Category="Dissolve")
	TObjectPtr<UMaterialInstance> BodyDissolveMaterial;
	UPROPERTY(EditDefaultsOnly,Category="Dissolve")
	TObjectPtr<UMaterialInstance> WeaponDissolveMaterial;

	
	
};

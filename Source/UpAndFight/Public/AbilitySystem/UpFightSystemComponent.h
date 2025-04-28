// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "Data/AbilityDataAsset.h"
#include "UpFightSystemComponent.generated.h"

class UUpFightSystemComponent; // временно чтобы ошибка не мазолила глаза и чтобы обьявление не опускать после класса

// делегат котоырй будет передавать Asset теги эффектов в Overlay Controller там если совпадают тег с тегом EffectMessage то вызовется он
DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTagsSignature,const FGameplayTagContainer& /*AssetTags*/)
// делегат котоырй будет передавать в Overlay Controller там будет запускаться Инцилизация стартовых абилок для вывода их иконок на экран
DECLARE_MULTICAST_DELEGATE(FAbilityGivenSignature)
// делегат который будет сообщать, что нужно сделать BroadCast для SpellMenu
DECLARE_MULTICAST_DELEGATE(FSpellMenuUpdateDataSignature)
// делегат который будет передавать AbilityInfo с заклинанием
DECLARE_MULTICAST_DELEGATE_OneParam(FAbilityInfoServerSignature,const FAbilityInfo& AbilityInfo /*AssetTags*/)
// делегат который будет передавать старый inputTag в контроллер overlay и SpellMenu, чтобы чистить старые глобусы
DECLARE_MULTICAST_DELEGATE_OneParam(FClearOldSpellGLobeServerSignatyre, const FGameplayTag PastInputTag)
UCLASS()
class UPANDFIGHT_API UUpFightSystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
public:
	// функция будет вызываться в персонаже героя и врага, она привязывает делегата к выхову нашей EffectApplied
	UFUNCTION()
	void AbilityActorInfoSet();
	// переберем классы всех GameplayAbilities стартовых для игрока/врага и сделаем GiveAbility
	void AddCharacterStartupAbilities(TArray<TSubclassOf<UGameplayAbility>> StartedGameplayAbilities);
	void AddAndActivatePassiveAbilities(TArray<TSubclassOf<UGameplayAbility>> PassiveGameplayAbilities);
	void AddCharacterAbilities(TSubclassOf<UGameplayAbility> GameplayAbility);
	
	void AbilityInputTagHeld(FGameplayTag& GameplayTag);
	void AbilityInputTagReleased(FGameplayTag& GameplayTag);

	void UpgradeAttributes(const FGameplayTag& AttributeTag);
	UFUNCTION(Server,Reliable)
	void ServerUpgradeAttributes(const FGameplayTag& AttributeTag);
	UFUNCTION(Server,Reliable)
	void ServerUpgradeSpellPoint(const FGameplayTag& AbilityTag, const FGameplayTag& StatusTag);
	UFUNCTION(Client,Reliable)
	void ClientUpgradeSpellMenu();
	UFUNCTION(Server,Reliable)
	void InitializeAbilitiesForMenuControllers();

	UFUNCTION(Client,Reliable)
	void InitializeAbilitiesForMenuControllersForClient(const FAbilityInfo& AbilityInfo);
	void UpdateStatusAbilities(const int32 Level);
	// перетаскивания SpellGlobe на новое место 
	UFUNCTION(Server,Reliable)
	void ServerSpendEquipAbility(const FGameplayTag AbilityTag, const FGameplayTag NewInputTag);
	UFUNCTION(Client,Reliable)
	void ClientSpendEquipAbility();
	UFUNCTION(Client,Reliable)
	void ClientClearOldGlobe(FGameplayTag PastInputTag);

	bool GetSpellDescriptions(const FGameplayTag& AbilityTag, FString& OutSpellDescription,FString& OutNextLevelSpellDescription);
	
	FAbilityInfoServerSignature AbilityInfoServerDelegate;
	
	FGameplayTag GetAbilityTagFromSpec(const FGameplayAbilitySpec& AbilitySpec);
	FGameplayTag GetInputTagFromSpec(const FGameplayAbilitySpec& AbilitySpec);
	FGameplayTag GetStatusTagFromSpec(const FGameplayAbilitySpec& AbilitySpec);

	FGameplayAbilitySpec* GetAbilitySpecByAbilityTag (const FGameplayTag AbilityTag);
	FGameplayAbilitySpec* GetAbilitySpecByInputTag (const FGameplayTag InInputTag);
	
	// экземпляр делегата передающий теги эффекта
	FEffectAssetTagsSignature EffectAssetTagsDelegate;
	// экземпляр делегата передающий UUpFightSystemComponent в OverlayController
	FAbilityGivenSignature AbilityGivenDelegate;
	// экземпляр делегата который будет сообщать, что нужно сделать BroadCast для SpellMenu
	FSpellMenuUpdateDataSignature SpellMenuUpdateDelegate;
	FClearOldSpellGLobeServerSignatyre ClearOldGlobeServerDelegate;

	// булевая которая будет проверяться в OverlayController для вывода иконок абилок
	bool bStartupAbilityGiven = false;
protected:
	// функция передающий через делегат EffectAssetTagsDelegate в OverlayController теги примененного эффекта для вызова EffectMessage если надо
	void EffectApplied (UAbilitySystemComponent* ASC, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle EffectHandle);

	// функция из AbilityComponent которая реплицируется после применения GetActivatableAbilities
	virtual void OnRep_ActivateAbilities() override;
};


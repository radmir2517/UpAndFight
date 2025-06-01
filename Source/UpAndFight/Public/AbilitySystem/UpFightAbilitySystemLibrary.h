// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UpFightAbilitySystemLibrary.generated.h"


class UAbilityDataAsset;
struct FGameplayEffectSpec;
struct FGameplayEffectContextHandle;
struct FDamageEffectParams;
class USpellWidgetController;
class ULevelUpInfo;
class UGameplayEffect;
struct FScalableFloat;
struct FGameplayTag;
class UAbilitySystemComponent;
enum class ECharacterClass : uint8;
class UCharacterClassInfo;
class UOverlayWidgetController;
class UUpFightAttributeMenuController;

UCLASS()
class UPANDFIGHT_API UUpFightAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, meta = (HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"), Category="UPFightAbilitySystemLibrary|WidgetController")
	static UOverlayWidgetController* GetOverlayWidgetController(const UObject* WorldContextObject);
	
	UFUNCTION(BlueprintPure, meta = (HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"), Category="UPFightAbilitySystemLibrary|WidgetController")
	static UUpFightAttributeMenuController* GetAttributeMenuController(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, meta = (HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"), Category="UPFightAbilitySystemLibrary|WidgetController")
	static USpellWidgetController* GetSpellMenuController(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, meta = (HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"), Category="UPFightAbilitySystemLibrary|CharacterInfo")
	static UCharacterClassInfo* GetCharacterClassInfo(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure,meta = (HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"), Category="UPFightAbilitySystemLibrary|CharacterInfo")
	static ULevelUpInfo* GetLevelUpInfo(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure,meta = (HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"), Category="UPFightAbilitySystemLibrary|CharacterInfo")
	static UAbilityDataAsset* GetAbilityInfo(const UObject* WorldContextObject);

	

	/*
	 * Ability System Startup
	 */
	// функция инициализации Primary,Secondary,Vital атрибутов для RPG классов
	UFUNCTION(BlueprintCallable,Category="AuraAbilitySystemLibrary|DefaultAttributes")
	static void InitializeDefaultAttributes(const UObject* WorldContextObject, ECharacterClass CharacterClass, UAbilitySystemComponent* ASC, float Level);
	// достанем из AbilityClassInfo common абилки и активируем их(GA_HitReact)
	UFUNCTION(BlueprintCallable, Category="UPFightAbilitySystemLibrary|CommonAttributes")
	static void GiveStartupAbilities(const UObject* WorldContextObject, UAbilitySystemComponent* ASC, ECharacterClass& Class);
	// вернем врагов цели в определенном радиусе
	UFUNCTION(BlueprintCallable, Category="UPFightAbilitySystemLibrary|CommonAttributes")
	static void GetLiveActorsFromRadius(const UObject* WorldContextObject, const TArray<AActor*>& IgnoreActors,TArray<AActor*>& ActorsToOut, const float InRadius, const FVector& Origin);
	UFUNCTION(BlueprintPure, Category="UPFightAbilitySystemLibrary|CommonAttributes")
	static bool AreTheyFriends(const AActor* FirstActor, const AActor* SecondActor);
	/*
	 * Gameplay Effect 
	 */
	UFUNCTION(BlueprintCallable, Category="UPFightAbilitySystemLibrary|GameplayEffect")
	static FGameplayEffectContextHandle UpFightApplyGameplayEffect(const FDamageEffectParams& DamageEffectParams);
	UFUNCTION(BlueprintPure, Category="UPFightAbilitySystemLibrary|GameplayEffect")
	static bool IsSuccessfulDebuff(const FGameplayEffectContextHandle& EffectContextHandle);
	UFUNCTION(BlueprintPure, Category="UPFightAbilitySystemLibrary|GameplayEffect")
	static float GetDebuffDamage(const FGameplayEffectContextHandle& EffectContextHandle);
	UFUNCTION(BlueprintPure, Category="UPFightAbilitySystemLibrary|GameplayEffect")
	static float GetDebuffDuration(const FGameplayEffectContextHandle& EffectContextHandle);
	UFUNCTION(BlueprintPure, Category="UPFightAbilitySystemLibrary|GameplayEffect")
	static float GetDebuffFrequency(const FGameplayEffectContextHandle& EffectContextHandle);
	static TSharedPtr<FGameplayTag> GetDamageType(const FGameplayEffectContextHandle& EffectContextHandle);
	// получим импульс смерти в при применении заклинание шара GetActorForwardVector * GetDeathImpulseMagnitude
	UFUNCTION(BlueprintPure, Category="UPFightAbilitySystemLibrary|GameplayEffect")
	static FVector GetDeathVector(const FGameplayEffectContextHandle& EffectContextHandle);
	
	UFUNCTION(BlueprintCallable, Category="UPFightAbilitySystemLibrary|GameplayEffect")
	static void SetSuccessDebuff(FGameplayEffectContextHandle& EffectContextHandle, bool InIsSuccessfulDebuff);
	UFUNCTION(BlueprintCallable, Category="UPFightAbilitySystemLibrary|GameplayEffect")
	static void SetDebuffDamage(FGameplayEffectContextHandle& EffectContextHandle, float InDamage);
	UFUNCTION(BlueprintCallable, Category="UPFightAbilitySystemLibrary|GameplayEffect")
	static void SetDebuffDuration(FGameplayEffectContextHandle& EffectContextHandle, float InDuration);
	UFUNCTION(BlueprintCallable, Category="UPFightAbilitySystemLibrary|GameplayEffect")
	static void SetDebuffFrequency(FGameplayEffectContextHandle& EffectContextHandle, float InFrequency);
	UFUNCTION(BlueprintPure, Category="UPFightAbilitySystemLibrary|GameplayEffect")
	static void SetDamageType(FGameplayEffectContextHandle& EffectContextHandle,const FGameplayTag& InDamageType);
	// зададим импульс смерти в при применении заклинание шара GetActorForwardVector * GetDeathImpulseMagnitude
	UFUNCTION(BlueprintPure, Category="UPFightAbilitySystemLibrary|GameplayEffect")
	static void SetDeathImpulse(FGameplayEffectContextHandle& EffectContextHandle,const FVector& InDeathImpulse);
	/*
	 * Gameplay Mechanics
	 */
	UFUNCTION(BlueprintPure, Category="UPFightAbilitySystemLibrary|GameplayMechanics")
	static int32 GetXPRewardForClassAndLevel(const UObject* WorldContextObject, const ECharacterClass& Class, const int32 Level);

	
	
};


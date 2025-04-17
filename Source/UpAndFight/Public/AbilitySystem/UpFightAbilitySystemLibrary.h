// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UpFightAbilitySystemLibrary.generated.h"


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
	UFUNCTION(BlueprintCallable, Category="UPFightAbilitySystemLibrary|CommonAttributes")
	static void UpFightApplyGameplayEffect(TSubclassOf<UGameplayEffect> EffectClass, AActor* SourceActor, AActor* TargetActor, TMap<FGameplayTag, FScalableFloat> EffectTypes, float Level);
	/*
	 * Gameplay Mechanics
	 */
	UFUNCTION(BlueprintPure, Category="UPFightAbilitySystemLibrary|GameplayMechanics")
	static int32 GetXPRewardForClassAndLevel(const UObject* WorldContextObject, const ECharacterClass& Class, const int32 Level);

	
	
};


// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UpFightAbilitySystemLibrary.generated.h"


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
	UFUNCTION(BlueprintPure, Category="UPFightAbilitySystemLibrary|WidgetController")
	static UOverlayWidgetController* GetOverlayWidgetController(const UObject* WorldContextObject);
	UFUNCTION(BlueprintPure, Category="UPFightAbilitySystemLibrary|WidgetController")
	static UUpFightAttributeMenuController* GetAttributeMenuController(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category="UPFightAbilitySystemLibrary|CharacterInfo")
	static UCharacterClassInfo* GetCharacterClassInfo(const UObject* WorldContextObject);

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
	static TArray<AActor*> GetLiveActorsFromRadius(const UObject* WorldContextObject, const AActor* SourceActor, const FVector& InLocation, const float InRadius);

	UFUNCTION(BlueprintCallable, Category="UPFightAbilitySystemLibrary|CommonAttributes")
	static bool AreTheyFriends(const AActor* SourceActor, const AActor* TargetActor);

	/*
	 * Gameplay Effect 
	 */
	UFUNCTION(BlueprintCallable, Category="UPFightAbilitySystemLibrary|CommonAttributes")
	static void UpFightApplyGameplayEffect(TSubclassOf<UGameplayEffect> EffectClass, AActor* SourceActor, AActor* TargetActor, TMap<FGameplayTag, FScalableFloat> EffectTypes, float Level);
};


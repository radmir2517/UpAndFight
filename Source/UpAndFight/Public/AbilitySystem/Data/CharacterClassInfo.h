// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CharacterClassInfo.generated.h"

class UGameplayAbility;
class UGameplayEffect;


UENUM(Blueprintable,BlueprintType)
enum class ECharacterClass : uint8
{
	Elementalist,
	Ranger,
	Warrior
};

// структура для RPG - класса персонажей, содержит эффект главных атрибутов и атакующих абилок 
USTRUCT(BlueprintType)
struct FCharacterClassDefaultInfo
{
	GENERATED_BODY()
 
	UPROPERTY(EditDefaultsOnly, Category="CharacterClass")
	TSubclassOf<UGameplayEffect> PrimaryAttributes;

	UPROPERTY(EditDefaultsOnly, Category="CharacterClass")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;
	
};

UCLASS()
class UPANDFIGHT_API UCharacterClassInfo : public UDataAsset
{
	GENERATED_BODY()
public:
	
	FCharacterClassDefaultInfo GetCharacterClassInfoByEnum(const ECharacterClass& inClass);
	
	UPROPERTY(EditDefaultsOnly, Category="Character Class Defaults")
	TMap<ECharacterClass, FCharacterClassDefaultInfo> CharacterClassInformation;
	
	UPROPERTY(EditDefaultsOnly,Category="Character Class Defaults")
	TSubclassOf<UGameplayEffect> SecondaryAttributesEffectClass;
	
	UPROPERTY(EditDefaultsOnly,Category="Character Class Defaults")
	TSubclassOf<UGameplayEffect> VitalAttributesEffectClass;
	// сюда будет входит HitReact например
	UPROPERTY(EditDefaultsOnly,Category="Character Class Defaults")
	TArray<TSubclassOf<UGameplayAbility>> CommonAbilities;
};

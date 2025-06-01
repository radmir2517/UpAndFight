// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "GameplayEffectTypes.h"
#include "UpFightAbilityTypes.generated.h"

class UGameplayEffect;

USTRUCT(BlueprintType)
struct FDamageEffectParams
{// структура для быстрой передачи и назначения параметров// структура хранящая параметры для создания эффекта Damage и также параметры дебаффа
	FDamageEffectParams(){};
	
	GENERATED_BODY()
	UPROPERTY()
	TObjectPtr<UObject> WoldContextObject = nullptr;
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> SourceAbilitySystemComponent = nullptr;
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> TargetAbilitySystemComponent = nullptr;
	UPROPERTY()
	TSubclassOf<UGameplayEffect> GameplayEffectClass = nullptr;

	UPROPERTY()
	TMap<FGameplayTag, float> DamageTagAndValue = {};
	UPROPERTY()
	int32 AbilityLevel = 1;
	// добавляем параметры дебаффа
	UPROPERTY()
	float DebuffDamage = 0.f;
	UPROPERTY()
	float DebuffChance = 0.f;
	UPROPERTY()
	float DebuffFrequency = 0.f;
	UPROPERTY()
	float DebuffDuration = 0.f;
	UPROPERTY()
	FVector DeathImpulse = FVector::ZeroVector;
	UPROPERTY()
	float DeathImpulseMagnitude = 0.f;
};


USTRUCT(BlueprintType)
struct FUpFightGameplayEffectContext : public FGameplayEffectContext
{
	GENERATED_BODY()
public:
	virtual bool NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess) override;

	/** Returns the actual struct used for serialization, subclasses must override this! */
	virtual UScriptStruct* GetScriptStruct() const
	{
		return FGameplayEffectContext::StaticStruct();
	}
	// геттеры и сеттеры для дебаффа
	bool IsSuccessfulDebuff() const {return bIsSuccessfulDebuff;}
	float GetDebuffDamage() const {return  DebuffDamage;}
	float GetDebuffDuration() const {return DebuffDuration;}
	float GetDebuffFrequency() const {return DebuffFrequency;}
	TSharedPtr<FGameplayTag> GetDamageType() const {return DamageType;}
	FVector GetDeathImpulse () const {return DeathImpulse;}
	float GetDeathImpulseMagnitude() const {return DeathImpulseMagnitude;}

	void SetIsSuccessfulDebuff(bool bIsSuccess) {bIsSuccessfulDebuff = bIsSuccess;}
	void SetDebuffDamage(float InDamage) {DebuffDamage = InDamage;}
	void SetDebuffDuration(float InDuration) {DebuffDuration = InDuration;}
	void SetDebuffFrequency(float InFrequency) {DebuffFrequency = InFrequency;}
	void SetDamageType(const TSharedPtr<FGameplayTag>& InDamageType) {DamageType = InDamageType;}
	void SetDeathImpulse(const FVector InDeath) {DeathImpulse = InDeath;}
	void SetDeathImpulseMagnitude(const float InDeathImpulseMagnitude) {DeathImpulseMagnitude = InDeathImpulseMagnitude;}
	
protected:
	// сюда мы может добавлять переменные который будет сериализовывать, например шанс крита или блока например
	// и потом его надо будет прописать в сериализацию
	//bool bIsBlocked = false;
	
	// булеан срабатывания дебаффа
	// добавляем параметры дебаффа
	UPROPERTY()
	bool bIsSuccessfulDebuff = false;
	UPROPERTY()
	float DebuffDamage = 0.f;
	UPROPERTY()
	float DebuffDuration = 0.f;
	UPROPERTY()
	float DebuffFrequency = 0.f;
	UPROPERTY()
	float DeathImpulseMagnitude = 0.f;
	// указатель на тег урона
	TSharedPtr<FGameplayTag> DamageType;

	// добавим импульс дебаффа
	UPROPERTY()
	FVector DeathImpulse = FVector::ZeroVector;
};

// используется для определения специальных свойств и поведения пользовательских структур для сетевой сериализации
// это пользовательская структура FAuraGameplayEffectContext будет поддерживать NetSerializer и копировать
template<>
struct TStructOpsTypeTraits< FUpFightGameplayEffectContext > : public TStructOpsTypeTraitsBase2< FUpFightGameplayEffectContext >
{
	enum
	{
		WithNetSerializer = true,
		WithCopy = true		// struct можно копировать с помощью оператора присваивания copy.
	};
};



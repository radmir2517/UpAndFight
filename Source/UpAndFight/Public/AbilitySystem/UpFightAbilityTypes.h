// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "GameplayEffectTypes.h"
#include "UpFightAbilityTypes.generated.h"

/**
 * 
 */
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
	
protected:
	// сюда мы может добавлять переменные который будет сериализовывать, например шанс крита или блока например
	// и потом его надо будет прописат ьв сериализацию
	//bool bIsBlocked = false;
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



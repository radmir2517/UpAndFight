// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "UpFightAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)
	
UCLASS()
class UPANDFIGHT_API UUpFightAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:

	UUpFightAttributeSet();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing="OnRep_Health", Category="Vital Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UUpFightAttributeSet,Health);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing="OnRep_MaxHealth", Category="Vital Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UUpFightAttributeSet,MaxHealth);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing="OnRep_Mana", Category="Vital Attributes")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UUpFightAttributeSet,Mana);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing="OnRep_MaxMana", Category="Vital Attributes")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UUpFightAttributeSet,MaxMana);
	
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldValue) const;

	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldValue) const;

	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldValue) const;

	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldValue) const;
};

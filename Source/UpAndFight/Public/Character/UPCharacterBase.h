// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "UPCharacterBase.generated.h"

class UAttributeSet;
// сделаем класс абстрактным, чтобы нельзя было его создать
UCLASS(Abstract)
class UPANDFIGHT_API AUPCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AUPCharacterBase();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	
protected:
	virtual void BeginPlay() override;
	
	// создадим оружие
	UPROPERTY(VisibleAnywhere, Category="Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
};

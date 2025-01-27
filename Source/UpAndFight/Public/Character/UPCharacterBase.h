// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "UPCharacterBase.generated.h"
// сделаем класс абстрактным, чтобы нельзя было его создать
UCLASS(Abstract)
class UPANDFIGHT_API AUPCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	AUPCharacterBase();

protected:
	virtual void BeginPlay() override;
	// создадим оружие
	UPROPERTY(VisibleAnywhere, Category="Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;
};

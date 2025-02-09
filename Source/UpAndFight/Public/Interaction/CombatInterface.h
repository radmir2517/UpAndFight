// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CombatInterface.generated.h"

UINTERFACE(MinimalAPI)
class UCombatInterface : public UInterface
{
	GENERATED_BODY()
};

class UPANDFIGHT_API ICombatInterface
{
	GENERATED_BODY()

public:
	// функция ICombatInterface по получению уровня
	UFUNCTION(BlueprintNativeEvent)
	int32 GetPlayerLevel();
	
	UFUNCTION(BlueprintNativeEvent)
	FVector GetSocketWeapon();
};

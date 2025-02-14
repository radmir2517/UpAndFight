// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "GameFramework/GameModeBase.h"
#include "UpFightGameMode.generated.h"

/**
 * 
 */
UCLASS()
class UPANDFIGHT_API AUpFightGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category="GameMode")
	TObjectPtr<UCharacterClassInfo> CharacterClassInfo;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LevelUpInfo.generated.h"


USTRUCT(Blueprintable)
struct FLevelInfo
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly,Category="LevelUpInfo")
	int32 XPForThisLevel;
	
	UPROPERTY(EditDefaultsOnly,Category="LevelUpInfo")
	int32 AttributePointReward = 1;
	
	UPROPERTY(EditDefaultsOnly,Category="LevelUpInfo")
	int32 SpellPointReward = 1;
};

UCLASS()
class UPANDFIGHT_API ULevelUpInfo : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly,Category="LevelUpInfo")
	TArray<FLevelInfo> LevelUpInfos;

	UFUNCTION(BlueprintCallable)
	int32 GetLevelByXp(int32 inXP);
	
};

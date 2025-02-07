// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "UpFightInputConfig.generated.h"


class UInputAction;

USTRUCT(Blueprintable,BlueprintType)
struct FUpFightInputAction
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> InputAction;
	
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag InputTag;
	
};

UCLASS()
class UPANDFIGHT_API UUpFightInputConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	TArray<FUpFightInputAction> InputActions;
};

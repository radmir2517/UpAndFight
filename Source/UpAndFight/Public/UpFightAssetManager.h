// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "UpFightAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class UPANDFIGHT_API UUpFightAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
	UUpFightAssetManager& InitializeUpFightAssetManage();

protected:
	virtual void StartInitialLoading() override;
	
};

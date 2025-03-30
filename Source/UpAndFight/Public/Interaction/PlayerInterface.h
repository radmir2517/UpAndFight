// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PlayerInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPlayerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class UPANDFIGHT_API IPlayerInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	int32 GetXP();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	int32 GetAttributePoints();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	int32 GetSpellPoints();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void AddXPReward(float Reward);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void AddPlayerLevel(int32 inLevel);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void AddToAttributePoints(int32 Points);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void AddToSpellPoints(int32 Points);
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EnemyInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI,BlueprintType)
class UEnemyInterface : public UInterface
{
	GENERATED_BODY()
};

class UPANDFIGHT_API IEnemyInterface
{
	GENERATED_BODY()

public:
	// функция выделения актера
	virtual void HighlightActor() = 0;
	// функция убирания выделения актера
	virtual void UnHighlightActor() = 0;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/UPCharacterBase.h"
#include "UPCharacter.generated.h"

/**
 * 
 */
UCLASS()
class UPANDFIGHT_API AUPCharacter : public AUPCharacterBase
{
	GENERATED_BODY()

public:
	AUPCharacter();
	void InitOverlay();

	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	// сообщаем кто avatar actor и кто Owner
	void InitAbilityInfo() override;

};



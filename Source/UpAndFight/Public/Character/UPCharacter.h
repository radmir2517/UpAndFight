// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/UPCharacterBase.h"
#include "Interaction/CombatInterface.h"
#include "UPCharacter.generated.h"

class AUpFightPlayerState;
class UGameplayEffect;
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

	/* CombatInterface */
	
	// функция ICombatInterface по получению уровня
	virtual int32 GetPlayerLevel_Implementation() override;
	
	/* end CombatInterface*/
protected:
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<AUpFightPlayerState> UpFightPlayerState;
	
};



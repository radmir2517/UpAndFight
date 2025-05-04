// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/UPCharacterBase.h"
#include "Interaction/CombatInterface.h"
#include "Interaction/PlayerInterface.h"
#include "UPCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class AUpFightPlayerState;
class UGameplayEffect;
/**
 * 
 */


UCLASS()
class UPANDFIGHT_API AUPCharacter : public AUPCharacterBase, public IPlayerInterface
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

	/* PlayerInterface */
	virtual int32 GetXP_Implementation() override;
	virtual void AddXPReward_Implementation(float Reward) override;
	virtual void AddPlayerLevel_Implementation(int32 InLevel) override;
	virtual void AddToAttributePoints_Implementation(int32 Points) override;
	virtual void AddToSpellPoints_Implementation(int32 Points) override;
	virtual int32 GetAttributePoints_Implementation() override;
	virtual int32 GetSpellPoints_Implementation() override;
	/* end PlayerInterface */

	
protected:
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<AUpFightPlayerState> UpFightPlayerState;

	// эффект повышения уровня
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TObjectPtr<UNiagaraSystem> LevelUpEffect;

	// эффект повышения уровня
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	// эффект повышения уровня
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TObjectPtr<UCameraComponent> CameraComponent;

	UFUNCTION(NetMulticast, Reliable)
	void MulticastLevelUpEffect();

	void AddCharacterAbilitiesFromAbilityInfo();
};



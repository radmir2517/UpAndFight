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
class UPANDFIGHT_API AUPCharacter : public AUPCharacterBase, public ICombatInterface
{
	GENERATED_BODY()

public:
	AUPCharacter();
	void InitOverlay();

	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	// включим эффект первичных атрибутов
	
	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level);
	// включим эффект первичных атрибутов
	void InitializeSecondaryAttributes();
	void InitializeDefaultAttributes();
	// сообщаем кто avatar actor и кто Owner
	void InitAbilityInfo() override;

	/* CombatInterface */
	
	// функция ICombatInterface по получению уровня
	virtual int32 GetPlayerLevel() override;
	
	/* end CombatInterface*/
protected:
	UPROPERTY(EditDefaultsOnly,Category="Attributes")
	TSubclassOf<UGameplayEffect> PrimaryAttributesEffectClass;
	UPROPERTY(EditDefaultsOnly,Category="Attributes")
	TSubclassOf<UGameplayEffect> SecondaryAttributesEffectClass;
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<AUpFightPlayerState> UpFightPlayerState;

private:
	// применения эффекта с атрибутами Primary and Secondary
	void InitializePrimaryAttributes();
};



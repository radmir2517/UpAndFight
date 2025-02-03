// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/UPCharacterBase.h"
#include "Interaction/CombatInterface.h"
#include "Interaction/EnemyInterface.h"
#include "UPEnemy.generated.h"

/**
 * 
 */
UCLASS()
class UPANDFIGHT_API AUPEnemy : public AUPCharacterBase, public IEnemyInterface, public ICombatInterface
{
	GENERATED_BODY()
public:

	AUPEnemy();

	virtual void BeginPlay() override;

	virtual void InitAbilityInfo() override;
	// функция выделения актера
	virtual void HighlightActor() override;
	// функция убирания выделения актера
	virtual void UnHighlightActor() override;
	
	/* CombatInterface */
	// функция ICombatInterface по получению уровня
	virtual int32 GetPlayerLevel() override;
	/* end CombatInterface */

	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Character Class Default")
	int32 Level = 1;

};

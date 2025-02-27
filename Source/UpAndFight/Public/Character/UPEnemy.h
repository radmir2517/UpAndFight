// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/UPCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "UI/WidgetController/EnemyWidgetController.h"
#include "UPEnemy.generated.h"


class UBlackboardComponent;
class UBehaviorTree;
class UUpFightUserWidget;
class UWidgetComponent;
/**
 * 
 */
UCLASS()
class UPANDFIGHT_API AUPEnemy : public AUPCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()
public:

	AUPEnemy();

	virtual void BeginPlay() override;

	virtual void PossessedBy(AController* NewController) override;

	virtual void InitAbilityInfo() override;
	// функция выделения актера
	virtual void HighlightActor_Implementation() override;
	// функция убирания выделения актера
	virtual void UnHighlightActor_Implementation() override;

	UFUNCTION(BlueprintCallable)
	UEnemyWidgetController* GetEnemyWidgetController();

	void InitEnemyWidget();
	/* CombatInterface */
	// функция ICombatInterface по получению уровня
	virtual int32 GetPlayerLevel_Implementation() override;
	//virtual void Die_Implementation() override;
	/* end CombatInterface */

	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UWidgetComponent> HealthWidgetComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UUpFightUserWidget> HeathWidget;
	/*
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UWidgetComponent> DamageWidgetComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UUpFightUserWidget> DamageWidget;
	*/

	
protected:

	void HitReactTagChanged(FGameplayTag Tag, int32 Count);

	
	TObjectPtr<UEnemyWidgetController> EnemyWidgetController;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UEnemyWidgetController> EnemyWidgetControllerClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUpFightUserWidget> EnemyHealthWidgetClass;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UBehaviorTree> BehaviorTree;

	TObjectPtr<UBlackboardComponent> BlackBoardComponent;


	
	bool bHitReacting = false;
};


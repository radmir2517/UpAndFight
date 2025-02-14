// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/UPCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "UI/WidgetController/EnemyWidgetController.h"
#include "UPEnemy.generated.h"


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
	/* end CombatInterface */

	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UWidgetComponent> HealthWidgetComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UUpFightUserWidget> HeathWidget;


	
protected:
	
	TObjectPtr<UEnemyWidgetController> EnemyWidgetController;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UEnemyWidgetController> EnemyWidgetControllerClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUpFightUserWidget> EnemyWidgetClass;
};

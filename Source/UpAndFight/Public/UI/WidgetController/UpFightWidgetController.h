// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "UpFightWidgetController.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;

// структура которая будет принимать несколько переменных, чтобы удобнее было инициализировать
USTRUCT(BlueprintType)
struct FWidgetControllerParams
{
	GENERATED_BODY()
	// конструктор который принимает нужные переменные для контроллера
	FWidgetControllerParams(){};
	FWidgetControllerParams(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
		: PlayerController(PC), PlayerState(PS), AbilitySystemComponent(ASC), AttributeSet(AS)   {}
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UAttributeSet> AttributeSet;
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<APlayerState> PlayerState;
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<APlayerController> PlayerController;
};

UCLASS(BlueprintType,Blueprintable)
class UPANDFIGHT_API UUpFightWidgetController : public UObject
{
	GENERATED_BODY()

public:
	
	virtual void BindCallBacksToDependencies();
	UFUNCTION(BlueprintCallable)
	virtual void BroadcastInitialValues();
	
	// сеттер который назначает переменные из структуры Params
	void SetWidgetControllerParams(const FWidgetControllerParams& Params);

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UAttributeSet> AttributeSet;
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<APlayerState> PlayerState;
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<APlayerController> PlayerController;
};

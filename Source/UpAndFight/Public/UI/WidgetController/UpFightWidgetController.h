// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/Data/AbilityDataAsset.h"
#include "UpFightWidgetController.generated.h"

class AUpFightPlayerController;
class AUpFightPlayerState;
class UUpFightAttributeSet;
class UUpFightSystemComponent;
class ULevelUpInfo;
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

// делегат который будет возвращать информацию об абилках готовых к активации в OverlayController
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAbilityInfoSignature,const FAbilityInfo&, Info);

UCLASS(BlueprintType,Blueprintable)
class UPANDFIGHT_API UUpFightWidgetController : public UObject
{
	GENERATED_BODY()

public:
	
	virtual void BindCallBacksToDependencies();
	UFUNCTION(BlueprintCallable)
	virtual void BroadcastInitialValues();
	// функция получения GetActivatableAbilities и получения структуры с AbilityDataAsset по тегу и отправлению струтктуры через делегат в виджет
	UFUNCTION(BlueprintCallable)
	virtual void OnInitializeStartupAbilities();
	// сеттер который назначает переменные из структуры Params
	void SetWidgetControllerParams(const FWidgetControllerParams& Params);

	// геттера для указателей
	UFUNCTION(BlueprintCallable)
	UUpFightSystemComponent* GetUpAbilitySystemComponent();
	UFUNCTION(BlueprintCallable)
	UUpFightAttributeSet* GetUpAttributeSet();
	UFUNCTION(BlueprintCallable)
	AUpFightPlayerState* GetUpPlayerState();
	UFUNCTION(BlueprintCallable)
	AUpFightPlayerController* GetUpPlayerController();
	

	// делегат который будет возвращать информацию об абилках готовых к активации в OverlayController
	UPROPERTY(BlueprintAssignable)
	FAbilityInfoSignature AbilityInfoDelegate;
		
	UPROPERTY(EditDefaultsOnly, Category="Widget Data")
	TObjectPtr<ULevelUpInfo> LevelUpIfInfoAsset;

	UPROPERTY(EditDefaultsOnly, Category="Widget Data")
	TObjectPtr<UAbilityDataAsset> AbilityDataAsset;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UAttributeSet> AttributeSet;
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<APlayerState> PlayerState;
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<APlayerController> PlayerController;


	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UUpFightSystemComponent> UpAbilitySystemComponent;
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UUpFightAttributeSet> UpAttributeSet;
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<AUpFightPlayerState> UpPlayerState;
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<AUpFightPlayerController> UpPlayerController;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "UpFightPlayerState.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;

UCLASS()
class UPANDFIGHT_API AUpFightPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
public:

	AUpFightPlayerState();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	void SetPlayerLevel(int32 InLevel) {Level = InLevel;}
	int32 GetPlayerLevel() const {return Level;}
protected:
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing= OnRep_Level)
	int32 Level = 1;
	
	UFUNCTION()
	void OnRep_Level(const int32& OldValue) const ;
};

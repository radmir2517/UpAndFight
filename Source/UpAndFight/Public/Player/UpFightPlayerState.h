// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "UpFightPlayerState.generated.h"

class UUpFightSystemComponent;
class UAttributeSet;
class UAbilitySystemComponent;


DECLARE_MULTICAST_DELEGATE_OneParam(FPlayerStateChangedSignature,int32 /*Value*/);

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
	TObjectPtr<UUpFightSystemComponent> AbilitySystemComponent;
	
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	FPlayerStateChangedSignature OnLevelHangedDelegate;

	FPlayerStateChangedSignature OnXPChangedDelegate;

	FPlayerStateChangedSignature OnAttributePointsDelegate;

	FPlayerStateChangedSignature OnSpellPointsDelegate;
		
	FORCEINLINE int32 GetPlayerLevel() const {return Level;}
	FORCEINLINE int32 GetXP() const {return XP;}
	FORCEINLINE int32 GetAttributePoints() const {return AttributePoints;}
	FORCEINLINE int32 GetSpellPoints() const {return SpellPoints;}
	
	void SetPlayerLevel(int32 InLevel) ;
	void SetXP(int32 InXP);
	UFUNCTION(BlueprintCallable)
	void AddXP(int32 InXP);
	UFUNCTION(BlueprintCallable)
	void AddPlayerLevel(int32 InLevel);
	UFUNCTION(BlueprintCallable)
	void AddAttributePoints(int32 InAttributePoints);
	UFUNCTION(BlueprintCallable)
	void AddSpellPoints(int32 InSpellPoints);
protected:
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing= OnRep_Level)
	int32 Level = 1;
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing= OnRep_XP)
	int32 XP = 0;
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing= OnRep_SpellPoints)
	int32 SpellPoints = 0;
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing= OnRep_AttributePoints)
	int32 AttributePoints = 0;
	
	
	UFUNCTION()
	void OnRep_Level(const int32& OldValue) const ;
	UFUNCTION()
	void OnRep_XP(const int32& OldValue) const ;
	UFUNCTION()
	void OnRep_SpellPoints(const int32& OldValue) const;
	UFUNCTION()
	void OnRep_AttributePoints(const int32& OldValue) const;
};

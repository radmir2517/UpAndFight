// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/UpFightPlayerState.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/UpFightAttributeSet.h"
#include "AbilitySystem/UpFightSystemComponent.h"
#include "Net/UnrealNetwork.h"

AUpFightPlayerState::AUpFightPlayerState()
{
	// Частота обновления серверов клиента
	SetNetUpdateFrequency(100.f);

	// создадим компонент AbilitySystemComponent и сделаем его реплицируемым
	AbilitySystemComponent = CreateDefaultSubobject<UUpFightSystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);	// Сделаем его реплицуемым
	AttributeSet = CreateDefaultSubobject<UUpFightAttributeSet>("AttributeSet");
	// режим мультипликации смешанный, игровые эффекты реплицированны
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	AbilitySystemComponent->SetIsReplicated(true);
}

UAbilitySystemComponent* AUpFightPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAttributeSet* AUpFightPlayerState::GetAttributeSet() const
{
	return AttributeSet;
}

void AUpFightPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AUpFightPlayerState,Level);
	DOREPLIFETIME(AUpFightPlayerState,XP);
	DOREPLIFETIME(AUpFightPlayerState,AttributePoints);
	DOREPLIFETIME(AUpFightPlayerState,SpellPoints);
}


void AUpFightPlayerState::SetPlayerLevel(int32 InLevel)
{
	Level = InLevel;
	OnLevelHangedDelegate.Broadcast(Level);
}

void AUpFightPlayerState::SetXP(int32 InXP)
{
	XP = InXP;
	OnXPChangedDelegate.Broadcast(XP);
}

void AUpFightPlayerState::AddXP(int32 InXP)
{
	XP += InXP;
	OnXPChangedDelegate.Broadcast(XP);
}

void AUpFightPlayerState::AddPlayerLevel(int32 InLevel)
{
	Level += InLevel;
	OnLevelHangedDelegate.Broadcast(Level);
	GEngine->AddOnScreenDebugMessage(5,3.f,FColor::Green,FString::Printf(TEXT("Player Level: %i"),Level));
}

void AUpFightPlayerState::AddAttributePoints(int32 InAttributePoints)
{
	AttributePoints += InAttributePoints;
	OnAttributePointsDelegate.Broadcast(AttributePoints);
}

void AUpFightPlayerState::AddSpellPoints(int32 InSpellPoints)
{
	SpellPoints += InSpellPoints;
	OnSpellPointsDelegate.Broadcast(SpellPoints);
}

void AUpFightPlayerState::OnRep_Level(const int32& OldValue) const
{
	// Это работает лишь в AttributeSet, тут задача как передать ее клиенту, передадим через делегат.
	//GAMEPLAYATTRIBUTE_REPNOTIFY(AUpFightPlayerState,Level,OldValue);

	OnLevelHangedDelegate.Broadcast(Level);
}

void AUpFightPlayerState::OnRep_XP(const int32& OldValue) const
{
	OnXPChangedDelegate.Broadcast(XP);
}

void AUpFightPlayerState::OnRep_SpellPoints(const int32& OldValue) const
{
	OnSpellPointsDelegate.Broadcast(SpellPoints);
}

void AUpFightPlayerState::OnRep_AttributePoints(const int32& OldValue) const
{
	OnAttributePointsDelegate.Broadcast(AttributePoints);
}

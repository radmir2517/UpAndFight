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
}

void AUpFightPlayerState::OnRep_Level(const int32& OldValue) const
{
	//GAMEPLAYATTRIBUTE_REPNOTIFY(AUpFightPlayerState,Level,OldValue);
}

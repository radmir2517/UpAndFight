// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/UPCharacterBase.h"

#include "AbilitySystemComponent.h"
#include "GameplayEffectTypes.h"
#include "Interaction/CombatInterface.h"


AUPCharacterBase::AUPCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;
	// создадим оружие иназначим на сокет руки и уберем коллизию
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), "WeaponHandSocket");
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

UAbilitySystemComponent* AUPCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AUPCharacterBase::InitAbilityInfo()
{
}

void AUPCharacterBase::InitializeDefaultAttributes()
{// применения эффекта с атрибутами Primary and Secondary, Vital
	InitializePrimaryAttributes();
	InitializeSecondaryAttributes();
	InitializeVitalAttributes();
}


void AUPCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AUPCharacterBase::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level)
{
	check(GameplayEffectClass)
	FGameplayEffectContextHandle EffectHandle = AbilitySystemComponent->MakeEffectContext();
	EffectHandle.AddSourceObject(this);
	FGameplayEffectSpecHandle EffectSpec = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffectClass,Level,EffectHandle);
	AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*EffectSpec.Data.Get());
}

void AUPCharacterBase::InitializePrimaryAttributes()
{// включим эффект первичных атрибутов
	ICombatInterface* CombatInterface = Cast<ICombatInterface>(this);
	ApplyEffectToSelf(PrimaryAttributesEffectClass, CombatInterface->GetPlayerLevel());
}

void AUPCharacterBase::InitializeSecondaryAttributes()
{// включим эффект вторичных атрибутов
	ICombatInterface* CombatInterface = Cast<ICombatInterface>(this);
	ApplyEffectToSelf(SecondaryAttributesEffectClass, CombatInterface->GetPlayerLevel());
}

void AUPCharacterBase::InitializeVitalAttributes()
{// включим эффект Vital атрибутов
	ICombatInterface* CombatInterface = Cast<ICombatInterface>(this);
	ApplyEffectToSelf(VitalAttributesEffectClass, CombatInterface->GetPlayerLevel());
}


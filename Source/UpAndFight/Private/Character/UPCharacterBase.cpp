// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/UPCharacterBase.h"

#include "AbilitySystemComponent.h"
#include "GameplayEffectTypes.h"
#include "AbilitySystem/UpFightSystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "Interaction/CombatInterface.h"


AUPCharacterBase::AUPCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;
	// создадим оружие иназначим на сокет руки и уберем коллизию
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), "WeaponHandSocket");
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera,ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera,ECR_Ignore);

	MotionWarping = CreateDefaultSubobject<UMotionWarpingComponent>("MotionWarpingComponent");
	
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

FVector AUPCharacterBase::GetSocketWeapon_Implementation()
{
	
	return Weapon->GetSocketLocation("TipSocket");
}

void AUPCharacterBase::UpdateMotionWarping_Implementation(const FVector& TargetLocation)
{
	MotionWarping->AddOrUpdateWarpTargetFromLocation("FacingTarget",TargetLocation);
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
	ApplyEffectToSelf(PrimaryAttributesEffectClass, ICombatInterface::Execute_GetPlayerLevel(this));
}

void AUPCharacterBase::InitializeSecondaryAttributes()
{// включим эффект вторичных атрибутов
	ApplyEffectToSelf(SecondaryAttributesEffectClass, ICombatInterface::Execute_GetPlayerLevel(this));
}

void AUPCharacterBase::InitializeVitalAttributes()
{// включим эффект Vital атрибутов
	ApplyEffectToSelf(VitalAttributesEffectClass, ICombatInterface::Execute_GetPlayerLevel(this));
}

void AUPCharacterBase::AddCharacterAbilities()
{	// проверим что это выполняет сервер и сделаем give ability
	if(!HasAuthority()) return;
	Cast<UUpFightSystemComponent>(AbilitySystemComponent)->AddCharacterAbilities(StartedGameplayAbilities);
}


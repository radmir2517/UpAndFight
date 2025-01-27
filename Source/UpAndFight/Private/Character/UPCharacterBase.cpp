// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/UPCharacterBase.h"


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


void AUPCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/UPEnemy.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/UpFightAttributeSet.h"
#include "AbilitySystem/UpFightSystemComponent.h"
#include "UpAndFight/UpAndFight.h"

AUPEnemy::AUPEnemy()
{
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility,ECR_Block);

	// создадим компонент AbilitySystemComponent и сделаем его реплицируемым
	AbilitySystemComponent = CreateDefaultSubobject<UUpFightSystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);	// Сделаем его реплицуемым
	AttributeSet = CreateDefaultSubobject<UUpFightAttributeSet>("AttributeSet");
	// режим мультипликации минималльный, т.к это ИИ и ему не нужно репликации эффектов
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	AbilitySystemComponent->SetIsReplicated(true);
}

void AUPEnemy::BeginPlay()
{
	Super::BeginPlay();
	// инцилизируем систему способностей у врага
	InitAbilityInfo();
}

void AUPEnemy::InitAbilityInfo()
{
	// сообщаем кто avatar actor и кто Owner
	AbilitySystemComponent->InitAbilityActorInfo(this,this);
	// вызов привязки делегата OnGameplayEffectAppliedToSelf к нашей функции в AbilitySystemComponent
	Cast<UUpFightSystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();
}

void AUPEnemy::HighlightActor_Implementation()
{
	GetMesh()->SetRenderCustomDepth(true);
	Weapon->SetRenderCustomDepth(true);
}

void AUPEnemy::UnHighlightActor_Implementation()
{
	GetMesh()->SetRenderCustomDepth(false);
	Weapon->SetRenderCustomDepth(false);
}

int32 AUPEnemy::GetPlayerLevel_Implementation()
{
	return Level;
}



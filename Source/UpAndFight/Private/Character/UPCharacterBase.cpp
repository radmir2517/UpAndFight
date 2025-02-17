// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/UPCharacterBase.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/UpFightAbilitySystemLibrary.h"
#include "AbilitySystem/UpFightSystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"


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


void AUPCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}


UAbilitySystemComponent* AUPCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AUPCharacterBase::InitAbilityInfo()
{
}

FVector AUPCharacterBase::GetSocketWeapon_Implementation()
{
	
	return Weapon->GetSocketLocation("TipSocket");
}

void AUPCharacterBase::UpdateMotionWarping_Implementation(const FVector& TargetLocation)
{
	MotionWarping->AddOrUpdateWarpTargetFromLocation("FacingTarget",TargetLocation);
}

UAnimMontage* AUPCharacterBase::GetHitReactMontage_Implementation()
{
	return HitReactMontage;
}



void AUPCharacterBase::Die_Implementation()
{
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MulticastHandleDeath();
}

void AUPCharacterBase::MulticastHandleDeath_Implementation()
{
	
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	GetMesh()->SetCollisionResponseToChannel(ECC_WorldStatic,ECR_Block);
	GetMesh()->SetSimulatePhysics(true);
	
	
	Weapon->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	Weapon->SetCollisionResponseToChannel(ECC_Pawn,ECR_Block);
	Weapon->SetCollisionResponseToChannel(ECC_WorldStatic,ECR_Block);
	Weapon->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	Weapon->SetSimulatePhysics(true);
	bDied = true;

	Dissolve();
}



void AUPCharacterBase::InitializeDefaultAttributes()
{	// применения эффекта с атрибутами Primary and Secondary, Vital
	if(!HasAuthority()){return;}
	UUpFightAbilitySystemLibrary::InitializeDefaultAttributes(this,CharacterClass,AbilitySystemComponent,Level);
}

void AUPCharacterBase::AddCharacterAbilities()
{	// проверим что это выполняет сервер и сделаем give ability
	if(!HasAuthority()) return;
	Cast<UUpFightSystemComponent>(AbilitySystemComponent)->AddCharacterAbilities(StartedGameplayAbilities);
}

void AUPCharacterBase::Dissolve()
{
	if(IsValid(BodyDissolveMaterial))
	{
		UMaterialInstanceDynamic* BodyInstanceDynamic = UMaterialInstanceDynamic::Create(BodyDissolveMaterial,this);
		GetMesh()->SetMaterial(0,BodyInstanceDynamic);
		StartBodyDissolveTimeline(BodyInstanceDynamic);
	}
	if(IsValid(WeaponDissolveMaterial))
	{
		UMaterialInstanceDynamic* WeaponInstanceDynamic = UMaterialInstanceDynamic::Create(WeaponDissolveMaterial,this);
		Weapon->SetMaterial(0,WeaponInstanceDynamic);
		StartWeaponDissolveTimeline(WeaponInstanceDynamic);	
	}

}






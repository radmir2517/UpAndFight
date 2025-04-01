// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/UPCharacterBase.h"

#include "AbilitySystemComponent.h"
#include "UpFightGameplayTags.h"
#include "AbilitySystem/UpFightAbilitySystemLibrary.h"
#include "AbilitySystem/UpFightSystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"


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

FVector AUPCharacterBase::GetSocketLocation_Implementation(const FGameplayTag& SocketTag)
{	// вернем местоположения сокета в зависимости от тега монтажа
	const FUpFightGameplayTags& UpTags = FUpFightGameplayTags::Get();
	if(SocketTag.MatchesTagExact(UpTags.SocketLocation_Weapon))
	{
		return Weapon->GetSocketLocation(WeaponSocketTipName);
	}
	else if(SocketTag.MatchesTagExact(UpTags.SocketLocation_LeftHand))
	{
		return GetMesh()->GetSocketLocation(LeftHandSocketTipName);
	}
	else if(SocketTag.MatchesTagExact(UpTags.SocketLocation_RightHand))
	{
		return GetMesh()->GetSocketLocation(RightHandSocketTipName);
	}
	else if(SocketTag.MatchesTagExact(UpTags.SocketLocation_Tail))
	{
		return GetMesh()->GetSocketLocation(TailSocketTipName);
	}
	UE_LOG(LogTemp,Error,TEXT("Check GetSocketLocation_Implementation, because it returns null"))
	return FVector();
}

void AUPCharacterBase::UpdateMotionWarping_Implementation(const FVector& TargetLocation)
{
	MotionWarping->AddOrUpdateWarpTargetFromLocation("TargetFacing",TargetLocation);
}

UAnimMontage* AUPCharacterBase::GetHitReactMontage_Implementation()
{
	return HitReactMontage;
}

TArray<FTaggedMontage> AUPCharacterBase::GetAttackMontages_Implementation()
{
	return AttackMontages;
}

void AUPCharacterBase::Die_Implementation()
{
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MulticastHandleDeath();
}

bool AUPCharacterBase::IsDead_Implementation()
{
	return bDead;
}

AActor* AUPCharacterBase::GetActor_Implementation()
{
	return this;
}

UNiagaraSystem* AUPCharacterBase::GetBloodEffect_Implementation()
{
	return BloodEffect;
}

FTaggedMontage AUPCharacterBase::GetTaggedMontageByTag_Implementation(const FGameplayTag& InMontageTag)
{	// вернем структуру
	for(FTaggedMontage Montage: AttackMontages)
	{
		if(Montage.MontageTag == InMontageTag)
		{
			return Montage;
		}
	}
	return FTaggedMontage();
}

void AUPCharacterBase::IncreaseMinionsCount_Implementation(int32 Amount)
{
	MinionsCount += Amount;
}

int32 AUPCharacterBase::GetMinionsCount_Implementation()
{
	return MinionsCount;
}

int32 AUPCharacterBase::GetMaxMinionsCount_Implementation()
{
	return MaxMinionsCount;
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
	// ABP будет подтягивать это значение и проверять надо ли перейти в пустой state
	bDead = true;
	// если этот персонаж был призван суммонером, то при смерти он отправит ему уменьшение числа текущих миньонов
	if(IsValid(GetInstigator()))
	{
		Execute_IncreaseMinionsCount(GetInstigator(),-1);
	}
	
	// воспроивзедения звука смерти
	if(IsValid(DeathSound))
	{
		UGameplayStatics::PlaySoundAtLocation(this,DeathSound,GetActorLocation(),FRotator::ZeroRotator);
	}
	Dissolve();

	SetLifeSpan(2.f);
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

void AUPCharacterBase::GiveAndActivatePassiveAbilities()
{
	if (!HasAuthority()) return;
	Cast<UUpFightSystemComponent>(AbilitySystemComponent)->AddAndActivatePassiveAbilities(PassiveGameplayAbilities);
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






// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/UpFightProjectileSpell.h"

#include "Actor/UpFightProjectile.h"
#include "Interaction/CombatInterface.h"
#include "Kismet/GameplayStatics.h"

void UUpFightProjectileSpell::SpawnProjectile()
{
	if(!HasAuthority(&CurrentActivationInfo)) return;
		
	FTransform ProjectileTransform;
	ProjectileTransform.SetLocation(ICombatInterface::Execute_GetSocketWeapon(GetAvatarActorFromActorInfo()));
	ProjectileTransform.SetRotation(GetAvatarActorFromActorInfo()->GetActorRotation().Quaternion());
	
	 AActor* CreatedActor = UGameplayStatics::BeginDeferredActorSpawnFromClass(this,
		ProjectileClass,
		ProjectileTransform,
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn,
		GetAvatarActorFromActorInfo());

	AUpFightProjectile* Projectile = Cast<AUpFightProjectile>(CreatedActor);
	
	Projectile->DamageEffectSpecHandle = MakeOutgoingGameplayEffectSpec(DamageEffect,1);
	Projectile->DamageEffectSpecHandle.Data->GetContext().AddSourceObject(GetAvatarActorFromActorInfo());
	
	UGameplayStatics::FinishSpawningActor(CreatedActor,ProjectileTransform);
}

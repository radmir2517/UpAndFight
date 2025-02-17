// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/UpFightProjectileSpell.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "UpFightGameplayTags.h"
#include "Actor/UpFightProjectile.h"
#include "Interaction/CombatInterface.h"
#include "Kismet/GameplayStatics.h"



void UUpFightProjectileSpell::SpawnProjectile(FVector InTargetLocation)
{
	// проверяем чтобы это делал сервер
	if(!GetAvatarActorFromActorInfo()->HasAuthority()) return;
	
	// создаем transform в посохе и пока направления игрока
	FTransform ProjectileTransform;
	FVector SocketLocation = ICombatInterface::Execute_GetSocketWeapon(GetAvatarActorFromActorInfo());
	ProjectileTransform.SetLocation(SocketLocation);
	// получаем направление шарика к цели
	FVector FromActorToTargetVector = InTargetLocation - SocketLocation;
	FromActorToTargetVector.Normalize();
	FRotator FromActorToTargetRotation = FromActorToTargetVector.Rotation();
	FromActorToTargetRotation.Pitch = 0.f;
	ProjectileTransform.SetRotation(FromActorToTargetRotation.Quaternion());
	
	// создаем отложенное спавн шарика
	AActor* CreatedActor = UGameplayStatics::BeginDeferredActorSpawnFromClass(this,
	   ProjectileClass,
	   ProjectileTransform,
	   ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn,
	   GetAvatarActorFromActorInfo());
	
	AUpFightProjectile* Projectile = Cast<AUpFightProjectile>(CreatedActor);
	const FUpFightGameplayTags& GameplayTags = FUpFightGameplayTags::Get();
	// в шарике создаем спецификацию эффекта и назначаем источник
	Projectile->DamageEffectSpecHandle = MakeOutgoingGameplayEffectSpec(DamageEffect,1);
	Projectile->DamageEffectSpecHandle.Data->GetContext().AddSourceObject(GetAvatarActorFromActorInfo());
	// пройдемся по всем типам урона которые есть в заклинание и присвоим им теги и урон
	for(auto Pair : DamageTypes)
	{
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(Projectile->DamageEffectSpecHandle,Pair.Key,Pair.Value.GetValueAtLevel(GetAbilityLevel()));
	}

	// досоздаем шарик
	UGameplayStatics::FinishSpawningActor(CreatedActor,ProjectileTransform);
}

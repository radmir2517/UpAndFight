// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/UpFightProjectileSpell.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "UpFightGameplayTags.h"
#include "AbilitySystem/UpFightAbilitySystemLibrary.h"
#include "Actor/UpFightProjectile.h"
#include "Interaction/CombatInterface.h"
#include "Kismet/GameplayStatics.h"


void UUpFightProjectileSpell::SpawnProjectile(const FVector InTargetLocation, const FGameplayTag SocketTag, const bool OverridePitch, const float InPitchOverride)
{
	// проверяем чтобы это делал сервер
	if(!GetAvatarActorFromActorInfo()->HasAuthority()) return;
	const FUpFightGameplayTags& GameplayTags = FUpFightGameplayTags::Get();
	// создаем transform в посохе и пока направления игрока
	FTransform ProjectileTransform;
	const FVector SocketLocation = ICombatInterface::Execute_GetSocketLocation(GetAvatarActorFromActorInfo(),SocketTag);
	ProjectileTransform.SetLocation(SocketLocation);
	
	// получаем направление шарика к цели
	FVector FromActorToTargetVector = InTargetLocation - SocketLocation;
	FromActorToTargetVector.Normalize();
	FRotator FromActorToTargetRotation = FromActorToTargetVector.Rotation();
	FromActorToTargetRotation.Pitch = 0.f;
	// если наклон снаряда будет true, то будем менять его по значению
	if(OverridePitch)
	{
		FromActorToTargetRotation.Pitch = InPitchOverride;
	}
	ProjectileTransform.SetRotation(FromActorToTargetRotation.Quaternion());
	
	// создаем отложенное спавн шарика
	AActor* CreatedActor = UGameplayStatics::BeginDeferredActorSpawnFromClass(this,
	   ProjectileClass,
	   ProjectileTransform,
	   ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn,
	   GetAvatarActorFromActorInfo());
	
	AUpFightProjectile* Projectile = Cast<AUpFightProjectile>(CreatedActor);

	FDamageEffectParams DamageEffectParams = MakeDefaultDamageEffectParams();
	/* теперь это будет в UUpFightAbilitySystemLibrary::UpFightApplyGameplayEffect
	// в шарике создаем спецификацию эффекта и назначаем источник
	Projectile->DamageEffectSpecHandle = MakeOutgoingGameplayEffectSpec(DamageEffect,1);
	Projectile->DamageEffectSpecHandle.Data->GetContext().AddSourceObject(GetAvatarActorFromActorInfo());
	// пройдемся по всем типам урона которые есть в заклинание и присвоим им теги и урон
	for(auto Pair : DamageTypes)
	{	
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(Projectile->DamageEffectSpecHandle,Pair.Key,Pair.Value.GetValueAtLevel(GetAbilityLevel()));
	}
	*/
	Projectile->DamageEffectParams = DamageEffectParams;
	// досоздаем шарик
	UGameplayStatics::FinishSpawningActor(CreatedActor,ProjectileTransform);
}

FString UUpFightProjectileSpell::GetSpellDescription(int32 Level)
{
	const int32 Damage = DamageTypes[FUpFightGameplayTags::Get().Damage_Fire].GetValueAtLevel(Level);

	if (Level == 1)
	{
		return FString::Printf(TEXT("<Title> FIRE BOLT</> \n\n <Default> Launches a bolt of fire, exploding on impact and dealing</> <Damage>%d</><Default> fire damage with a chance to burn</>\n\n <Small> Level: </><Level>%d</>"),Damage, Level);
	}
	else
	{
		return FString::Printf(TEXT("<Title> FIRE BOLT</> \n\n <Default> Launches %d boltes of fire, exploding on impact and dealing</> <Damage>%d</><Default> fire damage with a chance to burn</>\n\n <Small> Level: </><Level>%d</>"), FMath::Min(Level, NumProjectiles),Damage, Level);
	}
	
}

FString UUpFightProjectileSpell::GetNextLevelSpellDescription(int32 Level)
{
	const int32 Damage = DamageTypes[FUpFightGameplayTags::Get().Damage_Fire].GetValueAtLevel(Level);
	
	return FString::Printf(TEXT("<Title> FIRE BOLT</> \n\n <Default> Launches %d boltes of fire, exploding on impact and dealing</> <Damage>%d</><Default> fire damage with a chance to burn</>\n\n <Small> Level: </><Level>%d</>"), FMath::Min(Level, NumProjectiles),Damage, Level);
	
}

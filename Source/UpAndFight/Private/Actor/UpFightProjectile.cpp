// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/UpFightProjectile.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffect.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/AudioComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Interaction/CombatInterface.h"
#include "Kismet/GameplayStatics.h"
#include "UpAndFight/UpAndFight.h"

// Sets default values
AUpFightProjectile::AUpFightProjectile()
{
	// реппликация на клиентах
	bReplicates = true;
	
	PrimaryActorTick.bCanEverTick = false;
	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	SetRootComponent(Sphere);
	Sphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Sphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	Sphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	Sphere->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	Sphere->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);
	
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	ProjectileMovement->InitialSpeed = 550.f;
	ProjectileMovement->MaxSpeed = 550.f;
	ProjectileMovement->ProjectileGravityScale = 0.5f;
	// установим на новый тип колизии
	Sphere->SetCollisionObjectType(ECC_Projectile);
}

void AUpFightProjectile::BeginPlay()
{
	Super::BeginPlay();
	Sphere->OnComponentBeginOverlap.AddDynamic(this,&AUpFightProjectile::OnOverlap);
	// звук шипения 
	LoopingSoundComponent = UGameplayStatics::SpawnSoundAttached(LoopingSound,GetRootComponent());
	// задания время жизни
	SetLifeSpan(LifeSpanValue);
}

void AUpFightProjectile::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor->Implements<UCombatInterface>())
	{
		// звук удара и эффект удара
		UGameplayStatics::PlaySoundAtLocation(this,ImpactSound,GetActorLocation(),FRotator::ZeroRotator);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this,ImpactEffect,GetActorLocation());
		// остановим звук шипения
		LoopingSoundComponent->Stop();
		// если сервер то уничтожим если клиент то bHit = true
		if(HasAuthority() && DamageEffectSpecHandle.Data->GetContext().GetSourceObject() != OtherActor)
		{
			if(UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor))
			{
				ASC->ApplyGameplayEffectSpecToSelf(*DamageEffectSpecHandle.Data.Get());
			}
			Destroy();
		}
		else
		{
			bHit = true;
		}
	}
	else if(!OtherActor->Implements<UCombatInterface>())
	{
		if(HasAuthority())
		{
			Destroy();
		}
		else
		{
			bHit = true;
		}
	}
}

void AUpFightProjectile::Destroyed()
{
	if(!HasAuthority() && !bHit)
	{	// если это клиент и звука не было еще то воспроизведем
		UGameplayStatics::PlaySoundAtLocation(this,ImpactSound,GetActorLocation(),FRotator::ZeroRotator);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this,ImpactEffect,GetActorLocation());
		if(IsValid(LoopingSoundComponent))
		{
			LoopingSoundComponent->Stop();
		}
	}
	Super::Destroyed();
}
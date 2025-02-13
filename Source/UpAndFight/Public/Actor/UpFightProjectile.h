// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayAbilitySpec.h"
#include "GameFramework/Actor.h"
#include "UpFightProjectile.generated.h"


class UNiagaraSystem;
class UProjectileMovementComponent;
class USphereComponent;

UCLASS()
class UPANDFIGHT_API AUpFightProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AUpFightProjectile();
	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UPROPERTY()
	FGameplayEffectSpecHandle DamageEffectSpecHandle;
	
protected:
	virtual void BeginPlay() override;

	virtual void Destroyed() override;


	// переменная которая true при ударе и будет проверяться при destroy
	bool bHit = false;
	// время жизни шарика
	UPROPERTY(EditDefaultsOnly)
	float LifeSpanValue = 15.f;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> Sphere;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAudioComponent> LoopingSoundComponent;
	
	UPROPERTY(EditDefaultsOnly, Category="Projectile")
	TObjectPtr<USoundBase> ImpactSound;

	UPROPERTY(EditDefaultsOnly, Category="Projectile")
	TObjectPtr<UNiagaraSystem> ImpactEffect;

	UPROPERTY(EditDefaultsOnly, Category="Projectile")
	TObjectPtr<USoundBase> LoopingSound;


	
};

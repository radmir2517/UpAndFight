// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UpFightEffectActor.generated.h"

class UGameplayEffect;
class USphereComponent;

UCLASS()
class UPANDFIGHT_API AUpFightEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AUpFightEffectActor();

	
protected:
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable)
	//Функция применения эффекта к цели
	void ApplyEffectToTarget(AActor* Target,TSubclassOf<UGameplayEffect>GameplayEffectClass);

	// класс мгновенного эффекта
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect>InstanceGameplayEffectClass;
	
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UpFightEffectActor.generated.h"

class USphereComponent;

UCLASS()
class UPANDFIGHT_API AUpFightEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AUpFightEffectActor();

	virtual void Tick(float DeltaTime) override;

	virtual void OnOverlap (UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	virtual void EndOverlap (UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> Sphere;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UMeshComponent> Mesh;

	
};

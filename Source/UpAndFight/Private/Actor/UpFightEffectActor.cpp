// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/UpFightEffectActor.h"

#include "Components/SphereComponent.h"

// Sets default values
AUpFightEffectActor::AUpFightEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;
	Mesh = CreateDefaultSubobject<UMeshComponent>("Mesh");
	SetRootComponent(Mesh);
	
	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetupAttachment(Mesh);
	
}

void AUpFightEffectActor::BeginPlay()
{
	Super::BeginPlay();
	
	Sphere->OnComponentBeginOverlap.AddDynamic(this,&AUpFightEffectActor::OnOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this,&AUpFightEffectActor::EndOverlap);
}

// Called every frame
void AUpFightEffectActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AUpFightEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	
}

void AUpFightEffectActor::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
}


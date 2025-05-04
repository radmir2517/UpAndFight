// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/DebuffNiagaraComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Character/UPCharacterBase.h"


UDebuffNiagaraComponent::UDebuffNiagaraComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	bAutoActivate = false;

}


void UDebuffNiagaraComponent::BeginPlay()
{
	Super::BeginPlay();

	AUPCharacterBase* UpCharacterBase = Cast<AUPCharacterBase>(GetOwner());
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetOwner());
	if (ASC == nullptr)
	{
		UpCharacterBase->AbilitySystemInitializedDelegate.BindLambda([&]()
		{
			ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetOwner());
		});
	}
	for (auto Pair :NiagaraEffectToDebuffTag)
	{
		ASC->RegisterGameplayTagEvent(Pair.Key,EGameplayTagEventType::NewOrRemoved).AddUObject(this,&UDebuffNiagaraComponent::DebuffTagChanged);
	}

	
}

void UDebuffNiagaraComponent::DebuffTagChanged(FGameplayTag DebuffTag, int32 NewCount)
{
	if (NewCount > 0)
	{
		SetAsset(NiagaraEffectToDebuffTag[DebuffTag]);
		Activate();
	}
	else
	{
		Deactivate();
	}
}


void UDebuffNiagaraComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                            FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


}


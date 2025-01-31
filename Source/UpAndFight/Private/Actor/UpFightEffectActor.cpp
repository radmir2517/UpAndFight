// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/UpFightEffectActor.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"


// Sets default values
AUpFightEffectActor::AUpFightEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;
	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot"));
	
}

void AUpFightEffectActor::BeginPlay()
{
	Super::BeginPlay();
}

void AUpFightEffectActor::ApplyEffectToTarget(AActor* Target, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Target);
	checkf(GameplayEffectClass, TEXT("Set GameplayEffectclass to ActorEffect"));
	if(TargetASC)
	{
		FGameplayEffectContextHandle ContextHandle = TargetASC->MakeEffectContext();
		ContextHandle.AddSourceObject(this);
		FGameplayEffectSpecHandle SpecHandle = TargetASC->MakeOutgoingSpec(GameplayEffectClass,1.f,ContextHandle);
		// теперь для применения эффекта нам нужна ссылка на этот необработанный(он диначический) указатель спецификатора/
		FActiveGameplayEffectHandle ActiveGameplayEffectHandle = TargetASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		// булевая которая хранит бесконечен ли эффект или нет
		const bool bIsInfinity = SpecHandle.Data.Get()->Def->DurationPolicy == EGameplayEffectDurationType::Infinite;

		if(bIsInfinity && InfinityEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
		{// если эффект бесконечен и его надо завершить при выходе добавим его в карту
			ActiveEffectHandles.Add(ActiveGameplayEffectHandle,TargetASC);
		}
		// если стоит булевая к удалению и это не бесконеч. эффект то удалим актера
		if(bDestroyOnEffectRemoval && !bIsInfinity)
		{
			Destroy();
		}
	}
}

void AUpFightEffectActor::OnOverlap(AActor* Target)
{
	if(InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(Target,InstanceGameplayEffectClass);
	}
	if(DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(Target,DurationGameplayEffectClass);
	}
	if(InfinityEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(Target,InfinityGameplayEffectClass);
	}
}

void AUpFightEffectActor::OnEndOverlap(AActor* Target)
{
	if(InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(Target,InstanceGameplayEffectClass);
	}
	if(DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(Target,DurationGameplayEffectClass);
	}
	if(InfinityEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(Target,InfinityGameplayEffectClass);
	}

	if(InfinityEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(Target,InfinityGameplayEffectClass);
	}

	if(InfinityEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Target);
		if(!IsValid(TargetASC)) return;
		// 3) Создадим массив в котором будем хранить адреса эффектов для удаления
		TArray<FActiveGameplayEffectHandle> HandlesToRemove;
		for(auto HandlePair: ActiveEffectHandles)
		{// 1)пробегаемся по карте, сравниваем значение с нашим
			if(TargetASC == HandlePair.Value)
			{ // 2)у найденного значения есть ключ, а ключ это FActiveGameplayEffectHandle, нужный для завершения
				TargetASC->RemoveActiveGameplayEffect(HandlePair.Key,1);
				// 4) добавим в массив FActiveGameplayEffectHandle который надо удалить
				HandlesToRemove.Add(HandlePair.Key);
			}
		}
		for(auto& Handle : HandlesToRemove)
		{ // 5) Возьмем карту эффектов и найдем там те эффекты которые прекратили свое действие
			//  и безопасно удалим их
			ActiveEffectHandles.FindAndRemoveChecked(Handle);
		}
	}
	
}


// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/UpFightAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffectExtension.h"
#include "UpFightGameplayTags.h"
#include "GameFramework/Character.h"
#include "Interaction/CombatInterface.h"
#include "Net/UnrealNetwork.h"
#include "Player/UpFightPlayerController.h"

UUpFightAttributeSet::UUpFightAttributeSet()
{
	FUpFightGameplayTags Tags = FUpFightGameplayTags::Get();
	// добавим в карту атрибутов тег и в указатель вложим функцию вызова атрибута. Будет перебираться в AttributesMenuController и отправляться делегатом
	TagToAttributeFunc.Add(Tags.Attribute_Primary_Intelligence, GetIntelligenceAttribute);
	TagToAttributeFunc.Add(Tags.Attribute_Primary_Vigor, GetVigorAttribute);
	
	TagToAttributeFunc.Add(Tags.Attribute_Secondary_MaxMana, GetMaxManaAttribute);
	TagToAttributeFunc.Add(Tags.Attribute_Secondary_MaxHealth, GetMaxHealthAttribute);
	TagToAttributeFunc.Add(Tags.Attribute_Secondary_HealthRegeneration,GetHealthRegenerationAttribute);
	TagToAttributeFunc.Add(Tags.Attribute_Secondary_ManaRegeneration,GetManaRegenerationAttribute);

	TagToAttributeFunc.Add(Tags.Attribute_Vital_Health,GetHealthAttribute);
	TagToAttributeFunc.Add(Tags.Attribute_Vital_Mana, GetManaAttribute);

	TagToAttributeFunc.Add(Tags.Attribute_Resistance_Fire,GetFireResistanceAttribute);
	TagToAttributeFunc.Add(Tags.Attribute_Resistance_Lightning,GetLightningResistanceAttribute);
	TagToAttributeFunc.Add(Tags.Attribute_Resistance_Arcane,GetArcaneResistanceAttribute);
	TagToAttributeFunc.Add(Tags.Attribute_Resistance_Physical,GetPhysicalResistanceAttribute);
	
}

void UUpFightAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	// добавим репликацию для интеллекта, выносливости
	DOREPLIFETIME_CONDITION_NOTIFY(UUpFightAttributeSet,Intelligence,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UUpFightAttributeSet,Vigor,COND_None,REPNOTIFY_Always);
	// Secondary attributes
	DOREPLIFETIME_CONDITION_NOTIFY(UUpFightAttributeSet,HealthRegeneration,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UUpFightAttributeSet,ManaRegeneration,COND_None,REPNOTIFY_Always);
	// Vigor attributes
	DOREPLIFETIME_CONDITION_NOTIFY(UUpFightAttributeSet,Health,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UUpFightAttributeSet,MaxHealth,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UUpFightAttributeSet,Mana,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UUpFightAttributeSet,MaxMana,COND_None,REPNOTIFY_Always);
	// Resistance
	DOREPLIFETIME_CONDITION_NOTIFY(UUpFightAttributeSet,FireResistance,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UUpFightAttributeSet,LightningResistance,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UUpFightAttributeSet,ArcaneResistance,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UUpFightAttributeSet,PhysicalResistance,COND_None,REPNOTIFY_Always);
}


void UUpFightAttributeSet::OnRep_Intelligence(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UUpFightAttributeSet, Intelligence, OldValue);
}

void UUpFightAttributeSet::OnRep_Vigor(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UUpFightAttributeSet, Vigor, OldValue);
}

void UUpFightAttributeSet::OnRep_ManaRegeneration(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UUpFightAttributeSet, ManaRegeneration, OldValue);
}

void UUpFightAttributeSet::OnRep_HealthRegeneration(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UUpFightAttributeSet, HealthRegeneration, OldValue);
}

void UUpFightAttributeSet::OnRep_Health(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UUpFightAttributeSet, Health, OldValue);
}

void UUpFightAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UUpFightAttributeSet, MaxHealth, OldValue);
}

void UUpFightAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UUpFightAttributeSet, Mana, OldValue);
}

void UUpFightAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UUpFightAttributeSet, MaxMana, OldValue);
}


void UUpFightAttributeSet::OnRep_FireResistance(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UUpFightAttributeSet, FireResistance, OldValue);
}

void UUpFightAttributeSet::OnRep_LightningResistance(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UUpFightAttributeSet, LightningResistance, OldValue);
}

void UUpFightAttributeSet::OnRep_ArcaneResistance(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UUpFightAttributeSet, ArcaneResistance, OldValue);
}

void UUpFightAttributeSet::OnRep_PhysicalResistance(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UUpFightAttributeSet, PhysicalResistance, OldValue);
}


void UUpFightAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FEffectProperties Props;
	// получим SourceASC, SourceCharacter, SourceAvatarActor, SourceController, TargetASC, TargetCharacter,TargetAvatarActor, TargetController и EffectContextHandle
	SetEffectProperties(Data, Props);
	FUpFightGameplayTags& UpFightGameplayTags = FUpFightGameplayTags::Get();
	
	// пропишем ограничений для маны и здоровья, после изменением модификатором
	if(Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(),0.f,GetMaxHealth()));
		UE_LOG(LogTemp,Warning,TEXT("This Actor %s, changed Health, and has %f now"),*Props.TargetAvatarActor.GetName(), GetHealth())
	}
	if(Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		
		SetMana(FMath::Clamp(GetMana(),0.f,GetMaxMana()));
	}
	
	// получение урона
	if(Data.EvaluatedData.Attribute == GetDamageAttribute())
	{
		const float LocalDamage = GetDamage();
		
		if(LocalDamage == 0) return;
		
		SetDamage(0.f);
		const float LocalHealth = GetHealth() - LocalDamage;
		SetHealth(FMath::Clamp(LocalHealth,0.f,GetMaxHealth()));
		// если хп меньше нуля то будет считаться мертвым
		const bool bDead = LocalHealth <= 0.f;
		if(!bDead)
		{	// пробуем активировать GA_HitReact если он есть у персонажа
			FGameplayTagContainer TagContainer(UpFightGameplayTags.Effect_HitReact);
			
			for(auto Spec:Props.TargetAbilitySystemComponent->GetActivatableAbilities())
			{
				for(const FGameplayTag& Tag : Spec.Ability->AbilityTags)
				{
					if(Tag.MatchesTagExact(UpFightGameplayTags.Effect_HitReact))
					{
						Props.TargetAbilitySystemComponent->TryActivateAbility(Spec.Handle);
					}
				}
			}
			// покажем и воспроиведем анимацию виджета отвечающие за отоброжение урона
			if(Props.SourceCharacter != Props.TargetCharacter)
			{
				if(AUpFightPlayerController* UpFightPlayerController = Cast<AUpFightPlayerController>(Props.SourceController))
				{
					UpFightPlayerController->ShowDamageNumber(Props.TargetCharacter,LocalDamage);
				}
			}
			
		}
		else //(bDead)
		{
			ICombatInterface::Execute_Die(Props.TargetCharacter);
		}
	}
	
}

void UUpFightAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props)
{
	Props.EffectContextHandle =  Data.EffectSpec.GetContext();

	// получим информацию о Source
	Props.SourceAbilitySystemComponent = Props.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();
	if(IsValid(Props.SourceAbilitySystemComponent) && Props.SourceAbilitySystemComponent->AbilityActorInfo.IsValid() && IsValid(Props.SourceAbilitySystemComponent->GetAvatarActor()))
	{
		Props.SourceAvatarActor = Props.SourceAbilitySystemComponent->AbilityActorInfo->AvatarActor.Get();
		Props.SourceController = Props.SourceAbilitySystemComponent->AbilityActorInfo->PlayerController.Get();
		if(Props.SourceController == nullptr && Props.SourceAvatarActor != nullptr)
		{
			if(const APawn* Pawn = Cast<APawn>(Props.SourceAvatarActor))
			{
				Props.SourceController = Pawn->GetController();
			}
			if(Props.SourceController)
			{
				Props.SourceCharacter = Cast<ACharacter>(Props.SourceController->GetPawn());
			}
		}
	}
	// из Data получим информацию о Target
	if(Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		if(Props.TargetController == nullptr && Props.TargetAvatarActor != nullptr)
		{
			if(const APawn* Pawn = Cast<APawn>(Props.TargetAvatarActor))
			{
				Props.TargetController = Pawn->GetController();
			}
			if(Props.TargetController)
			{
				Props.TargetCharacter = Cast<ACharacter>(Props.TargetController->GetPawn());
			}
		}
		Props.TargetCharacter = Cast<ACharacter>(Props.TargetController->GetPawn());
		Props.TargetAbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Props.TargetCharacter);
	}
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AsyncTasks/WaitCooldownChange.h"

#include "AbilitySystemComponent.h"

UWaitCooldownChange* UWaitCooldownChange::WaitCooldownChange(UAbilitySystemComponent* AbiltiySystemComponent, FGameplayTag InCooldownTag)
{
	UWaitCooldownChange* WaitCooldownChange = NewObject<UWaitCooldownChange>();
	// присвоим локальным переменным значение параметров
	WaitCooldownChange->CooldownTag = InCooldownTag;
	WaitCooldownChange->ASC = AbiltiySystemComponent;
	// проверим, что все валидно, иначе закончим задачу
	if (!IsValid(WaitCooldownChange->ASC) || !WaitCooldownChange->CooldownTag.IsValid())
	{
		WaitCooldownChange->EndTask();
	}
	// привяжемся к делегату подсчета тегов для InCooldownTag и если он добавиться или удалиться вызовем нашу функцию
	WaitCooldownChange->ASC->RegisterGameplayTagEvent(InCooldownTag,EGameplayTagEventType::NewOrRemoved).AddUObject(WaitCooldownChange,&UWaitCooldownChange::CooldownTagEvent);
	// привяжемся к делегату применения эффекта с длительностью и тоже вызовем нашу функцию
	WaitCooldownChange->ASC->OnActiveGameplayEffectAddedDelegateToSelf.AddUObject(WaitCooldownChange,&UWaitCooldownChange::OnActiveEffectAdded);
	
	return WaitCooldownChange;
}

void UWaitCooldownChange::EndTask()
{
	if (!IsValid(ASC)) return;
	// удаляем привязку к удалению
	ASC->RegisterGameplayTagEvent(CooldownTag,EGameplayTagEventType::NewOrRemoved).RemoveAll(this);
	// помечаем экземпляр к удалению
	SetReadyToDestroy();
	MarkAsGarbage();
}


void UWaitCooldownChange::CooldownTagEvent(const FGameplayTag, int32 Count)
{	// если тег удалился значит эффект закончился и время его равно нулю
	if (Count == 0)
	{
		CooldownEndDelegate.Broadcast(0.f);
	}
}

void UWaitCooldownChange::OnActiveEffectAdded(UAbilitySystemComponent* AbiltiySystemComponent, const FGameplayEffectSpec& EffectSpec,
	FActiveGameplayEffectHandle EffectHandle)
{	// получим теги из спецификации эффектра
	FGameplayTagContainer GrantedTags;
	FGameplayTagContainer AssetsTags;
	
	EffectSpec.GetAllGrantedTags(GrantedTags);
	EffectSpec.GetAllAssetTags(AssetsTags);
	// если эффект имеет тег перезарядки
	if (GrantedTags.HasTagExact(CooldownTag) || AssetsTags.HasTagExact(CooldownTag))
	{	// то создадим запрос и найдем абилки с данным тегом и выпишем все оставшиеся времени выполнения
		FGameplayEffectQuery EffectQuery = FGameplayEffectQuery::MakeQuery_MatchAllOwningTags(CooldownTag.GetSingleTagContainer());
		TArray<float> TimeRemainings = AbiltiySystemComponent->GetActiveEffectsDuration(EffectQuery);
		
		if (TimeRemainings.Num() == 0) return;
		// найдем самую большое число и вернем через делегат
		float HighestTime = 0.f;
		for (float Duration : TimeRemainings)
		{
			if (Duration > HighestTime)
			{
				HighestTime = Duration;
			}
		}
		CooldownStartDelegate.Broadcast(HighestTime);
	}
	
}


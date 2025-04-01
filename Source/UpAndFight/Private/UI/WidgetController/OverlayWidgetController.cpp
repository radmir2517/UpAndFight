// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/UpFightAttributeSet.h"
#include "AbilitySystem/UpFightSystemComponent.h"
#include "AbilitySystem/Data/AbilityDataAsset.h"
#include "AbilitySystem/Data/LevelUpInfo.h"
#include "Player/UpFightPlayerState.h"


void UOverlayWidgetController::BindCallBacksToDependencies()
{
	Super::BindCallBacksToDependencies();
	UUpFightSystemComponent* UpFightAbilitySystemComponent = CastChecked<UUpFightSystemComponent>(AbilitySystemComponent);
	UUpFightAttributeSet* UpFightAttributeSet = Cast<UUpFightAttributeSet>(AttributeSet);
	AUpFightPlayerState* UpFightPlayerState = Cast<AUpFightPlayerState>(PlayerState);
	
	checkf(MessageWidgetDataTable, TEXT("Add a MessageWidgetDataTable to the OverlayWidgetController"));
	
	UpFightAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UpFightAttributeSet->GetHealthAttribute()).AddLambda([this](const FOnAttributeChangeData& Data)
	{
		HealthChangedDelegate.Broadcast(Data.NewValue);
	});
		UpFightAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UpFightAttributeSet->GetMaxHealthAttribute()).AddLambda([this](const FOnAttributeChangeData& Data)
	{
		MaxHealthChangedDelegate.Broadcast(Data.NewValue);
	});
		UpFightAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UpFightAttributeSet->GetManaAttribute()).AddLambda([this](const FOnAttributeChangeData& Data)
	{
		ManaChangedDelegate.Broadcast(Data.NewValue);
	});
		UpFightAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UpFightAttributeSet->GetMaxManaAttribute()).AddLambda([this](const FOnAttributeChangeData& Data)
	{
		MaxManaChangedDelegate.Broadcast(Data.NewValue);
	});
	
	// привяжемся к делегату который активируется при изменении опыта
	UpFightPlayerState->OnXPChangedDelegate.AddLambda([this](int32 NewXP)
	{
		const int32 PlayerLevel = LevelUpIfInfoAsset->GetLevelByXp(NewXP);
		const int32 MaxLevel = LevelUpIfInfoAsset->LevelUpInfos.Num();
		
		if (PlayerLevel <= MaxLevel)
		{	// Получим опыт для повышения предыдущего и след. уровня
		   const int32 NextLevelUPXP = LevelUpIfInfoAsset->LevelUpInfos[PlayerLevel+1].XPForThisLevel;
		   const int32 CurrentLevelUPXP = LevelUpIfInfoAsset->LevelUpInfos[PlayerLevel].XPForThisLevel;
			// Рассчитаем процент, для этого надо разницу медлу макс. след уровня и текущего	
		   const int32 DeltaLevelRequirement = NextLevelUPXP - CurrentLevelUPXP;
		   const int32 XPForThisLevel = NewXP - CurrentLevelUPXP;
		   // суть такая, нам нужно узнать какой сейчас процент опыта относительно текущего уровня и следующего,
		   // чтобы посчитать текущий процент, нужно отнять от нашего опыта, опыт который нужен для текущего и поделить на опыт следующего уровня
		   float XPBarPercent = static_cast<float>(XPForThisLevel) / static_cast<float>(DeltaLevelRequirement);
		   OnXPPercentChangedDelegate.Broadcast(XPBarPercent);
		}
	});

	UpFightPlayerState->OnLevelHangedDelegate.AddLambda([this](int32 NewLevel)
	{
		OnPlayerLevelChangedDelegate.Broadcast(NewLevel);
	});
	
	UpFightPlayerState->OnSpellPointsDelegate.AddLambda([this](int32 NewSpellPoints)
	{
		SpellPointsChangedDelegate.Broadcast(NewSpellPoints);
	});
	

	
	// вывод на экран иконок абилок, проверим был ли закончен процесс given
	UpFightAbilitySystemComponent->AbilityGivenDelegate.AddUObject(this, &UOverlayWidgetController::OnInitializeStartupAbilities);
		
	// после применения эффекта мы будем получать теги эффекта и если оно совпадет с зельями выведем на экран
	UpFightAbilitySystemComponent->EffectAssetTagsDelegate.AddLambda([this](const FGameplayTagContainer& AssetTags)
	{
		for(const FGameplayTag& Tag : AssetTags)
		{
			FUIWidgetRow* Row = GetDataRowFromTable<FUIWidgetRow>(MessageWidgetDataTable, Tag);
			EffectMessageDelegate.Broadcast(*Row);
		}
	});
}

void UOverlayWidgetController::BroadcastInitialValues()
{
	Super::BroadcastInitialValues();

	UUpFightAttributeSet* UpFightAttributeSet = Cast<UUpFightAttributeSet>(AttributeSet);
	MaxHealthChangedDelegate.Broadcast(UpFightAttributeSet->GetMaxHealth());
	HealthChangedDelegate.Broadcast(UpFightAttributeSet->GetHealth());
	MaxManaChangedDelegate.Broadcast(UpFightAttributeSet->GetMaxMana());
	ManaChangedDelegate.Broadcast(UpFightAttributeSet->GetMana());
}

void UOverlayWidgetController::OnInitializeStartupAbilities()
{// получим GameMode где мы достанем UAbilityDataAsset
	//const AUpFightGameMode* UpGameMode = Cast<AUpFightGameMode>(UGameplayStatics::GetGameMode(UpASC->GetAvatarActor()));
	//if(!IsValid(UpGameMode)) return;
	//UAbilityDataAsset* AbilityDataInfoAsset = UpGameMode->AbilityInfo;
	
	UUpFightSystemComponent* UpASC = CastChecked<UUpFightSystemComponent>(AbilitySystemComponent);
	if(!UpASC->bStartupAbilityGiven) return;
	// заблокируем список способностей, чтобы предотвратить их одновременное изменение
	FScopedAbilityListLock ActiveScopeLock(*UpASC);
	for(const FGameplayAbilitySpec AbilitySpec: UpASC->GetActivatableAbilities())
	{	// найдем структуру в AbilityInfo с нашим способностью
		FAbilityInfo AbilityInfo  = AbilityDataInfoAsset->FindAbilityInfoByTag(UpASC->GetAbilityTagFromSpec(AbilitySpec));
		if(AbilityInfo.AbilityTag.IsValid())
		{
			AbilityInfoDelegate.Broadcast(AbilityInfo);
		}
	}
}

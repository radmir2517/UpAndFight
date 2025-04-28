// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/UpFightSystemComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "UpFightGameplayTags.h"
#include "AbilitySystem/UpFightAbilitySystemLibrary.h"
#include "AbilitySystem/Abilities/UpFightGameplayAbility.h"
#include "AbilitySystem/Data/AbilityDataAsset.h"
#include "Game/UpFightGameMode.h"
#include "Interaction/PlayerInterface.h"
#include "Kismet/GameplayStatics.h"

void UUpFightSystemComponent::AbilityActorInfoSet()
{ // привяжемся к делегату которые при применения эффекта будет вызывать функцию EffectApplied
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this,&UUpFightSystemComponent::EffectApplied);
}

void UUpFightSystemComponent::AddCharacterStartupAbilities(TArray<TSubclassOf<UGameplayAbility>> StartedGameplayAbilities)
{	// переберем классы всех GameplayAbilities и сделаем GiveAbility
	for(const TSubclassOf<UGameplayAbility>& Ability : StartedGameplayAbilities)
	{
		FGameplayAbilitySpec Spec = BuildAbilitySpecFromClass(Ability,1);
		if(const UUpFightGameplayAbility* GameplayAbility = Cast<UUpFightGameplayAbility>(Spec.Ability))
		{	// добавим тег input и тег, что он Equipped
			Spec.GetDynamicSpecSourceTags().AddTag(GameplayAbility->SetupInputTag);
			Spec.GetDynamicSpecSourceTags().AddTag(FUpFightGameplayTags::Get().Abilities_Status_Equipped);
			GiveAbility(Spec);
		}
	}
	bStartupAbilityGiven = true;
	AbilityGivenDelegate.Broadcast();
}

void UUpFightSystemComponent::AddAndActivatePassiveAbilities(
	TArray<TSubclassOf<UGameplayAbility>> PassiveGameplayAbilities)
{
	for(const TSubclassOf<UGameplayAbility> AbilityClass : PassiveGameplayAbilities)
	{
		FGameplayAbilitySpec Spec = FGameplayAbilitySpec(AbilityClass,1);
		GiveAbility(Spec);
		FGameplayTagContainer PassiveGameplayTags;
		PassiveGameplayTags.AddTag(FUpFightGameplayTags::Get().Abilities_ListenAbility);
		TryActivateAbilitiesByTag(PassiveGameplayTags);
	}

}

void UUpFightSystemComponent::AddCharacterAbilities(TSubclassOf<UGameplayAbility> GameplayAbility)
{
	FGameplayAbilitySpec Spec = BuildAbilitySpecFromClass(GameplayAbility,1);
	// если уже такая абилка уже добавлена другим способом,то не добавляем ее заново
	for (FGameplayAbilitySpec Ability : GetActivatableAbilities())
	{
		if (Ability.Ability->AbilityTags.First() == Spec.Ability->AbilityTags.First())
		{
			return;
		}
	}
	// проверяем что что кастится и делаем GiveAbility
	if(const UUpFightGameplayAbility* GameplayAbility = Cast<UUpFightGameplayAbility>(Spec.Ability))
	{	// добавим status тег, что он Eligible
		Spec.GetDynamicSpecSourceTags().AddTag(FUpFightGameplayTags::Get().Abilities_Status_Locked);
		GiveAbility(Spec);
	}
	
}

void UUpFightSystemComponent::AbilityInputTagHeld(FGameplayTag& GameplayTag)
{// переберем все GetActivatableAbilities и активируем заклинания
	FScopedAbilityListLock ActiveScopeLock(*this);
	for(FGameplayAbilitySpec& Spec : GetActivatableAbilities())
	{
		if(Spec.GetDynamicSpecSourceTags().HasTagExact(GameplayTag))
		{
			AbilitySpecInputPressed(Spec);
			if(!Spec.IsActive())
			{
				TryActivateAbility(Spec.Handle);
				GEngine->AddOnScreenDebugMessage(2,3.f,FColor::Red,FString::Printf(TEXT("AbilityInputTagHeld InputTag: %s"),*GameplayTag.ToString()));
			}
		}
	}
}

void UUpFightSystemComponent::AbilityInputTagReleased(FGameplayTag& GameplayTag)
{// переберем все GetActivatableAbilities и отметим что произошел Released
	FScopedAbilityListLock ActiveScopeLock(*this);
	for(FGameplayAbilitySpec& Spec : GetActivatableAbilities())
	{
		if(Spec.GetDynamicSpecSourceTags().HasTagExact(GameplayTag))
		{
			AbilitySpecInputReleased(Spec);
			GEngine->AddOnScreenDebugMessage(3,3.f,FColor::Red,FString::Printf(TEXT("AbilityInputTagReleased InputTag: %s"),*GameplayTag.ToString()));
		}
	}
}

void UUpFightSystemComponent::UpgradeAttributes(const FGameplayTag& AttributeTag)
{
	if (GetAvatarActor()->Implements<UPlayerInterface>())
	{
		ServerUpgradeAttributes(AttributeTag);
	}
}

void UUpFightSystemComponent::ServerUpgradeAttributes_Implementation(const FGameplayTag& AttributeTag)
{
	// создадим Payload, загрузим туда тег атрибута и значение и отправляем эвент в GA_ListenForEvent
	// не забываем добавить аттрибуты EventBasedEffect
	FGameplayEventData EventData;
	EventData.EventTag = AttributeTag;
	EventData.EventMagnitude = 1.f;
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetAvatarActor(),AttributeTag,EventData);
	IPlayerInterface::Execute_AddToAttributePoints(GetAvatarActor(),-1);
}


void UUpFightSystemComponent::ServerUpgradeSpellPoint_Implementation(const FGameplayTag& AbilityTag,
	const FGameplayTag& StatusTag)
{// повысим уровень данного заклинания по тегу на 1 единицу и проверим его статусы
	FGameplayAbilitySpec* AbilitySpec = GetAbilitySpecByAbilityTag(AbilityTag);
	// проверим что абилка внутри есть
	if (IsValid(AbilitySpec->Ability))
	{	// прибавим уровень абилки
		AbilitySpec->Level += 1;
		// прибавим ее и в PlayerState
		IPlayerInterface::Execute_AddToSpellPoints(GetAvatarActor(),-1);
		// поменяет статусы при первом повышения уровня с 0 до 1
		if (StatusTag == FUpFightGameplayTags::Get().Abilities_Status_Eligible)
		{	
			AbilitySpec->GetDynamicSpecSourceTags().RemoveTag(FUpFightGameplayTags::Get().Abilities_Status_Eligible);
			AbilitySpec->GetDynamicSpecSourceTags().AddTag(FUpFightGameplayTags::Get().Abilities_Status_Unlocked);
		}
		MarkAbilitySpecDirty(*AbilitySpec);
		ClientUpgradeSpellMenu();
	}
}

void UUpFightSystemComponent::ClientUpgradeSpellMenu_Implementation()
{	// запустит USpellWidgetController::BroadcastInitialValues(), и он обновит во всех виджетах spell даже в Overlay иконки заклинаний
	SpellWidgetsUpdateDelegate.Broadcast();
}

void UUpFightSystemComponent::InitializeAbilitiesForMenuControllers_Implementation()
{// пройдемся по AbilityInfo, если наши заклинания есть в Give то вытащим inputTag и Status, назначим в AbilityInfo и отправим во все SpellWidget(что в Overlay, что в SpellMenu)
	AUpFightGameMode* UpFightGameMode = Cast<AUpFightGameMode>(UGameplayStatics::GetGameMode(GetAvatarActor()));
	UAbilityDataAsset* AbilityDataInfoAsset = UpFightGameMode->AbilityDataInfoAsset;
	
	// заблокируем список способностей, чтобы предотвратить их одновременное изменение
	FScopedAbilityListLock ActiveScopeLock(*this);
	
	for(const FGameplayAbilitySpec AbilitySpec: GetActivatableAbilities())
	{	// найдем структуру в AbilityInfo с нашим способностью
		FAbilityInfo AbilityInfo  = AbilityDataInfoAsset->FindAbilityInfoByTag(GetAbilityTagFromSpec(AbilitySpec));
		if(AbilityInfo.AbilityTag.IsValid())
		{
			// назначим тег статуса в эту структуру и отправим ее в виджеты
			AbilityInfo.StatusTag = GetStatusTagFromSpec(AbilitySpec);
			AbilityInfo.InputTag = GetInputTagFromSpec(AbilitySpec); 
			InitializeAbilitiesForMenuControllersForClient(AbilityInfo);
		}
	}
}


void UUpFightSystemComponent::InitializeAbilitiesForMenuControllersForClient_Implementation(
	const FAbilityInfo& AbilityInfo)
{
	AbilityInfoServerDelegate.Broadcast(AbilityInfo);
}


// запускается в AUpFightPlayerState::AddPlayerLevel при повышения уровня
void UUpFightSystemComponent::UpdateStatusAbilities(const int32 Level)
{	// проверим достигли ли мы уровня для добавления новых заклинаний, если достигли то добавим в Give и добавим ему статус
	UAbilityDataAsset* AbilityDataAsset = UUpFightAbilitySystemLibrary::GetAbilityInfo(GetAvatarActor());

	for (auto Info : AbilityDataAsset->AbilitiesInfo)
	{
		// если тега нет, то стартуем слудующий цикл
		if (!Info.AbilityTag.IsValid()) continue;
		// Если требования уровня больше чем у нас то следующий цикл
		if (Level < Info.LevelRequirement) continue;
		// если этого заклинания еще нет в Give то следующий цикл
		FGameplayAbilitySpec* AbilitySpec = GetAbilitySpecByAbilityTag(Info.AbilityTag);
		if (AbilitySpec == nullptr ) continue;

		if (AbilitySpec->GetDynamicSpecSourceTags().HasTagExact(FUpFightGameplayTags::Get().Abilities_Status_Locked))
		{
			AbilitySpec->GetDynamicSpecSourceTags().RemoveTag(FUpFightGameplayTags::Get().Abilities_Status_Locked);
			AbilitySpec->GetDynamicSpecSourceTags().AddTag(FUpFightGameplayTags::Get().Abilities_Status_Eligible);
		}
		MarkAbilitySpecDirty(*AbilitySpec);
	}
}
// перетаскивания SpellGlobe на новое место, замена тегов статуса на новые
void UUpFightSystemComponent::ServerSpendEquipAbility_Implementation(const FGameplayTag AbilityTag, const FGameplayTag NewInputTag)
{ 	// перетаскивания SpellGlobe на новое место, замена тегов статуса на новые
	/*TODO:  1) если мы заменяем заклинание на глобус где уже есть, то у старого надо обнулить inputTag  DONE
	 *		2)А если мы перемещаем заклинание на пустой глобус но при этом это заклинание уже есть на глобусах то надо убрать его со старого место  DONE
	 */
	if (AbilityTag.IsValid() && NewInputTag.IsValid())
	{	// получаем спецификацию абилки и меняем в нем теги 
		FGameplayAbilitySpec* AbilitySpec = GetAbilitySpecByAbilityTag(AbilityTag);
		// получим предыдущий InputTag если он уже был на глобусах
		const FGameplayTag PastInputTag = GetInputTagFromSpec(*AbilitySpec);

		// если в том глобусе на который мы будем переносить заклинание уже есть заклинание, то очистим заклинание от inputTag и обновим SpellGlobe
		if (FGameplayAbilitySpec* OldAbilitySpec = GetAbilitySpecByInputTag(NewInputTag))
		{
			OldAbilitySpec->GetDynamicSpecSourceTags().RemoveTag(NewInputTag);
			OldAbilitySpec->GetDynamicSpecSourceTags().RemoveTag(FUpFightGameplayTags::Get().Abilities_Status_Equipped);
			OldAbilitySpec->GetDynamicSpecSourceTags().AddTag(FUpFightGameplayTags::Get().Abilities_Status_Unlocked);
			
			// чистим старый глобус, а точнее делаем невидим Background и Icon изображение, т.к при назначении нового мы заменим иконки и постави видимость
			ClientClearOldGlobe(NewInputTag);
			// отмечаем ее для обновления
			MarkAbilitySpecDirty(*OldAbilitySpec);
		}
		
		// если заклинание уже имеет InputTag, т.е находится на виджетах, то очистим его и SpellGlobe, дадим новый тег и отправим все виджеты на обновление
		if (PastInputTag.IsValid())
		{
			AbilitySpec->GetDynamicSpecSourceTags().RemoveTag(PastInputTag);
			AbilitySpec->GetDynamicSpecSourceTags().AddTag(NewInputTag);
			// чистим старый глобус, а точнее делаем невидим Background и Icon изображение, т.к при назначении нового мы заменим иконки и постави видимость
			ClientClearOldGlobe(PastInputTag);
			// отмечаем ее для обновления
			MarkAbilitySpecDirty(*AbilitySpec);
			// запускаем клиентскую функцию
			ClientSpendEquipAbility();
		}
		// если заклинание еще не было  (GetStatusTagFromSpec(*AbilitySpec) == FUpFightGameplayTags::Get().Abilities_Status_Unlocked)
		else 
		{
			AbilitySpec->GetDynamicSpecSourceTags().RemoveTag(FUpFightGameplayTags::Get().Abilities_Status_Unlocked);
			AbilitySpec->GetDynamicSpecSourceTags().AddTag(FUpFightGameplayTags::Get().Abilities_Status_Equipped);
			AbilitySpec->GetDynamicSpecSourceTags().AddTag(NewInputTag);
			
			// отмечаем ее для обновления
			MarkAbilitySpecDirty(*AbilitySpec);
			// запускаем клиентскую функцию
			ClientSpendEquipAbility();
		}
	}
}

void UUpFightSystemComponent::ClientSpendEquipAbility_Implementation()
{	// отправим на обновление 
	SpellWidgetsUpdateDelegate.Broadcast();
}

void UUpFightSystemComponent::ClientClearOldGlobe_Implementation(const FGameplayTag PastInputTag)
{
	ClearOldGlobeServerDelegate.Broadcast(PastInputTag);
}

bool UUpFightSystemComponent::GetSpellDescriptions(const FGameplayTag& AbilityTag, FString& OutSpellDescription,
                                                   FString& OutNextLevelSpellDescription)
{// если способность глобуса есть в Give, то достанем инфу о нем
	FGameplayAbilitySpec* AbilitySpec = GetAbilitySpecByAbilityTag(AbilityTag);
	if (AbilitySpec && GetStatusTagFromSpec(*AbilitySpec) != FUpFightGameplayTags::Get().Abilities_Status_Eligible)
	{
		UUpFightGameplayAbility* UpAbility = Cast<UUpFightGameplayAbility>(AbilitySpec->Ability);
		OutSpellDescription = UpAbility->GetSpellDescription(AbilitySpec->Level);
		OutNextLevelSpellDescription = UpAbility->GetNextLevelSpellDescription(AbilitySpec->Level + 1);
		return true;
	}
	// если ее нет, то достанем уровень из AbilityDataAsset и вернем строку с требуемым уровнем
	UAbilityDataAsset* AbilityInfoDataAsset = UUpFightAbilitySystemLibrary::GetAbilityInfo(GetAvatarActor());
	FAbilityInfo Info = AbilityInfoDataAsset->FindAbilityInfoByTag(AbilityTag);
	OutSpellDescription = UUpFightGameplayAbility::GetLockedSpellDescription(Info.LevelRequirement);
	OutNextLevelSpellDescription = FString();
	return false;
}

FGameplayTag UUpFightSystemComponent::GetAbilityTagFromSpec(const FGameplayAbilitySpec& AbilitySpec)
{	// получем тег из спецификации
	if(AbilitySpec.Ability)
	{
		for(FGameplayTag Tag : AbilitySpec.Ability.Get()->AbilityTags)
		{
			if(Tag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("Abilities"))))
			{
				return Tag;
			}
		}
	}
	return FGameplayTag();
}

FGameplayTag UUpFightSystemComponent::GetInputTagFromSpec(const FGameplayAbilitySpec& AbilitySpec)
{	// получем тег из спецификации 
	if(IsValid(AbilitySpec.Ability))
	{
		for(FGameplayTag Tag : AbilitySpec.GetDynamicSpecSourceTags())
		{
			if(Tag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("InputTag"))))
			{
				return Tag;
			}
		}
	}
	return FGameplayTag();
}

FGameplayTag UUpFightSystemComponent::GetStatusTagFromSpec(const FGameplayAbilitySpec& AbilitySpec)
{
	if (IsValid(AbilitySpec.Ability))
	{
		for (FGameplayTag Tag : AbilitySpec.GetDynamicSpecSourceTags())
		{
			if (Tag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("Abilities.Status"))))
			{
				return Tag;
			}
		}
	}
	return FGameplayTag();
}

FGameplayAbilitySpec* UUpFightSystemComponent::GetAbilitySpecByAbilityTag(const FGameplayTag AbilityTag)
{
	for (FGameplayAbilitySpec& Spec : GetActivatableAbilities())
	{
		if (Spec.Ability->AbilityTags.First().MatchesTagExact(AbilityTag))
		{
			return &Spec;
		}
	}
	return nullptr;
}

FGameplayAbilitySpec* UUpFightSystemComponent::GetAbilitySpecByInputTag(const FGameplayTag InInputTag)
{
	for (FGameplayAbilitySpec& Spec : GetActivatableAbilities())
	{
		for (FGameplayTag InputTag  : Spec.GetDynamicSpecSourceTags())
		{
			if (InputTag == InInputTag)
			{
				return &Spec;
			}
		}
	}
	return nullptr;
}

void UUpFightSystemComponent::EffectApplied(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& EffectSpec,FActiveGameplayEffectHandle EffectHandle)
{	// вытащим теги и передадим в OverlayController
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);

	EffectAssetTagsDelegate.Broadcast(TagContainer);
}

void UUpFightSystemComponent::OnRep_ActivateAbilities()
{
	Super::OnRep_ActivateAbilities();

	if (!bStartupAbilityGiven)
	{
		bStartupAbilityGiven = true;
		AbilityGivenDelegate.Broadcast();
	}

}

// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/UpFightAbilitySystemLibrary.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Engine/OverlapResult.h"
#include "Game/UpFightGameMode.h"
#include "Interaction/CombatInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Player/UpFightPlayerState.h"
#include "UI/HUD/UpFightHUD.h"
#include "UI/WidgetController/UpFightWidgetController.h"

UOverlayWidgetController* UUpFightAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject,0);
	if(AUpFightHUD* UpFightHUD = Cast<AUpFightHUD>(PC->GetHUD()))
	{
		AUpFightPlayerState* PS = PC->GetPlayerState<AUpFightPlayerState>();
		UAttributeSet* AS = PS->GetAttributeSet();
		UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
		FWidgetControllerParams WCParams(PC,PS,ASC,AS);
		return UpFightHUD->GetOverlayWidgetController(WCParams);
	}
	return nullptr;
}

UUpFightAttributeMenuController* UUpFightAbilitySystemLibrary::GetAttributeMenuController(const UObject* WorldContextObject)
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject,0);
	if(AUpFightHUD* UpFightHUD = Cast<AUpFightHUD>(PC->GetHUD()))
	{
		AUpFightPlayerState* PS = PC->GetPlayerState<AUpFightPlayerState>();
		UAttributeSet* AS = PS->GetAttributeSet();
		UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
		FWidgetControllerParams WCParams(PC,PS,ASC,AS);
		return UpFightHUD->GetAttributeMenuWidgetController(WCParams);
	}
	return nullptr;
}

UCharacterClassInfo* UUpFightAbilitySystemLibrary::GetCharacterClassInfo(const UObject* WorldContextObject)
{
	AUpFightGameMode* UpFightGameMode = Cast<AUpFightGameMode>(UGameplayStatics::GetGameMode(WorldContextObject));
	return UpFightGameMode->CharacterClassInfo;
	
}

void UUpFightAbilitySystemLibrary::InitializeDefaultAttributes(const UObject* WorldContextObject,
	ECharacterClass CharacterClass, UAbilitySystemComponent* ASC, float Level)
{

	// получим доступ к UpFightGameModeBase чтобы взять оттуда ассут с Primary attributes,Secondary,Vital;
	UCharacterClassInfo* CharacterClassInfo = GetCharacterClassInfo(WorldContextObject);
	
	// назначим источник аватара, чтобы могли работать MMC_MaxHealth и мана
	AActor* Avatar = ASC->GetAvatarActor();
	FGameplayEffectContextHandle EffectContext = ASC->MakeEffectContext();
	EffectContext.AddSourceObject(Avatar);
	
	// получим структуру содержащий PrimaryAttributes конкретного класса Воина, Лучника, Элементалиста
	FCharacterClassDefaultInfo ClassDefaultInfo = CharacterClassInfo->GetCharacterClassInfoByEnum(CharacterClass);
	
	// получим спецификатор и применим эффект с атрибутами к персонажу врага для каждого аттрибута
	FGameplayEffectSpecHandle PrimaryAttributesSpec = ASC->MakeOutgoingSpec(ClassDefaultInfo.PrimaryAttributes,Level,EffectContext);
	ASC->ApplyGameplayEffectSpecToSelf(*PrimaryAttributesSpec.Data.Get());
	
	// получим спецификатор и применим эффект с атрибутами к персонажу врага для каждого аттрибута
	FGameplayEffectSpecHandle SecondaryAttributesSpec = ASC->MakeOutgoingSpec(CharacterClassInfo->SecondaryAttributesEffectClass,Level,EffectContext);
	ASC->ApplyGameplayEffectSpecToSelf(*SecondaryAttributesSpec.Data.Get());
	
	// получим спецификатор и применим эффект с атрибутами к персонажу врага для каждого аттрибута
	FGameplayEffectSpecHandle VitalAttributesSpec = ASC->MakeOutgoingSpec(CharacterClassInfo->VitalAttributesEffectClass,Level,EffectContext);
	ASC->ApplyGameplayEffectSpecToSelf(*VitalAttributesSpec.Data.Get());

}

void UUpFightAbilitySystemLibrary::GiveStartupAbilities(const UObject* WorldContextObject,
                                                        UAbilitySystemComponent* ASC, ECharacterClass& Class)
{
	check(ASC);
	UCharacterClassInfo* ClassInfo = GetCharacterClassInfo(WorldContextObject);
	for(const TSubclassOf<UGameplayAbility> AbilityClass : ClassInfo->CommonAbilities)
	{
		ASC->GiveAbility(ASC->BuildAbilitySpecFromClass(AbilityClass));
	}
	UCharacterClassInfo* CharacterClassInfo = UUpFightAbilitySystemLibrary::GetCharacterClassInfo(WorldContextObject);
	const FCharacterClassDefaultInfo ClassDefaultInfo = CharacterClassInfo->GetCharacterClassInfoByEnum(Class);

	for(auto Ability: ClassDefaultInfo.StartupAbilities)
	{
		if(ASC->GetAvatarActor()->Implements<UCombatInterface>())
		{
			const FGameplayAbilitySpec Spec = ASC->BuildAbilitySpecFromClass(Ability,ICombatInterface::Execute_GetPlayerLevel(ASC->GetAvatarActor()));
			ASC->GiveAbility(Spec);
		}
	}
}


TArray<AActor*> UUpFightAbilitySystemLibrary::GetLiveActorsFromRadius(const UObject* WorldContextObject, const AActor* SourceActor,
                                                                      const FVector& InLocation, const float InRadius)
{
	// параметры запроса коллизии, добавим туда игнор нашего персонажа
	FCollisionQueryParams SphereParams(FName(),false, SourceActor);
	
	// query scene to see what we hit
	TArray<FOverlapResult> Overlaps;
	
	if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{	// тут нужна будет структура с запросом колиизии, добавим туда запрос с AllDynamicObjects и лишь в концу добавим наш SphereParams, т.к в конструкторе нет одновременно фильтра MobilityType и игнор объекта
		World->OverlapMultiByObjectType(Overlaps, InLocation, FQuat::Identity, FCollisionObjectQueryParams(FCollisionObjectQueryParams::InitType::AllDynamicObjects), FCollisionShape::MakeSphere(InRadius), SphereParams);
	}
	// структура актеров которые мы будем возвращать
	TArray<AActor*> OverlapActors;
	// переберем массив в котором будут актеры в радиусе
	for (const FOverlapResult& Overlap : Overlaps)
	{
		AActor* const OverlapActor = Overlap.OverlapObjectHandle.FetchActor();
		if(!AreTheyFriends(SourceActor, OverlapActor))
		{
			OverlapActors.AddUnique(OverlapActor);
		}
	}
	return OverlapActors;
}

bool UUpFightAbilitySystemLibrary::AreTheyFriends( const AActor* SourceActor,
	const AActor* TargetActor)
{
	bool IsFriend = false;
	IsFriend = SourceActor->ActorHasTag("Enemy") && TargetActor->ActorHasTag("Enemy");
	IsFriend = SourceActor->ActorHasTag("Player") && TargetActor->ActorHasTag("Player");
	return IsFriend;
}

void UUpFightAbilitySystemLibrary::UpFightApplyGameplayEffect(TSubclassOf<UGameplayEffect> EffectClass, AActor* SourceActor,
	AActor* TargetActor, TMap<FGameplayTag, FScalableFloat> EffectTypes, float Level)
{
	if( !IsValid(SourceActor) || !IsValid(TargetActor) || EffectTypes.IsEmpty() ) return;
	
	UAbilitySystemComponent* SourceASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(SourceActor);
	if(!IsValid(SourceASC)) return;

	FGameplayEffectContextHandle ContextHandle = SourceASC->MakeEffectContext();
	ContextHandle.AddSourceObject(SourceActor);
	FGameplayEffectSpecHandle SpecHandle = SourceASC->MakeOutgoingSpec(EffectClass,Level,ContextHandle);

	for(auto Pair : EffectTypes)
	{
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle,Pair.Key,Pair.Value.GetValueAtLevel(Level));
	}
	
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	SourceASC->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(),TargetASC);
	
}

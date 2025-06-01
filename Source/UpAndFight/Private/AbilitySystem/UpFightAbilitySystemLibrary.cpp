// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/UpFightAbilitySystemLibrary.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "UpFightGameplayTags.h"
#include "AbilitySystem/UpFightAbilityTypes.h"
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

USpellWidgetController* UUpFightAbilitySystemLibrary::GetSpellMenuController(const UObject* WorldContextObject)
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject,0);
	
	if (IsValid(PC))
	{
		AUpFightHUD* UpHUD = Cast<AUpFightHUD>(PC->GetHUD());
		if (IsValid(UpHUD))
		{
			UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(PC->GetPawn());
			AUpFightPlayerState* PS = PC->GetPlayerState<AUpFightPlayerState>();
			UAttributeSet* AS = PS->GetAttributeSet();
			
			FWidgetControllerParams WCParams(PC,PS,ASC,AS);
			return UpHUD->GetSpellMenuWidgetController(WCParams);
		}
	}
	return nullptr;
}

UCharacterClassInfo* UUpFightAbilitySystemLibrary::GetCharacterClassInfo(const UObject* WorldContextObject)
{
	AUpFightGameMode* UpFightGameMode = Cast<AUpFightGameMode>(UGameplayStatics::GetGameMode(WorldContextObject));
	return UpFightGameMode->CharacterClassInfo;
	
}

ULevelUpInfo* UUpFightAbilitySystemLibrary::GetLevelUpInfo(const UObject* WorldContextObject)
{
	AUpFightGameMode* UpFightGameMode = Cast<AUpFightGameMode>(UGameplayStatics::GetGameMode(WorldContextObject));
	return UpFightGameMode->LevelUpInfo;
}

UAbilityDataAsset* UUpFightAbilitySystemLibrary::GetAbilityInfo(const UObject* WorldContextObject)
{
	AGameModeBase* BaseGameMode = UGameplayStatics::GetGameMode(WorldContextObject);
	if (AUpFightGameMode* UpFightGameMode = Cast<AUpFightGameMode>(BaseGameMode))
	{
		return UpFightGameMode->AbilityDataInfoAsset;
	}
	return nullptr;
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


void UUpFightAbilitySystemLibrary::GetLiveActorsFromRadius(const UObject* WorldContextObject, const TArray<AActor*>& IgnoreActors,
	TArray<AActor*>& ActorsToOut, const float InRadius, const FVector& Origin)
{
	// параметры запроса коллизии, добавим туда игнор нашего персонажа
	FCollisionQueryParams SphereParams;

	SphereParams.AddIgnoredActors(IgnoreActors);
	// query scene to see what we hit
	TArray<FOverlapResult> Overlaps;
	// провреим что можем получить мир
	if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{	// тут нужна будет структура с запросом колиизии, добавим туда запрос с AllDynamicObjects и лишь в концу добавим наш SphereParams, т.к в конструкторе нет одновременно фильтра MobilityType и игнор объекта
		World->OverlapMultiByObjectType(Overlaps, Origin, FQuat::Identity, FCollisionObjectQueryParams(FCollisionObjectQueryParams::InitType::AllDynamicObjects), FCollisionShape::MakeSphere(InRadius), SphereParams);
		// переберем массив в котором будут актеры в радиусе
		ActorsToOut.Empty();
		for (const FOverlapResult& Overlap : Overlaps)
		{
			AActor* OverlapActor = Overlap.OverlapObjectHandle.FetchActor();
			if(OverlapActor->Implements<UCombatInterface>() && !ICombatInterface::Execute_IsDead(OverlapActor))
			{
				ActorsToOut.AddUnique(OverlapActor);
			}
		}
	}
}

bool UUpFightAbilitySystemLibrary::AreTheyFriends( const AActor* SourceActor,
	const AActor* TargetActor)
{
	if(TargetActor->Tags.Num() == 0) return false;
	return SourceActor->Tags[0] == TargetActor->Tags[0];
}

FGameplayEffectContextHandle UUpFightAbilitySystemLibrary::UpFightApplyGameplayEffect(const FDamageEffectParams& DamageEffectParams)
{
	// получаем SourceAvatarActor и теги
	FUpFightGameplayTags& GameplayTags = FUpFightGameplayTags::Get();
	AActor* SourceAvatarActor = DamageEffectParams.SourceAbilitySystemComponent->GetAvatarActor();
	// для эффекта нужен контекст и спецификация
	FGameplayEffectContextHandle ContextHandle = DamageEffectParams.SourceAbilitySystemComponent->MakeEffectContext();
	ContextHandle.AddSourceObject(SourceAvatarActor);
	const FGameplayEffectSpecHandle SpecHandle = DamageEffectParams.SourceAbilitySystemComponent->MakeOutgoingSpec(DamageEffectParams.GameplayEffectClass,DamageEffectParams.AbilityLevel,ContextHandle);
	// назначаем урон
	for(auto Pair : DamageEffectParams.DamageTagAndValue)
	{
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle,Pair.Key,Pair.Value);
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle,GameplayTags.DamageTypesToDebuff[Pair.Key], DamageEffectParams.DebuffDamage);
	}
	// если задан импульс смерти, то передадим его в контекст чтобы дальше его применить при смерти
	if (DamageEffectParams.DeathImpulseMagnitude > 0.0f)
	{
		SetDeathImpulse(ContextHandle,DamageEffectParams.DeathImpulse);
	}
	// назначаем дебаффу его параметры полученные из UDamageGameplayAbility::MakeDefaultDamageEffectParams
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle,GameplayTags.Debuff_Chance, DamageEffectParams.DebuffChance);
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle,GameplayTags.Debuff_Duration, DamageEffectParams.DebuffDuration);
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle,GameplayTags.Debuff_Frequency, DamageEffectParams.DebuffFrequency);
	// применяем эффект
	DamageEffectParams.TargetAbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
	// возвращаем контекст для дальнейшего взаимодействия
	return ContextHandle;
}

bool UUpFightAbilitySystemLibrary::IsSuccessfulDebuff(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FUpFightGameplayEffectContext* EffectContext = static_cast<const FUpFightGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return EffectContext->IsSuccessfulDebuff();
	}
	return false;
}

float UUpFightAbilitySystemLibrary::GetDebuffDuration(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FUpFightGameplayEffectContext* EffectContext = static_cast<const FUpFightGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return EffectContext->GetDebuffDuration();
	}
	return 0.f;
}

float UUpFightAbilitySystemLibrary::GetDebuffFrequency(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FUpFightGameplayEffectContext* EffectContext = static_cast<const FUpFightGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return EffectContext->GetDebuffFrequency();
	}
	return 0.f;
}

TSharedPtr<FGameplayTag> UUpFightAbilitySystemLibrary::GetDamageType(
	const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FUpFightGameplayEffectContext* EffectContext = static_cast<const FUpFightGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return EffectContext->GetDamageType();
	}
	return nullptr;
}

FVector UUpFightAbilitySystemLibrary::GetDeathVector(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FUpFightGameplayEffectContext* EffectContext = static_cast<const FUpFightGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return EffectContext->GetDeathImpulse();
	}
	return FVector::ZeroVector;
}

void UUpFightAbilitySystemLibrary::SetSuccessDebuff(FGameplayEffectContextHandle& EffectContextHandle,
                                                    bool InIsSuccessfulDebuff)
{
	if (FUpFightGameplayEffectContext* EffectContext = static_cast<FUpFightGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		EffectContext->SetIsSuccessfulDebuff(InIsSuccessfulDebuff);
	}
}

void UUpFightAbilitySystemLibrary::SetDebuffDamage(FGameplayEffectContextHandle& EffectContextHandle, float InDamage)
{
	if (FUpFightGameplayEffectContext* EffectContext = static_cast<FUpFightGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		EffectContext->SetDebuffDamage(InDamage);
	}
}

void UUpFightAbilitySystemLibrary::SetDebuffDuration(FGameplayEffectContextHandle& EffectContextHandle,
	float InDuration)
{
	if (FUpFightGameplayEffectContext* EffectContext = static_cast<FUpFightGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		EffectContext->SetDebuffDuration(InDuration);
	}
}

void UUpFightAbilitySystemLibrary::SetDebuffFrequency(FGameplayEffectContextHandle& EffectContextHandle,
	float InFrequency)
{
	if (FUpFightGameplayEffectContext* EffectContext = static_cast<FUpFightGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		EffectContext->SetDebuffFrequency(InFrequency);
	}
}

void UUpFightAbilitySystemLibrary::SetDamageType(FGameplayEffectContextHandle& EffectContextHandle,
	const FGameplayTag& InDamageType)
{
	if (FUpFightGameplayEffectContext* EffectContext = static_cast<FUpFightGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		TSharedPtr<FGameplayTag> DamageType = MakeShared<FGameplayTag>(InDamageType);
		EffectContext->SetDamageType(DamageType);
	}
}

void UUpFightAbilitySystemLibrary::SetDeathImpulse(FGameplayEffectContextHandle& EffectContextHandle,
	const FVector& InDeathImpulse)
{
	if (FUpFightGameplayEffectContext* EffectContext = static_cast<FUpFightGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		EffectContext->SetDeathImpulse(InDeathImpulse);
	}
}


float UUpFightAbilitySystemLibrary::GetDebuffDamage(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FUpFightGameplayEffectContext* EffectContext = static_cast<const FUpFightGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return EffectContext->GetDebuffDamage();
	}
	return 0.f;
}

int32 UUpFightAbilitySystemLibrary::GetXPRewardForClassAndLevel(const UObject* WorldContextObject,const  ECharacterClass& Class, const int32 Level)
{	// получим информацию о классах и вытащим оттуда структуру с нашим классом
	UCharacterClassInfo* CharacterClassInfo = GetCharacterClassInfo(WorldContextObject);
	FCharacterClassDefaultInfo Info = CharacterClassInfo->GetCharacterClassInfoByEnum(Class);
	// вернем кол-во опыта от врага
	return static_cast<int32>(Info.XPReward.GetValueAtLevel(Level));
}

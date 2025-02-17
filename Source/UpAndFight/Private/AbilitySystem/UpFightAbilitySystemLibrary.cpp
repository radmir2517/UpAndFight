// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/UpFightAbilitySystemLibrary.h"

#include "Game/UpFightGameMode.h"
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
	UAbilitySystemComponent* ASC)
{
	check(ASC);
	UCharacterClassInfo* ClassInfo = GetCharacterClassInfo(WorldContextObject);
	for(const TSubclassOf<UGameplayAbility> AbilityClass : ClassInfo->CommonAbilities)
	{
		ASC->GiveAbility(ASC->BuildAbilitySpecFromClass(AbilityClass));
	}
}

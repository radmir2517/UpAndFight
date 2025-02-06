// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/UpFightAbilitySystemLibrary.h"

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

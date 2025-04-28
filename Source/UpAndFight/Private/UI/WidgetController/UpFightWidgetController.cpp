// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/UpFightWidgetController.h"


#include "AbilitySystem/UpFightAttributeSet.h"
#include "AbilitySystem/UpFightSystemComponent.h"
#include "AbilitySystem/Data/AbilityDataAsset.h"
#include "Player/UpFightPlayerController.h"
#include "Player/UpFightPlayerState.h"


void UUpFightWidgetController::BindCallBacksToDependencies()
{
	UpAbilitySystemComponent = GetUpAbilitySystemComponent();
	UpAbilitySystemComponent->AbilityInfoServerDelegate.AddLambda([&](const FAbilityInfo& AbilityInfo)
{
	AbilityInfoDelegate.Broadcast(AbilityInfo);
});

	UpAbilitySystemComponent->ClearOldGlobeServerDelegate.AddLambda([&](const FGameplayTag PastInputTag)
	{
		ClearOldGlobeDelegate.Broadcast(PastInputTag);
	});
}

void UUpFightWidgetController::BroadcastInitialValues()
{
	
}

void UUpFightWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& Params)
{
	PlayerController = Params.PlayerController;
	PlayerState = Params.PlayerState;
	AbilitySystemComponent = Params.AbilitySystemComponent;
	AttributeSet = Params.AttributeSet;
}

UUpFightSystemComponent* UUpFightWidgetController::GetUpAbilitySystemComponent()
{
	if (UpAbilitySystemComponent == nullptr)
	{
		UpAbilitySystemComponent = Cast<UUpFightSystemComponent>(AbilitySystemComponent);
	}
	return UpAbilitySystemComponent;
}

UUpFightAttributeSet* UUpFightWidgetController::GetUpAttributeSet()
{
	if (UpAttributeSet == nullptr)
	{
		UpAttributeSet = Cast<UUpFightAttributeSet>(AttributeSet);
	}
	return UpAttributeSet;
}

AUpFightPlayerState* UUpFightWidgetController::GetUpPlayerState()
{
	if (UpPlayerState == nullptr)
	{
		UpPlayerState = Cast<AUpFightPlayerState>(PlayerState);
	}
	return UpPlayerState;
}

AUpFightPlayerController* UUpFightWidgetController::GetUpPlayerController()
{
	if (UpPlayerController == nullptr)
	{
		UpPlayerController = Cast<AUpFightPlayerController>(PlayerController);
	}
	return UpPlayerController;
}

void UUpFightWidgetController::OnInitializeStartupAbilities()
{
	/** Теперь не будем получать AbilityDataInfoAsset с GameMode а будем брать указатель с UUpFightWidgetController
	 * //получим GameMode где мы достанем UAbilityDataAsset
	//const AUpFightGameMode* UpGameMode = Cast<AUpFightGameMode>(UGameplayStatics::GetGameMode(UpASC->GetAvatarActor()));
	//if(!IsValid(UpGameMode)) return;
	//UAbilityDataAsset* AbilityDataInfoAsset = UpGameMode->AbilityInfo;*/

	// будем получать AbilityDataAsset теперь из Gamemode
	//if (!GetUpPlayerController()->HasAuthority()) return;
	UAbilityDataAsset* AbilityDataInfoAsset = AbilityDataAsset;
	
	UpAbilitySystemComponent = GetUpAbilitySystemComponent();
	if(!UpAbilitySystemComponent->bStartupAbilityGiven) return;
	
	UpAbilitySystemComponent->InitializeAbilitiesForMenuControllers();
	/*
	// заблокируем список способностей, чтобы предотвратить их одновременное изменение
	FScopedAbilityListLock ActiveScopeLock(*UpAbilitySystemComponent);
	
	for(const FGameplayAbilitySpec AbilitySpec: UpAbilitySystemComponent->GetActivatableAbilities())
	{	// найдем структуру в AbilityInfo с нашим способностью
		FAbilityInfo AbilityInfo  = AbilityDataInfoAsset->FindAbilityInfoByTag(UpAbilitySystemComponent->GetAbilityTagFromSpec(AbilitySpec));
		if(AbilityInfo.AbilityTag.IsValid())
		{
			// назначим тег статуса в эту структуру и отправим ее в виджеты
			AbilityInfo.StatusTag = UpAbilitySystemComponent->GetStatusTagFromSpec(AbilitySpec);
			AbilityInfoDelegate.Broadcast(AbilityInfo);
		}
	}
	*/
}

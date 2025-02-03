// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/UPCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/UpFightAttributeSet.h"
#include "AbilitySystem/UpFightSystemComponent.h"
#include "Chaos/ChaosPerfTest.h"
#include "Player/UpFightPlayerController.h"
#include "Player/UpFightPlayerState.h"
#include "UI/HUD/UpFightHUD.h"


AUPCharacter::AUPCharacter()
{
	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; 
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
}

void AUPCharacter::InitOverlay()
{
	// делаем касты на наш контроллер и HUD с проверкой
	AUpFightPlayerController* UpFightPlayerController = CastChecked<AUpFightPlayerController>(GetController());
	AUpFightHUD* UpFightHUD = CastChecked<AUpFightHUD>(UpFightPlayerController->GetHUD());
	// если они пустые то возвращаем
	if(!IsValid(UpFightHUD) || !IsValid(UpFightPlayerController)) return;
	// инцилизация оверлея, создания контроллера в HUD и создания выведения Overlay виджета на экран
	UpFightHUD->InitOverlay(UpFightPlayerController,GetPlayerState(),AbilitySystemComponent,AttributeSet);
}

void AUPCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	// сообщаем кто avatar actor и кто Owner, также получаем AbilitySystem, AttributeSet из PlayerState
	// также там проводит инициализацию OverlayWidget и OverlayWidgetController
	InitAbilityInfo();
}

void AUPCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	// сообщаем кто avatar actor и кто Owner
	InitAbilityInfo();
}


void AUPCharacter::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level)
{
	check(GameplayEffectClass)
	FGameplayEffectContextHandle EffectHandle = AbilitySystemComponent->MakeEffectContext();
	EffectHandle.AddSourceObject(this);
	FGameplayEffectSpecHandle EffectSpec = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffectClass,Level,EffectHandle);
	AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*EffectSpec.Data.Get());
}


void AUPCharacter::InitializePrimaryAttributes()
{
	// включим эффект первичных атрибутов
	ApplyEffectToSelf(PrimaryAttributesEffectClass, UpFightPlayerState->GetPlayerLevel());
}

void AUPCharacter::InitializeSecondaryAttributes()
{// включим эффект вторичных атрибутов
	ApplyEffectToSelf(SecondaryAttributesEffectClass, UpFightPlayerState->GetPlayerLevel());
}


void AUPCharacter::InitializeDefaultAttributes()
{// применения эффекта с атрибутами Primary and Secondary
	InitializePrimaryAttributes();
	InitializeSecondaryAttributes();
}

// сообщаем кто avatar actor и кто Owner
void AUPCharacter::InitAbilityInfo()
{
	UpFightPlayerState = GetPlayerState<AUpFightPlayerState>();
	check(UpFightPlayerState);
	AbilitySystemComponent = UpFightPlayerState->GetAbilitySystemComponent();
	AttributeSet = UpFightPlayerState->GetAttributeSet();
	// вызов привязки делегата OnGameplayEffectAppliedToSelf к нашей функции в AbilitySystemComponent
	Cast<UUpFightSystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();
	// сообщаем кто avatar actor и кто Owner
	AbilitySystemComponent->InitAbilityActorInfo(UpFightPlayerState, this);
	// применения эффекта с атрибутами Primary and Secondary
	InitializeDefaultAttributes();
	// инцилизация оверлея, создания контроллера в HUD и создания выведения Overlay виджета на экран
	InitOverlay();
}

int32 AUPCharacter::GetPlayerLevel()
{
	return Cast<AUpFightPlayerState>(GetPlayerState())->GetPlayerLevel();
}

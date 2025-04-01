// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/UPCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "AbilitySystemComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "AbilitySystem/UpFightSystemComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/UpFightPlayerController.h"
#include "Player/UpFightPlayerState.h"
#include "UI/HUD/UpFightHUD.h"


AUPCharacter::AUPCharacter()
{

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->TargetArmLength = 350.f;
	SpringArmComponent->SetRelativeRotation(FRotator(-30, 90, 0));
	SpringArmComponent->bInheritPitch = false;
	SpringArmComponent->bInheritRoll = false;
	SpringArmComponent->bInheritYaw = false;
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);
	
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
	if(AUpFightPlayerController* UpFightPlayerController = Cast<AUpFightPlayerController>(GetController()))
	{
		if(AUpFightHUD* UpFightHUD = Cast<AUpFightHUD>(UpFightPlayerController->GetHUD()))
		{
			// инцилизация оверлея, создания контроллера в HUD и создания выведения Overlay виджета на экран
			UpFightHUD->InitOverlay(UpFightPlayerController,GetPlayerState(),AbilitySystemComponent,AttributeSet);
		}
	}
}

void AUPCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	// сообщаем кто avatar actor и кто Owner, также получаем AbilitySystem, AttributeSet из PlayerState
	// также там проводит инициализацию OverlayWidget и OverlayWidgetController
	InitAbilityInfo();
	// сделаем give ability для стартовых ability
	AddCharacterAbilities();
	GiveAndActivatePassiveAbilities();
}

void AUPCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	// сообщаем кто avatar actor и кто Owner
	InitAbilityInfo();
}

// сообщаем кто avatar actor и кто Owner
void AUPCharacter::InitAbilityInfo()
{
	UpFightPlayerState = GetPlayerState<AUpFightPlayerState>();
	check(UpFightPlayerState);
	AbilitySystemComponent = UpFightPlayerState->GetAbilitySystemComponent();
	AttributeSet = UpFightPlayerState->GetAttributeSet();
	InitOverlay();
	// вызов привязки делегата OnGameplayEffectAppliedToSelf к нашей функции в AbilitySystemComponent
	Cast<UUpFightSystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();
	// сообщаем кто avatar actor и кто Owner
	AbilitySystemComponent->InitAbilityActorInfo(UpFightPlayerState, this);
	// применения эффекта с атрибутами Primary and Secondary
	InitializeDefaultAttributes();
	// инцилизация оверлея, создания контроллера в HUD и создания выведения Overlay виджета на экран
	
}

int32 AUPCharacter::GetPlayerLevel_Implementation()
{
	return Cast<AUpFightPlayerState>(GetPlayerState())->GetPlayerLevel();
}

int32 AUPCharacter::GetXP_Implementation()
{
	return Cast<AUpFightPlayerState>(GetPlayerState())->GetXP();
}

void AUPCharacter::AddXPReward_Implementation(float Reward)
{
	UpFightPlayerState->AddXP(Reward);
}

void AUPCharacter::AddPlayerLevel_Implementation(int32 InLevel)
{
	UpFightPlayerState->AddPlayerLevel(InLevel);
	UNiagaraFunctionLibrary::SpawnSystemAttached(LevelUpEffect,GetMesh(),FName("pelvis"),GetMesh()->GetComponentLocation(),FRotator(),EAttachLocation::KeepWorldPosition,true);
}

void AUPCharacter::AddToAttributePoints_Implementation(int32 Points)
{
	UpFightPlayerState->AddAttributePoints(Points);
}

void AUPCharacter::AddToSpellPoints_Implementation(int32 Points)
{
	UpFightPlayerState->AddSpellPoints(Points);
}

int32 AUPCharacter::GetAttributePoints_Implementation()
{
	return UpFightPlayerState->GetAttributePoints();
}

int32 AUPCharacter::GetSpellPoints_Implementation()
{
	return UpFightPlayerState->GetSpellPoints();
}


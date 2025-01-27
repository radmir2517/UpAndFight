// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/UPCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"

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

void AUPCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	InitAbilityInfo();
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
	AUpFightPlayerState* UpFightPlayerState = GetPlayerState<AUpFightPlayerState>();
	check(UpFightPlayerState);
	AbilitySystemComponent = UpFightPlayerState->GetAbilitySystemComponent();
	AttributeSet = UpFightPlayerState->GetAttributeSet();
	// сообщаем кто avatar actor и кто Owner
	AbilitySystemComponent->InitAbilityActorInfo(UpFightPlayerState, this);
}

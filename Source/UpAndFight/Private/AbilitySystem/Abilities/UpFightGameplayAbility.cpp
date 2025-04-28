// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/UpFightGameplayAbility.h"

#include "Interaction/CombatInterface.h"

UUpFightGameplayAbility::UUpFightGameplayAbility()
{
	
}

FTaggedMontage UUpFightGameplayAbility::GetRandomTaggedMontageFromArray(const TArray<FTaggedMontage>& TaggedMontages)
{
	int32 MaxMontages = TaggedMontages.Num();
	
	if(MaxMontages == 1)
	{
		return TaggedMontages[0];
	}
	else if (MaxMontages > 1)
	{
		int32 RandomMontageNumber = FMath::RandRange(0,MaxMontages-1);
		return TaggedMontages[RandomMontageNumber];
	}
	
	UE_LOG(LogTemp, Error, TEXT("TaggedMontages.Num = 0, check AttackMontages at %s"), *GetAvatarActorFromActorInfo()->GetName())
	return FTaggedMontage();
}

FString UUpFightGameplayAbility::GetSpellDescription(int32 Level)
{	// L "" это расширенный текст, который позволяет ввести много текста, вести спец слово LoremIpsum которые далее будеться заменяться
	return FString::Printf(TEXT("<%s</> <Default> Current Level: </><Level>%d </>"),
		L"Default> Ability Name - LoremIpsum LoremIpsum LoremIpsum LoremIpsum LoremIpsum LoremIpsum LoremIpsum LoremIpsum, ", Level);
}

FString UUpFightGameplayAbility::GetNextLevelSpellDescription(int32 Level)
{ // будем выводить пока следующий уровень
	return FString::Printf(TEXT("<Default> Next Level: </><Level>%d</>"),Level);
}

FString UUpFightGameplayAbility::GetLockedSpellDescription(int32 Level)
{
	return FString::Printf(TEXT("<Default> Spell Locked Until Level: </><Level>%d</>"),Level);
}

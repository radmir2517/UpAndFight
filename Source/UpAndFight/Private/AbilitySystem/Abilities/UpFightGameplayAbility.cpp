// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/UpFightGameplayAbility.h"

#include "Interaction/CombatInterface.h"

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

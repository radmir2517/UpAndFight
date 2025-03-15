// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Data/AbilityDataAsset.h"

FAbilityInfo UAbilityDataAsset::FindAbilityInfoByTag(FGameplayTag AbilityTag, bool bLogNotFound)
{ // выведем структуру с нашей абилкой, если не найдем такую то напишем в лог если bLogNotFound = true
	for (auto Info : AbilitiesInfo)
	{
		if(Info.AbilityTag == AbilityTag)
		{
			return Info;
		}
		if(bLogNotFound)
		{
			UE_LOG(LogTemp,Warning,TEXT("UAbilityDataAsset::FindAbilityInfoByTag, can't find Ability by this Tag %s"), *AbilityTag.ToString());
		}
	}
	return FAbilityInfo();
}

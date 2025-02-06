// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Data/AttributeDataAsset.h"

FAttributeInfo UAttributeDataAsset::GetAttributeInfoByTag(const FGameplayTag& Tag)
{	// найдем структуру атрибута по тегу
	for (FAttributeInfo Info : AttributesInfo)
	{
		if(Info.AttributeTag.MatchesTag(Tag))
		{
			return Info;
		}
	}
	return FAttributeInfo();
}

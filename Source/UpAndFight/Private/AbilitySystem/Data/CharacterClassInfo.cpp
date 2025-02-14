// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Data/CharacterClassInfo.h"

FCharacterClassDefaultInfo UCharacterClassInfo::GetCharacterClassInfoByEnum(const ECharacterClass& inClass)
{
	for(auto Info : CharacterClassInformation)
	{
		if(Info.Key == inClass)
		{
			return Info.Value;
		}
	}
	return FCharacterClassDefaultInfo();
}

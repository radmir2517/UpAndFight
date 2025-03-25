// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Data/LevelUpInfo.h"

int32 ULevelUpInfo::GetLevelByXp(int32 inXP)
{	
	int32 CurrentLevel = 0;
	for (FLevelInfo Info :LevelUpInfos)
	{
		// если текущий кол-во текущего опыты меньше чем требования этого уровня возвращаем предыдущий уровень
		if (inXP < Info.XPForThisLevel)
		{
			return CurrentLevel - 1;
		}
		++CurrentLevel;
	}
	// если ничего не вернуло в If то вернем просто первый уровень
	return 1;
}

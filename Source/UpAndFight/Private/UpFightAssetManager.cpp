// Fill out your copyright notice in the Description page of Project Settings.


#include "UpFightAssetManager.h"

#include "UpFightGameplayTags.h"

UUpFightAssetManager& UUpFightAssetManager::InitializeUpFightAssetManage()
{
	check(GEngine);
	UUpFightAssetManager* UpFightAssetManager = Cast<UUpFightAssetManager>(GEngine->AssetManager);
	return *UpFightAssetManager;
}

void UUpFightAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	// Вызовем инициализацию тегов в менеджере тегов
	FUpFightGameplayTags::InitializeNativeGameplayTags();
}

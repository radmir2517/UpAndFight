// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UpFightAbilitySystemLibrary.generated.h"


class UOverlayWidgetController;
class UUpFightAttributeMenuController;

UCLASS()
class UPANDFIGHT_API UUpFightAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category="UPFightAbilitySystemLibrary|WidgetController")
	static UOverlayWidgetController* GetOverlayWidgetController(const UObject* WorldContextObject);
	UFUNCTION(BlueprintPure, Category="UPFightAbilitySystemLibrary|WidgetController")
	static UUpFightAttributeMenuController* GetAttributeMenuController(const UObject* WorldContextObject);
};

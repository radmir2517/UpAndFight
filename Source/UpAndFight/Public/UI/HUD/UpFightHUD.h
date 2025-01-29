// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UpFightHUD.generated.h"

class UUpFightUserWidget;
/**
 * 
 */
UCLASS()
class UPANDFIGHT_API AUpFightHUD : public AHUD
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TObjectPtr<UUpFightUserWidget> OverlayWidget;

protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> OverlayWidgetClass;
};

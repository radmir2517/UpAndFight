// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UpFightHUD.generated.h"

class UUpFightAttributeMenuController;
class UAttributeSet;
class UAbilitySystemComponent;
struct FWidgetControllerParams;
class UOverlayWidgetController;
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

	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WCParams);
	UFUNCTION(BlueprintCallable)
	UUpFightAttributeMenuController* GetAttributeMenuWidgetController(const FWidgetControllerParams& WCParams);
	
	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);

protected:
	virtual void BeginPlay() override;
	
private:

	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;
	TObjectPtr<UUpFightAttributeMenuController> AttributeMenuWidgetController;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> OverlayWidgetClass;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUpFightAttributeMenuController> AttributeMenuWidgetControllerClass;
	
};

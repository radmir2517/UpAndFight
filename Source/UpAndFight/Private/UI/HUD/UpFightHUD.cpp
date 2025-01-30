// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/UpFightHUD.h"

#include "UI/WidgetController/OverlayWidgetController.h"
#include "Blueprint/UserWidget.h"
#include "UI/Widget/UpFightUserWidget.h"

UOverlayWidgetController* AUpFightHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if(!IsValid(OverlayWidgetController))
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		// назначим AttributeSet, AbilitySystem, PlayerController, PlayerState в контроллер
		OverlayWidgetController->SetWidgetControllerParams(WCParams);
	}
	return OverlayWidgetController;
}

void AUpFightHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	// проверим что эти классы назначены в HUD
	checkf(OverlayWidgetClass, TEXT("Overlay Widget Class uninitialized, please fill out BP_UpFightHUD"));
	checkf(OverlayWidgetControllerClass, TEXT("Overlay Widget Controller Class uninitialized, please fill out BP_UpFightHUD"));
	
	FWidgetControllerParams WCParams(PC,PS,ASC,AS);
	// получим или создадим виджет контроллер для Overlay
	GetOverlayWidgetController(WCParams);
	
	// Создадим виджет и выставим на экран
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(),OverlayWidgetClass);
	OverlayWidget = Cast<UUpFightUserWidget> (Widget);
	// добавим контроллер в виджет
	OverlayWidget->SetWidgetController(OverlayWidgetController);
	OverlayWidget->AddToViewport();

	OverlayWidgetController->BroadcastInitialValues();
}

void AUpFightHUD::BeginPlay()
{
	Super::BeginPlay();

}

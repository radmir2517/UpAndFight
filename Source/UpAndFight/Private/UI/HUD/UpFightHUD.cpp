// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/UpFightHUD.h"

#include "Blueprint/UserWidget.h"
#include "UI/Widget/UpFightUserWidget.h"

void AUpFightHUD::BeginPlay()
{
	Super::BeginPlay();
	// СОздадим виджет и выставим на экран
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(),OverlayWidgetClass);
	OverlayWidget = Cast<UUpFightUserWidget> (Widget);
	OverlayWidget->AddToViewport();
}

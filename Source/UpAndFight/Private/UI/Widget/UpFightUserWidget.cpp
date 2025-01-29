// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/UpFightUserWidget.h"

void UUpFightUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UpFightUserWidget.generated.h"


UCLASS()
class UPANDFIGHT_API UUpFightUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// установка контоллера и запуск функции WidgetControllerSet в BP
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InWidgetController);

	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();
	// указатель на контроллер 
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;
};

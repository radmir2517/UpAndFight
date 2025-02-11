// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "TargetDataUnderCursor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMouseTargetDataSignature, const FGameplayAbilityTargetDataHandle&, TargetData);

UCLASS()
class UPANDFIGHT_API UTargetDataUnderCursor : public UAbilityTask
{
	GENERATED_BODY()

public:
	
	// функция создания экземпляра нашего класса
	UFUNCTION(BlueprintCallable, Category="Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
	static UTargetDataUnderCursor* CreateTargetDataUnderMouse(UGameplayAbility* OwningAbility);

	// делегат который будет передавать координаты под курсором
	UPROPERTY(BlueprintAssignable)
	FMouseTargetDataSignature TargetDataCursorTrace;

	// функция будет активировано когда будет получены реплицированные данные цели
	void OnTargetDataReplicatedCallback(const FGameplayAbilityTargetDataHandle& TargetDataHandle, FGameplayTag GameplayTag );

private:
	// функция которая будет активироваться при вызова нода этого класса
	virtual void Activate() override;
	virtual void OnDestroy(bool bInOwnerFinished) override;
	void SendMouseCursorData();
};

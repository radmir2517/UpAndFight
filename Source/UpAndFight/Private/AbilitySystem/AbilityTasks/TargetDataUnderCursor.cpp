// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AbilityTasks/TargetDataUnderCursor.h"

#include "AbilitySystemComponent.h"
#include "Kismet/GameplayStatics.h"



UTargetDataUnderCursor* UTargetDataUnderCursor::CreateTargetDataUnderMouse(UGameplayAbility* OwningAbility)
{// создадим экземпляр задачи
	UTargetDataUnderCursor* MyObj = NewAbilityTask<UTargetDataUnderCursor>(OwningAbility);
	return MyObj;
}

void UTargetDataUnderCursor::OnDestroy(bool bInOwnerFinished)
{
	Super::OnDestroy(bInOwnerFinished);
	
}

void UTargetDataUnderCursor::Activate()
{
	Super::Activate();
	//Возвращает true, если этот агент локально контролируется. Только true для игроков на клиенте
	const bool IsLocally = Ability->GetCurrentActorInfo()->IsLocallyControlled();

	if(IsLocally)
	{
		SendMouseCursorData();
	}
	else
	{// действие для сервера
		const FGameplayAbilitySpecHandle SpecHandle = GetAbilitySpecHandle();
		const FPredictionKey ActivationPredictionKey = GetActivationPredictionKey();
		// делегат отвечает за установку данных о целях для способности. Оно будет вызвано в сервере
		AbilitySystemComponent->AbilityTargetDataSetDelegate(SpecHandle,ActivationPredictionKey).AddUObject(this, &UTargetDataUnderCursor::OnTargetDataReplicatedCallback);
		// далее проверяем была ли привяз делегат, если все ок, то он осуществляет Broadcast целевых данных TargetData и ТегАктивации
		const bool bCalledDelegate = AbilitySystemComponent->CallReplicatedTargetDataDelegatesIfSet(SpecHandle,ActivationPredictionKey);
		if(!bCalledDelegate)
		{ //  Вызывается, когда задача способности ожидает данных от удаленного игрока. Если удаленный игрок завершает способность досрочно,
			// а задача с этим набором все еще запущена, способность будет убита.
			SetWaitingOnRemotePlayerData();
		}
	}

}

void UTargetDataUnderCursor::SendMouseCursorData()
{
	FScopedPredictionWindow ScopedPredictionWindow(AbilitySystemComponent.Get());
	// после создания экземпляра, будет активация задачи
	// вытащим контроллер
	AActor* PlayerActor = Ability->GetAvatarActorFromActorInfo();
	APlayerController* PC = UGameplayStatics::GetPlayerController(PlayerActor,0);
	
	// Целевые данные с одним результатом попадания, данные упаковываются в результат попадания, будут отправлены на сервер и на клиент
	FGameplayAbilityTargetData_SingleTargetHit * TargetData = new FGameplayAbilityTargetData_SingleTargetHit();
	// получим место нажатия курсора и передадим в TargetData_SingleTargetHit
	PC->GetHitResultUnderCursor(ECC_Visibility,false,TargetData->HitResult);
	// Give it a handle and return
	FGameplayAbilityTargetDataHandle DataHandle;
	DataHandle.Data.Add(TSharedPtr<FGameplayAbilityTargetData>(TargetData));
	//Репликация данных таргетинга на сервер
	AbilitySystemComponent->ServerSetReplicatedTargetData(
		GetAbilitySpecHandle(),
		GetActivationPredictionKey(),
		DataHandle, FGameplayTag(),
		AbilitySystemComponent->ScopedPredictionKey);
	// Эта функция должна быть вызвана перед передачей делегатов обратно в граф способностей. Это позволяет убедиться, что способность все еще активна.
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		TargetDataCursorTrace.Broadcast(DataHandle);
	}
}

void UTargetDataUnderCursor::OnTargetDataReplicatedCallback(const FGameplayAbilityTargetDataHandle& TargetDataHandle,
	FGameplayTag GameplayTag)
{// Потребляет кэшированные данные TargetData от клиента (только TargetData), и сообщает что целевые данные получены, далее чистит AbilityTargetDataMap от нашего TargetData_SingleTargetHit
	AbilitySystemComponent->ConsumeClientReplicatedTargetData(GetAbilitySpecHandle(),GetActivationPredictionKey());
	//далее проверяем что способность активна и отправляем данные
	if(ShouldBroadcastAbilityTaskDelegates())
	{	// через наш личный делегат передаем координаты
		TargetDataCursorTrace.Broadcast(TargetDataHandle);
	}
}
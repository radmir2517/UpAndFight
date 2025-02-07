// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "UpFightInputConfig.h"
#include "UpFightEnhancedInputComponent.generated.h"


/**
 * 
 */
UCLASS()
class UPANDFIGHT_API UUpFightEnhancedInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	// функция бинда InputActions(лкм,пкм, 1,2,3) для вызова функции в ASC
	template<class UserClass, typename PressedFunc,  typename TriggeredFunc, typename ReleasedFunc>
	void BindActions(UUpFightInputConfig* InputConfig, UserClass* Object, PressedFunc PressedF, TriggeredFunc HeldF,ReleasedFunc ReleasedF);
};
// функция бинда InputActions(лкм,пкм, 1,2,3) для вызова функции в ASC
template <class UserClass, typename PressedFunc, typename HeldFunc, typename ReleasedFunc>
void UUpFightEnhancedInputComponent::BindActions(UUpFightInputConfig* InputConfig, UserClass* Object, PressedFunc PressedF, HeldFunc HeldF, ReleasedFunc ReleasedF)
{
	check(InputConfig);

	if(InputConfig->InputActions.IsEmpty() || !IsValid(Object)) return;

	for(FUpFightInputAction& Config:InputConfig->InputActions)
	{
		if(PressedF)
		{
			BindAction(Config.InputAction,ETriggerEvent::Started,Object,PressedF,Config.InputTag);
		}
		if(HeldF)
		{
			BindAction(Config.InputAction,ETriggerEvent::Triggered,Object,HeldF,Config.InputTag);
		}
		if(ReleasedF)
		{
			BindAction(Config.InputAction,ETriggerEvent::Completed,Object,ReleasedF,Config.InputTag);
		}
	}
}

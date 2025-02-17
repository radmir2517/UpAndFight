// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "UpFightAIController.generated.h"

class UBehaviorTreeComponent;
/**
 * 
 */
UCLASS()
class UPANDFIGHT_API AUpFightAIController : public AAIController
{
	GENERATED_BODY()
public:

	AUpFightAIController();
	UPROPERTY(VisibleAnywhere, Category="AI")
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent;

protected:

};

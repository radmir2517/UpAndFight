// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/UpFightAIController.h"

#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

AUpFightAIController::AUpFightAIController()
{
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>("BehaviorTreeComponent");

	Blackboard = CreateDefaultSubobject<UBlackboardComponent>("BlackboardComponent");
}



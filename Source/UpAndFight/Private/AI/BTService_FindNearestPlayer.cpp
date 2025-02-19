// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTService_FindNearestPlayer.h"

#include "AIController.h"
#include "BehaviorTree/BTFunctionLibrary.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

void UBTService_FindNearestPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	GEngine->AddOnScreenDebugMessage(0,5.f,FColor::Blue,AIOwner->GetName());
	GEngine->AddOnScreenDebugMessage(0,5.f,FColor::Red,ActorOwner->GetName());

	const APawn* PawnOwner = AIOwner->GetPawn();
	const FName TargetTag = PawnOwner->ActorHasTag(FName("Player")) ? FName("Enemy") : FName("Player") ;

	TArray<AActor*> AllNearActors;
	UGameplayStatics::GetAllActorsOfClassWithTag(AIOwner,ACharacter::StaticClass(),TargetTag,AllNearActors);

	AActor* NearestTargetActor = nullptr;
	float DistanceToTarget = TNumericLimits<float>::Max();
	for(AActor* Actor : AllNearActors)
	{
		if(IsValid(Actor) && (IsValid(PawnOwner)))
		{
			float Distance = Actor->GetDistanceTo(PawnOwner);
			if(Distance < DistanceToTarget )
			{
				NearestTargetActor = Actor;
				DistanceToTarget = Distance;
			}
		}
	}
	
	UBTFunctionLibrary::SetBlackboardValueAsFloat(this,DistanceToTargetActor,DistanceToTarget);
	UBTFunctionLibrary::SetBlackboardValueAsObject(this,TargetActor,NearestTargetActor);
}

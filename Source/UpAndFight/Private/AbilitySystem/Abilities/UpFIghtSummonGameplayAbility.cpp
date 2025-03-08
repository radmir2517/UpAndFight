// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/UpFIghtSummonGameplayAbility.h"
/*  Это мой старый вариант
void UUpFIghtSummonGameplayAbility::SummonMinions(const int32 InCount, const float InDistance)
{
	if(InCount == 0) return;
	
	AActor* AvatarActor = GetAvatarActorFromActorInfo();
	FVector Origin = AvatarActor->GetActorLocation();

	FVector ForwardVector = AvatarActor->GetActorForwardVector();
	ForwardVector.Normalize();
	DrawDebugLine(AvatarActor->GetWorld(), Origin, Origin + (ForwardVector * InDistance) , FColor::White,false,2.f);
	

	FVector RightVector = AvatarActor->GetActorRightVector();
	RightVector.Normalize();
	DrawDebugLine(AvatarActor->GetWorld(), Origin, Origin + (RightVector * InDistance) , FColor::White,false,2.f);
	
	double Delta = 180.f/InCount;

	TArray<FVector> SpawnLocation;

	if(InCount == 1) return;
	
	else
	{
		for(int32 i = 0; i <= InCount - 1; i++)
		{
			FVector RotateVector = RightVector.RotateAngleAxis(-Delta * i, FVector::UpVector) * InDistance;
			FVector NewPosition = Origin + RotateVector;
			DrawDebugLine(AvatarActor->GetWorld(), Origin, NewPosition, FColor::Red,false,3.f);
			DrawDebugSphere(AvatarActor->GetWorld(), NewPosition, 10.f, 10,  FColor::Red,false, 3.f);
			SpawnLocation.Add(NewPosition);
		}
		
	}
	
}
*/
TArray<FVector> UUpFIghtSummonGameplayAbility::GetSpawnLocations()
{
	// получим вектор местоположения и вектор направленный вперед 
	const FVector Forward = GetAvatarActorFromActorInfo()->GetActorForwardVector();
	const FVector Location = GetAvatarActorFromActorInfo()->GetActorLocation();
	const float DeltaSpread = SpawnSpread / NumMinions;

	// определим левый угол
	const FVector LeftOfSpread = Forward.RotateAngleAxis(-SpawnSpread / 2.f, FVector::UpVector);
	TArray<FVector> SpawnLocations;
	
	for (int32 i = 0; i < NumMinions; i++)
	{	// будем поворачивать вектор на дельту
		const FVector Direction = LeftOfSpread.RotateAngleAxis(DeltaSpread * i, FVector::UpVector);
		FVector ChosenSpawnLocation = Location + Direction * FMath::FRandRange(MinSpawnDistance, MaxSpawnDistance);
		// чтобы спавнились не в воздухе или или под землей сделаем трассировку чтобы на земле было
		FHitResult Hit;
		GetWorld()->LineTraceSingleByChannel(Hit, ChosenSpawnLocation + FVector(0.f, 0.f, 400.f), ChosenSpawnLocation - FVector(0.f, 0.f, 400.f), ECC_Visibility);
		if (Hit.bBlockingHit)
		{
			ChosenSpawnLocation = Hit.ImpactPoint;
		}
		SpawnLocations.Add(ChosenSpawnLocation);
		DrawDebugSphere(GetAvatarActorFromActorInfo()->GetWorld(), ChosenSpawnLocation, 10.f, 10,  FColor::Red,false, 3.f);
	}
	
	return SpawnLocations;
}

TSubclassOf<APawn> UUpFIghtSummonGameplayAbility::GetRandomMinionClass()
{
	const int32 Selection = FMath::RandRange(0, MinionClasses.Num() - 1);
	return MinionClasses[Selection];
}



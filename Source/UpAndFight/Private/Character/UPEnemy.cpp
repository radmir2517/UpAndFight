// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/UPEnemy.h"
#include "UpAndFight/UpAndFight.h"

AUPEnemy::AUPEnemy()
{
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility,ECR_Block);
}

void AUPEnemy::HighlightActor()
{
	GetMesh()->SetCustomDepthStencilValue(true);
	Weapon->SetRenderCustomDepth(true);
}

void AUPEnemy::UnHighlightActor()
{
	GetMesh()->SetCustomDepthStencilValue(false);
	Weapon->SetRenderCustomDepth(false);
}


// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/UPEnemy.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/UpFightAbilitySystemLibrary.h"
#include "AbilitySystem/UpFightAttributeSet.h"
#include "AbilitySystem/UpFightSystemComponent.h"
#include "AI/UpFightAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UI/Widget/UpFightUserWidget.h"
#include "UI/WidgetController/EnemyWidgetController.h"
#include "UpAndFight/UpAndFight.h"

AUPEnemy::AUPEnemy()
{
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility,ECR_Block);

	HealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("HealthWidgetComponent");
	HealthWidgetComponent->SetupAttachment(GetRootComponent());
	
	// создадим компонент AbilitySystemComponent и сделаем его реплицируемым
	AbilitySystemComponent = CreateDefaultSubobject<UUpFightSystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);	// Сделаем его реплицуемым
	AttributeSet = CreateDefaultSubobject<UUpFightAttributeSet>("AttributeSet");
	// режим мультипликации минималльный, т.к это ИИ и ему не нужно репликации эффектов
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	AbilitySystemComponent->SetIsReplicated(true);
	// укажем чтобы новый тип коллизии враг делал Overlap
	GetMesh()->SetCollisionResponseToChannel(ECC_Projectile, ECR_Overlap);
	GetMesh()->SetGenerateOverlapEvents(true);
	
}

void AUPEnemy::BeginPlay()
{
	Super::BeginPlay();
	// инцилизируем систему способностей у врага
	InitAbilityInfo();
	InitEnemyWidget();
	if(!HasAuthority()) return;
	// give абилку GA_HitReact
	UUpFightAbilitySystemLibrary::GiveStartupAbilities(this,AbilitySystemComponent);
}

void AUPEnemy::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	// т.к PossessedBy вызывается лишь сервере, скажем чтобы на клиенте он сразу выходил из него
	if(!HasAuthority()) return;
	check(BehaviorTree);
	// кастуем на наш контроллер
	AUpFightAIController* UpFightAIController = Cast<AUpFightAIController>(NewController);
	// далее инициализируем BlackboardComponent() доской назначенной в дереве
	UpFightAIController->GetBlackboardComponent()->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
	// далле запустим работы нашего дерева
	UpFightAIController->RunBehaviorTree(BehaviorTree);
	
	
}

void AUPEnemy::InitAbilityInfo()
{
	// сообщаем кто avatar actor и кто Owner
	AbilitySystemComponent->InitAbilityActorInfo(this,this);
	// вызов привязки делегата OnGameplayEffectAppliedToSelf к нашей функции в AbilitySystemComponent
	Cast<UUpFightSystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();
	if(!HasAuthority()){return;}
	InitializeDefaultAttributes();
	
}

void AUPEnemy::HighlightActor_Implementation()
{
	GetMesh()->SetRenderCustomDepth(true);
	Weapon->SetRenderCustomDepth(true);
}

void AUPEnemy::UnHighlightActor_Implementation()
{
	GetMesh()->SetRenderCustomDepth(false);
	Weapon->SetRenderCustomDepth(false);
}

int32 AUPEnemy::GetPlayerLevel_Implementation()
{
	return Level;
}



UEnemyWidgetController* AUPEnemy::GetEnemyWidgetController()
{
	if(!IsValid(EnemyWidgetController))
	{
		EnemyWidgetController = NewObject<UEnemyWidgetController>(this,EnemyWidgetControllerClass);
		APlayerController* PC = UGameplayStatics::GetPlayerController(this,0);
		FWidgetControllerParams Param(PC,GetPlayerState(),AbilitySystemComponent,AttributeSet);
		EnemyWidgetController->SetWidgetControllerParams(Param);
	}
	return EnemyWidgetController;
}

void AUPEnemy::InitEnemyWidget()
{
	check(EnemyWidgetControllerClass);
	check(EnemyHealthWidgetClass);
	
	UUserWidget* UserWidget = CreateWidget<UUserWidget>(GetWorld(),EnemyHealthWidgetClass);
	HeathWidget = Cast<UUpFightUserWidget>(UserWidget);
	HeathWidget->SetWidgetController(GetEnemyWidgetController());
	
	EnemyWidgetController->BindCallBacksToDependencies();
	EnemyWidgetController->BroadcastInitialValues();
	
	HealthWidgetComponent->SetWidget(HeathWidget);

	HealthWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	HealthWidgetComponent->SetRelativeLocation(FVector(0.f,0.f, 80.f));
	HealthWidgetComponent->SetDrawSize(FVector2D(100.f,10.f));
	HealthWidgetComponent->SetWidgetClass(EnemyHealthWidgetClass);
	HealthWidgetComponent->SetWidget(HeathWidget);
	
	
	//HeathWidget->SetVisibility(ESlateVisibility::Hidden);
}


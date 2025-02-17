

#include "Player/UpFightPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "AbilitySystem/UpFightSystemComponent.h"
#include "Character/UPCharacter.h"
#include "Input/UpFightEnhancedInputComponent.h"
#include "Interaction/EnemyInterface.h"
#include "UI/Widget/DamageWidgetComponent.h"


AUpFightPlayerController::AUpFightPlayerController()
{
	// контроллер будет реплицирован другим участинкам сети
	bReplicates = true;
}

void AUpFightPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	CursorTrace();
}



void AUpFightPlayerController::CursorTrace()
{
		
	GetHitResultUnderCursor(ECC_Visibility,false,HitResult);

	LastActor = ThisActor;
	
	if(!HitResult.bBlockingHit) return;

	if(HitResult.GetActor()->Implements<UEnemyInterface>())
	{
		
		ThisActor = HitResult.GetActor();
	}
	else
	{
		ThisActor = nullptr;
	}

	if(ThisActor == nullptr)
	{
		if(ThisActor == LastActor)
		{
			// ничего не делаем
		}
		else //(ThisActor != LastActor)
		{
			IEnemyInterface::Execute_UnHighlightActor(LastActor);
		}
	}
	else //(ThisActor != nullptr)
	{
		if(ThisActor == LastActor)
		{
			// ничего не делаем
		}
		else //(ThisActor != LastActor)
		{
			IEnemyInterface::Execute_HighlightActor(ThisActor);
		}
	}
}



void AUpFightPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(MoveActionMapping);
	// создадим субсистему и сделаем ее как enhanced
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if(Subsystem)
	{
		// добавим в него наш контекст
		Subsystem->AddMappingContext(MoveActionMapping,0);
	}
	// курсор будет виден всегда и он будет обычным
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	// по умолчанию поставим чтобы курсор не скрывался и не был lock в Viewport
	FInputModeGameAndUI InputGameMode;
	InputGameMode.SetHideCursorDuringCapture(false);
	InputGameMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	SetInputMode(InputGameMode);
}




void AUpFightPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UUpFightEnhancedInputComponent* EnhancedInputComponent = CastChecked<UUpFightEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered, this, &AUpFightPlayerController::Move);
	
	//EnhancedInputComponent->BindAction(CTRLAction,ETriggerEvent::Started, this, &AUpFightPlayerController::IsCTRLPressed,true);
	//EnhancedInputComponent->BindAction(CTRLAction,ETriggerEvent::Completed, this, &AUpFightPlayerController::IsCTRLPressed, false);
	// функция бинда InputActions(лкм,пкм, 1,2,3) для вызова функции в ASC
	EnhancedInputComponent->BindActions(InputConfig,this,&ThisClass::AbilityInputTagPressed,&ThisClass::AbilityInputTagHeld, &ThisClass::AbilityInputTagReleased);
}

void AUpFightPlayerController::Move(const FInputActionValue& InputActionValue)
{
	// т.к мы задали вектор 2D то получим в нем
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	// нам интересует поворот лишь
	const FRotator YawRotation = FRotator(0.f,Rotation.Yaw, 0.f);
	// направления движения вперед и вправо
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	// получим пешку и будем двигать
	if(APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection,InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection,InputAxisVector.X);
	}
}

void AUpFightPlayerController::ShowDamageNumber_Implementation(ACharacter* TargetCharacter, const float Value)
{
	UDamageWidgetComponent* DamageWidgetComponent = NewObject<UDamageWidgetComponent>(TargetCharacter,DamageWidgetComponentClass);

	DamageWidgetComponent->AttachToComponent(TargetCharacter->GetMesh(),FAttachmentTransformRules::KeepRelativeTransform);
	DamageWidgetComponent->SetRelativeLocation(FVector(0.f,-100.f,120.f));
	DamageWidgetComponent->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	DamageWidgetComponent->RegisterComponent();
	DamageWidgetComponent->SetTextDamage(Value);
}


void AUpFightPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	GEngine->AddOnScreenDebugMessage(1,3.f,FColor::Red,FString::Printf(TEXT("AbilityInputTagPressed InputTag: %s"),*InputTag.ToString()));
}

void AUpFightPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	UUpFightSystemComponent* UpFightASC =  Cast<UUpFightSystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetCharacter()));
	UpFightASC->AbilityInputTagHeld(InputTag);
}
void AUpFightPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	UUpFightSystemComponent* UpFightASC =  Cast<UUpFightSystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetCharacter()));
	UpFightASC->AbilityInputTagReleased(InputTag);
}





#include "Player/UpFightPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"



AUpFightPlayerController::AUpFightPlayerController()
{
	// контроллер будет реплицирован другим участинкам сети
	bReplicates = true;
}

void AUpFightPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(MoveActionMapping);
	// создадим субсистему и сделаем ее как enhanced
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	// добавим в него наш контекст
	Subsystem->AddMappingContext(MoveActionMapping,0);
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

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered, this, &AUpFightPlayerController::Move);
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

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "UpFightPlayerController.generated.h"

struct FInputActionValue;
class UInputMappingContext;
class UInputAction;
/**
 * 
 */
UCLASS()
class UPANDFIGHT_API AUpFightPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void SetupInputComponent() override;

	AUpFightPlayerController();
protected:
	virtual void BeginPlay() override;

	void Move(const FInputActionValue& InputActionValue);
private:
	UPROPERTY(EditDefaultsOnly, Category="Combat")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditDefaultsOnly, Category="Combat")
	TObjectPtr<UInputMappingContext> MoveActionMapping;
};

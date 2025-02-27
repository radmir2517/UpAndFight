
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "UpFightPlayerController.generated.h"

class UDamageWidgetComponent;
class UUpFightInputConfig;
struct FGameplayTag;
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

	virtual void Tick(float DeltaSeconds) override;
	UFUNCTION(Client,Reliable)
	void ShowDamageNumber(ACharacter* TargetCharacter, float Value);
protected:
	virtual void BeginPlay() override;

	void Move(const FInputActionValue& InputActionValue);

	

private:
	// функции которые будут использоваться при разных срабатыванию(при нажатии,отпускания,зажатия)
	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);

	void CursorTrace();

	//void IsCTRLPressed(bool IsPressed);
	
	UPROPERTY(EditDefaultsOnly, Category="Combat")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditDefaultsOnly, Category="Combat")
	TObjectPtr<UInputAction> CTRLAction;
	
	UPROPERTY(EditDefaultsOnly, Category="Combat")
	TObjectPtr<UInputMappingContext> MoveActionMapping;

	UPROPERTY(EditDefaultsOnly, Category="Combat")
	TObjectPtr<UUpFightInputConfig> InputConfig;

	UPROPERTY(EditDefaultsOnly, Category="Combat")
	TSubclassOf<UDamageWidgetComponent> DamageWidgetComponentClass;

	//bool bCTRLPressed = false;

	FHitResult HitResult;

	TObjectPtr<AActor> ThisActor;
	TObjectPtr<AActor> LastActor;
};

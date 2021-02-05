// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ToonTanks/Pawns/PawnBase.h"
#include "PawnTank.generated.h"

class USpringArmComponent;
class UCameraComponent;

/**
 * 
 */
UCLASS()
class TOONTANKS_API APawnTank : public APawnBase
{
	GENERATED_BODY()

private:

	enum eAimStrategy
	{
		eAimStrategy_First = 0,
		eAimStrategy_Mouse = eAimStrategy_First,
		eAimStrategy_Joystick,
		eAimStrategy_Total
	};

	class IPlayerAimInputStrategy
	{
		public:
			virtual ~IPlayerAimInputStrategy() {}
			virtual void Execute(APawnTank* pPlayer) = 0;
	};

	class JoystickAimInput : public IPlayerAimInputStrategy
	{
		friend IPlayerAimInputStrategy;
		public:
			void Execute(APawnTank* pPlayer) override;
	};

	class MouseAimInput : public IPlayerAimInputStrategy
	{
		friend IPlayerAimInputStrategy;
		public:
			void Execute(APawnTank* pPlayer) override;
	};

	// This strategy is selected based on the input of the player
	// if he uses the mouse to aim, it automatically changes to the mouse implementation
	// if he uses the joystick, then it uses the joystick implementation
	// default implementation is mouse
	IPlayerAimInputStrategy* PlayerAimStrategy;
	// all instances of the aim strategy
	IPlayerAimInputStrategy* ConcreteAimStrategy[eAimStrategy_Total];

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* CameraView;

	FVector MoveDirection;
	FQuat RotationDirection;
	FQuat TurretRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float MoveSpeed = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float RotateSpeed = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float TurretRotateSpeed = 100.f;


	void CalculateMoveInput(float Value);
	void CalculateRotateInput(float Value);
	void CalculateTurretRotationOnX(float Value);
	void CalculateTurretRotationOnY(float Value);

	void Move();
	void Rotate();

	double angleOnX = 0.;
	double angleOnY = 0.;


	APlayerController* SelfReference = nullptr;
	bool isPlayerAlive = true;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Constructor
	APawnTank();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void HandleDestruction() override;

	bool IsPlayerAlive() const;

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateHealthBar(float CurrentHealth, float MaxHealth);

};


FORCEINLINE bool APawnTank::IsPlayerAlive() const
{
	return isPlayerAlive;
}



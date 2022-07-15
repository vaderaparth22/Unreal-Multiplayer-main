// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSAiCharacter.generated.h"

class UPawnSensingComponent;
UENUM(BlueprintType)
enum class EAIState : uint8
{
	Idle,
	Suspicious,
	Alert
};

UCLASS()
class UNREALMULTIPLAYER_API AFPSAiCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSAiCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere,Category="Component")
	UPawnSensingComponent* PawnSensingComp;

	UFUNCTION()
	void OnPawnSeen(APawn* Pawn);

	UFUNCTION()
	void OnHearSound(APawn* NoiseInstigator, const FVector& Location, float Volume);

	UPROPERTY(EditInstanceOnly, Category = "Rotation")
	float rotationSpeed;

	UPROPERTY(ReplicatedUsing=OnRep_GuardState)
	EAIState AIGuardState;

	UFUNCTION()
	void OnRep_GuardState();

	void SetGuardState(EAIState NewState);


	FTimerHandle TimerHandle_ResetOrientation;
	UFUNCTION(BlueprintImplementableEvent, Category = "AI")
	void OnstateChange(EAIState SetState);

	void ResetOrientation();


	UPROPERTY(EditInstanceOnly, Category = "AI")
	bool bPatrol;

	UPROPERTY(EditInstanceOnly, Category = "AI",meta = (EditCondition ="bPatrol"))
	AActor* FirstPatrolPoint;
	UPROPERTY(EditInstanceOnly, Category = "AI", meta = (EditCondition = "bPatrol"))
	AActor* SecondPatrolPoint;

	AActor* CurrentPatrolPoint;

	FRotator OrignalRotation;

	void MoveToNextPatrolPoint();
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};

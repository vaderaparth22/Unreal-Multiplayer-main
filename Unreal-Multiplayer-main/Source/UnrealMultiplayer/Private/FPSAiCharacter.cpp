// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSAiCharacter.h"
#include "perception/PawnSensingComponent.h"
#include "DrawDebugHelpers.h"
#include "UnrealMultiplayer/UnrealMultiplayerGameMode.h"
#include "Engine/EngineTypes.h"
#include "NavigationSystem.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AFPSAiCharacter::AFPSAiCharacter()
{
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensing"));
	AIGuardState = EAIState::Idle;
	OrignalRotation = GetActorRotation();
	if (bPatrol)
	{
		MoveToNextPatrolPoint();
	}
}

// Called when the game starts or when spawned
void AFPSAiCharacter::BeginPlay()
{
	PawnSensingComp->OnSeePawn.AddDynamic(this, &AFPSAiCharacter::OnPawnSeen);
	PawnSensingComp->OnHearNoise.AddDynamic(this, &AFPSAiCharacter::OnHearSound);
	Super::BeginPlay();
}

void AFPSAiCharacter::OnPawnSeen(APawn* Pawn)
{
	if (Pawn == nullptr)
	{
		return;
	}
	DrawDebugSphere(GetWorld(), Pawn->GetActorLocation(), 32.0f, 12, FColor::Yellow, false, 10.0f);
	AUnrealMultiplayerGameMode* ugm = Cast<AUnrealMultiplayerGameMode>(Pawn->GetWorld()->GetAuthGameMode());
	if (ugm)
	{
		ugm->CompleteMission(Pawn, false);
	}
	SetGuardState(EAIState::Alert);

	AController* controler = GetController();
	if (controler)
	{
		controler->StopMovement();
	}
}

void AFPSAiCharacter::OnHearSound(APawn* NoiseInstigator, const FVector& Location, float Volume)
{
	if (AIGuardState == EAIState::Alert)
	{
		return;
	}

	DrawDebugSphere(GetWorld(), NoiseInstigator->GetActorLocation(), 32.0f, 12, FColor::Red, false, 10.0f);
	FVector Direction = Location - GetActorLocation();
	Direction.Normalize();
	FRotator NewLookAt = FRotationMatrix::MakeFromX(Direction).Rotator();
	NewLookAt.Pitch = 0.0f;
	NewLookAt.Roll = 0.0f;
	SetActorRotation(NewLookAt * rotationSpeed);
	GetWorldTimerManager().ClearTimer(TimerHandle_ResetOrientation);
	GetWorldTimerManager().SetTimer(TimerHandle_ResetOrientation, this, &AFPSAiCharacter::ResetOrientation, 3.0f);
	SetGuardState(EAIState::Suspicious);
}

void AFPSAiCharacter::OnRep_GuardState()
{
	OnstateChange(AIGuardState);
}

void AFPSAiCharacter::SetGuardState(EAIState NewState)
{
	if (NewState == AIGuardState)
	{
		return;
	}
	AIGuardState = NewState;
	OnRep_GuardState();
}

void AFPSAiCharacter::ResetOrientation()
{
	if (AIGuardState == EAIState::Alert)
	{
		return;
	}
	SetActorRotation(OrignalRotation);
	SetGuardState(EAIState::Idle);
	if (bPatrol)
	{
		MoveToNextPatrolPoint();
	}
}

void AFPSAiCharacter::MoveToNextPatrolPoint()
{
	if (CurrentPatrolPoint == nullptr || CurrentPatrolPoint == SecondPatrolPoint)
	{
		CurrentPatrolPoint = FirstPatrolPoint;
	}
	else
	{
		CurrentPatrolPoint = SecondPatrolPoint;
	}

	UNavigationSystemV1::SimpleMoveToActor(GetController(), CurrentPatrolPoint);
}

// Called every frame
void AFPSAiCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (CurrentPatrolPoint)
	{
		FVector Delta = GetActorLocation() - CurrentPatrolPoint->GetActorLocation();
		float DistanceToAGoal = Delta.Size();
		if (DistanceToAGoal < 50)
		{
			MoveToNextPatrolPoint();
		}
	}
}


void AFPSAiCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AFPSAiCharacter, AIGuardState);
}

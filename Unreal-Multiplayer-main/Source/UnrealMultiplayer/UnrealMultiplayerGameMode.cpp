// Copyright Epic Games, Inc. All Rights Reserved.

#include "UnrealMultiplayerGameMode.h"
#include "UnrealMultiplayerHUD.h"
#include "UnrealMultiplayerCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "kismet/GameplayStatics.h"
#include "FPSGameState.h"

AUnrealMultiplayerGameMode::AUnrealMultiplayerGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(
		TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AUnrealMultiplayerHUD::StaticClass();
	GameStateClass = AFPSGameState::StaticClass();
}

void AUnrealMultiplayerGameMode::CompleteMission(APawn* instigatorPawn, bool IsMissionSuccess)
{
	if (instigatorPawn)
	{
		if (SpectatingViewPoint)
		{
			TArray<AActor*> ReturnActors;

			UGameplayStatics::GetAllActorsOfClass(this, SpectatingViewPoint, ReturnActors);

			if (ReturnActors.Num() > 0)
			{
				AActor* NewActor = ReturnActors[0];


				for (FConstPlayerControllerIterator PlayerControllerIterator = GetWorld()->GetPlayerControllerIterator()
				     ;
				     PlayerControllerIterator; ++PlayerControllerIterator++)
				{
					APlayerController* pc = PlayerControllerIterator->Get();
					if (pc)
					{
						pc->SetViewTargetWithBlend(NewActor, 0.5f, VTBlend_Cubic);
					}
				}
			}
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("Viewport Has not Been Setted to the base class Its null Pls Set the ViewPort"))
		}
	}
	AFPSGameState* AfpsGameState = GetGameState<AFPSGameState>();
	if (AfpsGameState)
	{
		AfpsGameState->MultiClassOnMissionComplete(instigatorPawn, IsMissionSuccess);
	}


	OnMissionComplete(instigatorPawn, IsMissionSuccess);
}

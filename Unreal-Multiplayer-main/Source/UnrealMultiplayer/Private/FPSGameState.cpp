// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSGameState.h"
#include "FPSPlayerController.h"

void AFPSGameState::MultiClassOnMissionComplete_Implementation(APawn* InstigatorPawn, bool IsMissionSucess)
{
	//for (FConstPawnIterator FIterator = InstigatorPawn->GetWorld()->GetPawnIterator(); FIterator; ++FIterator)
	//{
	//	APawn* pawn = FIterator->Get();
	//	if (pawn && pawn->IsLocallyControlled())
	//	{
	//		pawn->DisableInput(nullptr);
	//	}
	//}
	for (FConstPlayerControllerIterator PlayerControllerIterator = GetWorld()->GetPlayerControllerIterator();
	     PlayerControllerIterator; ++PlayerControllerIterator++)
	{
		AFPSPlayerController* fpsPlayerController = Cast<AFPSPlayerController>(PlayerControllerIterator->Get());
		if (fpsPlayerController && fpsPlayerController->IsLocalController())
		{
			fpsPlayerController->OnMissionComplete(InstigatorPawn, IsMissionSucess);
			APawn* pawn = fpsPlayerController->GetPawn();
			if (pawn)
			{
				pawn->DisableInput(fpsPlayerController);
			}
		}
	}
}

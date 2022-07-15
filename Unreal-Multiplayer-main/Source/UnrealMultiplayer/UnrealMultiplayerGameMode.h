// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UnrealMultiplayerGameMode.generated.h"

UCLASS(minimalapi)
class AUnrealMultiplayerGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AUnrealMultiplayerGameMode();

	void CompleteMission(APawn* instigatorPawn, bool IsMissionSuccess);

	UFUNCTION(BlueprintImplementableEvent,Category ="GameMode")
	void OnMissionComplete(APawn* instigatorpawn, bool IsMissionSuccess);
protected:
	UPROPERTY(EditDefaultsOnly,Category="Spectating")
	TSubclassOf<AActor> SpectatingViewPoint;
};




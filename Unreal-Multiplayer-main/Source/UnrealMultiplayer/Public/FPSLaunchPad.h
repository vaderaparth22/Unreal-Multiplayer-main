// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSLaunchPad.generated.h"

class UStaticMeshComponent;
class UBoxComponent;
class UParticleSystem;
UCLASS()
class UNREALMULTIPLAYER_API AFPSLaunchPad : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSLaunchPad();

protected:
	
	UPROPERTY(VisibleAnywhere,Category="Component")
	UStaticMeshComponent* BoxMesh;
	UPROPERTY(VisibleAnywhere,Category="Component")
	UBoxComponent* Box;
	UPROPERTY(EditInstanceOnly,Category="LaunchPad")
	float LaunchStregth;
	UPROPERTY(EditInstanceOnly,Category="LaunchPad")
	float LaunchAngle;
	UPROPERTY(EditDefaultsOnly,Category="ParticalEffect")
	UParticleSystem* particleeffect;
public:
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};

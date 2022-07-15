// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSObjectiveActor.generated.h"


class UStaticMeshComponent;
class USphereComponent;
class UParticleSystem;

UCLASS()
class UNREALMULTIPLAYER_API AFPSObjectiveActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSObjectiveActor();

protected:
	UPROPERTY(VisibleAnywhere,Category = "Components")
	UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* sp;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "FX")
	UParticleSystem* PickUpFX;

	void PlayEffects();
public:	
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};

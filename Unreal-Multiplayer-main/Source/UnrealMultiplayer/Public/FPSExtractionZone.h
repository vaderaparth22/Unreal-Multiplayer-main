// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSExtractionZone.generated.h"

class UBoxComponent;
class UDecalComponent; 

UCLASS()
class UNREALMULTIPLAYER_API AFPSExtractionZone : public AActor
{
	GENERATED_BODY()
	
public:	

	AFPSExtractionZone();
protected:

	/*void BeginPlay();*/

	UPROPERTY(VisibleAnywhere, Category = "Component")
	UBoxComponent* OverlapComp;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	UDecalComponent* DecalComp;


	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	USoundBase* ObjectiveMissingSound;
	/*UFUNCTION()
	void HandleOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool FromSweep, const FHitResult& SweepResult);*/

public:
	 virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	
	

};

// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSExtractionZone.h"
#include "Components/BoxComponent.h"
#include "UnrealMultiplayer/UnrealMultiplayerCharacter.h"
#include "Components/DecalComponent.h"
#include "UnrealMultiplayer//UnrealMultiplayerGameMode.h"
#include "kismet/GameplayStatics.h"
// Sets default values
AFPSExtractionZone::AFPSExtractionZone()
{

	OverlapComp = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapComp"));
	OverlapComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	OverlapComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	OverlapComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	OverlapComp->SetBoxExtent(FVector(200.0f));
	RootComponent = OverlapComp;

	OverlapComp->SetHiddenInGame(false);
	
	DecalComp = CreateDefaultSubobject<UDecalComponent>(TEXT("DecalComp"));
	DecalComp->DecalSize = FVector(200.0f);
	DecalComp->SetupAttachment(RootComponent);
	

}


//void AFPSExtractionZone::BeginPlay()
//{
//	OverlapComp->OnComponentBeginOverlap.AddDynamic(this, &AFPSExtractionZone::HandleOverlap);
//}

//
//void AFPSExtractionZone::HandleOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool FromSweep, const FHitResult& SweepResult)
//{
//	UE_LOG(LogTemp, Log, TEXT("Overlapped with extraction zone!"));
//}
//

void AFPSExtractionZone::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	AUnrealMultiplayerCharacter* myCharacter = Cast<AUnrealMultiplayerCharacter>(OtherActor);
	
	if (myCharacter == nullptr )
	{
		return;	
	}
	if (myCharacter->IsCarryingObjective)
	{
		AUnrealMultiplayerGameMode* ugm = Cast<AUnrealMultiplayerGameMode>(myCharacter->GetWorld()->GetAuthGameMode());

		if (ugm)
		{
			ugm->CompleteMission(myCharacter,true);
		}
	}
	else
	{
		UGameplayStatics::PlaySound2D(this, ObjectiveMissingSound);
	}
	
}

 


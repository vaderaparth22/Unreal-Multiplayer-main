// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSObjectiveActor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UnrealMultiplayer/UnrealMultiplayerCharacter.h"
// Sets default values
AFPSObjectiveActor::AFPSObjectiveActor()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = MeshComp;

	sp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	sp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	sp->SetCollisionResponseToAllChannels(ECR_Ignore);
	sp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	sp->SetupAttachment(MeshComp);
	SetReplicates(true);
}


void AFPSObjectiveActor::PlayEffects()
{
	UGameplayStatics::SpawnEmitterAtLocation(this, PickUpFX, GetActorLocation());
}

// Called when the game starts or when spawned
void AFPSObjectiveActor::BeginPlay()
{
	Super::BeginPlay();
}


void AFPSObjectiveActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	PlayEffects();

	AUnrealMultiplayerCharacter* myCharacter = Cast<AUnrealMultiplayerCharacter>(OtherActor);
	if (myCharacter)
	{
		myCharacter->IsCarryingObjective = true;
		Destroy();
	}
}

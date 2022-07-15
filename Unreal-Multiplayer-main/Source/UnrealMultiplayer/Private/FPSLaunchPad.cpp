
#include "FPSLaunchPad.h"
#include "components/BoxComponent.h"
#include "UnrealMultiplayer/UnrealMultiplayerCharacter.h"
#include "kismet/GameplayStatics.h"
// Sets default values
AFPSLaunchPad::AFPSLaunchPad()
{

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("BOXComponent"));
	Box->SetBoxExtent(FVector(100, 100, 50));
	RootComponent = Box;
	BoxMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BOXMesh"));
	BoxMesh->SetupAttachment(RootComponent);
	
	LaunchStregth = 100.0f;
	LaunchAngle = 35.0f;
}



void AFPSLaunchPad::NotifyActorBeginOverlap(AActor * OtherActor)
{

	FRotator LaunchDirection = GetActorRotation();
	LaunchDirection.Pitch += LaunchAngle;
	FVector LaunchVelocity = LaunchDirection.Vector() * LaunchStregth;
	AUnrealMultiplayerCharacter* OtherCharacter = Cast<AUnrealMultiplayerCharacter>(OtherActor);
	if (OtherCharacter)
	{
		OtherCharacter->LaunchCharacter(LaunchVelocity, true, true);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), particleeffect, GetActorLocation());
	}

}




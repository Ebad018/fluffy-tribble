#include "AssignAICharacter.h"
#include "AssignAIController.h"

#include "GameFramework/CharacterMovementComponent.h"

AAssignAICharacter::AAssignAICharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	AIControllerClass = AAssignAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	if (GetCharacterMovement())
	{
		GetCharacterMovement()->bOrientRotationToMovement = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	}
}

void AAssignAICharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AAssignAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

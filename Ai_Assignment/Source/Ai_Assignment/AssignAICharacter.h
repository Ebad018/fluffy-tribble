#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AssignAICharacter.generated.h"

UCLASS()
class AI_ASSIGNMENT_API AAssignAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AAssignAICharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
};

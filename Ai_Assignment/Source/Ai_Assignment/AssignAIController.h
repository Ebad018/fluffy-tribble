#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "AssignAIController.generated.h"

class UAIPerceptionComponent;
class UAISenseConfig_Sight;
class UAISenseConfig_Hearing;
class UBehaviorTree;

/**
 * Custom AI Controller for the AI Programming Assignment.
 * Handles Sight and Hearing perception, updates the Blackboard, and triggers Team Alertness.
 */
UCLASS()
class AI_ASSIGNMENT_API AAssignAIController : public AAIController
{
	GENERATED_BODY()

public:
	AAssignAIController();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void OnPossess(APawn* InPawn) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Settings")
	bool bUseSight = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Settings")
	bool bUseHearing = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	UBehaviorTree* BehaviorTreeAsset;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	UAIPerceptionComponent* AIPerceptionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	UAISenseConfig_Sight* SightConfig;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	UAISenseConfig_Hearing* HearingConfig;

	UFUNCTION()
	void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

	// Handles team alertness by telling this AI to investigate a threat found by another AI
	void AlertReceived(AActor* ThreatActor, FVector ThreatLocation);

	// Helper to update the blackboard state
	void UpdateBlackboardState(uint8 NewState);
};

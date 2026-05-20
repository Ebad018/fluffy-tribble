#include "AssignAIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"
#include "GameFramework/Character.h"

// Enum matching our BT states
enum class EAIState : uint8
{
	Patrol = 0,
	Investigate = 1,
	Chase = 2
};

AAssignAIController::AAssignAIController()
{
	AIPerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComp"));

	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	SightConfig->SightRadius = 1500.0f;
	SightConfig->LoseSightRadius = 1800.0f;
	SightConfig->PeripheralVisionAngleDegrees = 60.0f;
	SightConfig->SetMaxAge(5.0f);
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	AIPerceptionComp->ConfigureSense(*SightConfig);

	HearingConfig = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("HearingConfig"));
	HearingConfig->HearingRange = 3000.0f;
	HearingConfig->SetMaxAge(5.0f);
	HearingConfig->DetectionByAffiliation.bDetectEnemies = true;
	HearingConfig->DetectionByAffiliation.bDetectNeutrals = true;
	HearingConfig->DetectionByAffiliation.bDetectFriendlies = true;
	AIPerceptionComp->ConfigureSense(*HearingConfig);

	AIPerceptionComp->SetDominantSense(SightConfig->GetSenseImplementation());
	AIPerceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &AAssignAIController::OnTargetPerceptionUpdated);
	PrimaryActorTick.bCanEverTick = true;
}

void AAssignAIController::BeginPlay()
{
	Super::BeginPlay();

	// Enable or disable senses dynamically based on the bools
	if (!bUseSight)
	{
		AIPerceptionComp->SetSenseEnabled(UAISense_Sight::StaticClass(), false);
	}
	
	if (!bUseHearing)
	{
		AIPerceptionComp->SetSenseEnabled(UAISense_Hearing::StaticClass(), false);
	}
}

void AAssignAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Print UI elements based on blackboard state
	if (UBlackboardComponent* BB = GetBlackboardComponent())
	{
		AActor* Target = Cast<AActor>(BB->GetValueAsObject(TEXT("TargetActor")));
		if (Target && Target == UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
		{
			GEngine->AddOnScreenDebugMessage(1, 0.0f, FColor::Red, TEXT("!!! YOU ARE BEING CHASED !!!"), true, FVector2D(3.0f, 3.0f));
		}
		else if (BB->GetValueAsInt(TEXT("State")) == static_cast<uint8>(EAIState::Investigate))
		{
			GEngine->AddOnScreenDebugMessage(2, 0.0f, FColor::Yellow, TEXT("? NOISE HEARD - INVESTIGATING ?"), true, FVector2D(3.0f, 3.0f));
		}
	}
}

void AAssignAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (BehaviorTreeAsset)
	{
		RunBehaviorTree(BehaviorTreeAsset);
	}
}

void AAssignAIController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (!GetBlackboardComponent()) return;

	if (Stimulus.WasSuccessfullySensed())
	{
		if (Stimulus.Type == UAISense::GetSenseID<UAISense_Sight>())
		{
			// Sight: Chase player
			GetBlackboardComponent()->SetValueAsObject(TEXT("TargetActor"), Actor);
			UpdateBlackboardState(static_cast<uint8>(EAIState::Chase));
			
			// Team Alertness: Notify others
			for (TActorIterator<AAssignAIController> It(GetWorld()); It; ++It)
			{
				AAssignAIController* OtherAI = *It;
				if (OtherAI && OtherAI != this)
				{
					OtherAI->AlertReceived(Actor, Actor->GetActorLocation());
				}
			}
		}
		else if (Stimulus.Type == UAISense::GetSenseID<UAISense_Hearing>())
		{
			// Hearing: Investigate if not already chasing
			if (GetBlackboardComponent()->GetValueAsInt(TEXT("State")) != static_cast<uint8>(EAIState::Chase))
			{
				GetBlackboardComponent()->SetValueAsVector(TEXT("TargetLocation"), Stimulus.StimulusLocation);
				UpdateBlackboardState(static_cast<uint8>(EAIState::Investigate));
			}
		}
	}
	else
	{
		// Lost Sight
		if (Stimulus.Type == UAISense::GetSenseID<UAISense_Sight>())
		{
			GetBlackboardComponent()->ClearValue(TEXT("TargetActor"));
			GetBlackboardComponent()->SetValueAsVector(TEXT("TargetLocation"), Stimulus.StimulusLocation);
			UpdateBlackboardState(static_cast<uint8>(EAIState::Investigate));
		}
	}
}

void AAssignAIController::AlertReceived(AActor* ThreatActor, FVector ThreatLocation)
{
	if (!GetBlackboardComponent()) return;

	// Only react if we are patrolling (don't interrupt an existing chase or investigate)
	if (GetBlackboardComponent()->GetValueAsInt(TEXT("State")) == static_cast<uint8>(EAIState::Patrol))
	{
		GetBlackboardComponent()->SetValueAsVector(TEXT("TargetLocation"), ThreatLocation);
		UpdateBlackboardState(static_cast<uint8>(EAIState::Investigate));
	}
}

void AAssignAIController::UpdateBlackboardState(uint8 NewState)
{
	if (GetBlackboardComponent())
	{
		GetBlackboardComponent()->SetValueAsInt(TEXT("State"), NewState);
	}
}

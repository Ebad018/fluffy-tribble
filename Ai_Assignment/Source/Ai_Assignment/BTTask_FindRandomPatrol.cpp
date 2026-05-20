#include "BTTask_FindRandomPatrol.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "NavigationSystem.h"

UBTTask_FindRandomPatrol::UBTTask_FindRandomPatrol()
{
	NodeName = TEXT("Find Random Patrol Point");
}

EBTNodeResult::Type UBTTask_FindRandomPatrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController) return EBTNodeResult::Failed;

	APawn* AIPawn = AIController->GetPawn();
	if (!AIPawn) return EBTNodeResult::Failed;

	UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(GetWorld());
	if (!NavSys) return EBTNodeResult::Failed;

	FNavLocation RandomLocation;
	bool bFound = NavSys->GetRandomReachablePointInRadius(AIPawn->GetActorLocation(), SearchRadius, RandomLocation);

	if (bFound)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(BlackboardKey.SelectedKeyName, RandomLocation.Location);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}

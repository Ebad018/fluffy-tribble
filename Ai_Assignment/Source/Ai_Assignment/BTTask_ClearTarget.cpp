#include "BTTask_ClearTarget.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_ClearTarget::UBTTask_ClearTarget()
{
	NodeName = TEXT("Clear Target");
}

EBTNodeResult::Type UBTTask_ClearTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (OwnerComp.GetBlackboardComponent())
	{
		OwnerComp.GetBlackboardComponent()->ClearValue(BlackboardKey.SelectedKeyName);
		OwnerComp.GetBlackboardComponent()->SetValueAsInt(TEXT("State"), 0); // EAIState::Patrol
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}

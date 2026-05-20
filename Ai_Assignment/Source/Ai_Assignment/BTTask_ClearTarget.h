#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_ClearTarget.generated.h"

UCLASS()
class AI_ASSIGNMENT_API UBTTask_ClearTarget : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_ClearTarget();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};

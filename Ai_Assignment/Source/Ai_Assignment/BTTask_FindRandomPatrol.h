#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_FindRandomPatrol.generated.h"

UCLASS()
class AI_ASSIGNMENT_API UBTTask_FindRandomPatrol : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_FindRandomPatrol();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float SearchRadius = 1500.0f;

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};

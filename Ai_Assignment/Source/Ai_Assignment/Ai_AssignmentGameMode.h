// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Ai_AssignmentGameMode.generated.h"

/**
 *  Simple GameMode for a third person game
 */
UCLASS(abstract)
class AAi_AssignmentGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	
	/** Constructor */
	AAi_AssignmentGameMode();
};




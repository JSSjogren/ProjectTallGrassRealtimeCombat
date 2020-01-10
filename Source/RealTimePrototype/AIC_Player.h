// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include <RealTimePrototype\Trainer.h>
#include "AIC_Player.generated.h"

/**
 * 
 */
UCLASS()
class REALTIMEPROTOTYPE_API AAIC_Player : public AAIController
{
	GENERATED_BODY()

	public:
		void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;
};

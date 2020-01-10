// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Engine.h"
#include "Engine/World.h"
#include "RealTimePrototype\Trainer.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "AIController.h"
#include "Classes/Components/SplineComponent.h"
#include "TrainerController.generated.h"

/**
 * 
 */
UCLASS()
class REALTIMEPROTOTYPE_API ATrainerController : public APlayerController
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
public:
	ATrainerController();
	UFUNCTION()
		void LineTraceOnAttack(FHitResult& HitResult);
		void LineTraceOnInstruct(FHitResult& HitResult);
		void SpawnBattleAreaSpline(FVector CombatStartLocation);
		ATrainer* GetTrainer();
		void SetTrainer(ATrainer * Trainer);

	UFUNCTION(BlueprintCallable)
		void ToggleMainHUD();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = UI)
		TSubclassOf<UUserWidget> MainHUD;

	UPROPERTY(VisibleAnywhere, Category = UI)
		UUserWidget* MainHUDInstance;

	UPROPERTY(VisibleAnywhere, Category = General)
		ATrainer* Trainer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat)
		float MaxCombatClickDistance = 3000;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Combat)
		bool MoveFinished = false;
};

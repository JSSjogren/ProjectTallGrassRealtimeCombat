// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Engine.h"
#include "Engine/World.h"
#include "AIController.h"
#include "Monster.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SplineComponent.h"
#include "Math/TransformNonVectorized.h"
#include "Trainer.generated.h"

UCLASS()
class REALTIMEPROTOTYPE_API ATrainer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATrainer();

private:
	AAIController* AIController;
	AController * OldController;
	AMonster* Sidekick;
	bool MonToggled = false;
	bool CombatStarted = false;
	USplineComponent* BattleSpline;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	float BaseTurnRate = 45.0f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Follower AI Controller Class"), Category = Pawn)
		TSubclassOf<AController> FollowerAIControllerClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Follower Class"), Category = Pawn)
		TSubclassOf<APawn> FollowerClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Battle Area Spline"), Category = Combat)
		TSubclassOf<AActor> BattleAreaSpline;

	UFUNCTION()
		void MoveForward(float AxisValue);
		void MoveRight(float AxisValue);
		void TurnRate(float AxisValue);
		void Turn(float AxisValue);
		void LookUpRate(float AxisValue);
		void LookUp(float AxisValue);
		void Jump();
		void StopJumping();
		void MoveTo(FVector Location);
		void RepossessOldController();
		void ToggleMonster();
		void CheckRightClick();
		void AttemptStartCombat();
		void CombatRightClick();
		void StartCombat(FHitResult HitResult);
		FHitResult LineTrace();
};

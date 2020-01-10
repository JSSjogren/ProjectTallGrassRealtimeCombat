// Fill out your copyright notice in the Description page of Project Settings.

#include "TrainerController.h"
#include "Components/Border.h"
#include "Blueprint/UserWidget.h"


/*
* OnTick, and when in combat, we want the player to be moved onto the path of the spline
* at the location nearest to them. This provides the illusion of moving
* around the BattleAreaSpline.
*/
void ATrainerController::Tick(float DeltaTime) 
{ 
	Super::Tick(DeltaTime);
}

// Called when the game starts or when spawned
void ATrainerController::BeginPlay()
{
	Super::BeginPlay();
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("PlayerController is here!"));
	}

	this->ToggleMainHUD();

	if (!Trainer)
		Trainer = Cast<ATrainer>(this->GetCharacter());
}

ATrainerController::ATrainerController()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}


/*
* Responsible for executing a linetrace and returning the results of the hit.
*/
void ATrainerController::LineTraceOnAttack(FHitResult& HitResult)
{
	FVector StartLocation = PlayerCameraManager->GetCameraLocation();
	FVector EndLocation = PlayerCameraManager->GetActorForwardVector();
	EndLocation = EndLocation * MaxCombatClickDistance;
	EndLocation = EndLocation + StartLocation;

	FCollisionQueryParams TraceParams(FName(TEXT("Attack Trace")), true, nullptr);

	GetWorld()->LineTraceSingleByObjectType(HitResult, StartLocation, EndLocation, ECC_Pawn, TraceParams);
}

void ATrainerController::LineTraceOnInstruct(FHitResult& HitResult)
{
	FVector StartLocation = PlayerCameraManager->GetCameraLocation();
	FVector EndLocation = PlayerCameraManager->GetActorForwardVector();
	EndLocation = EndLocation * MaxCombatClickDistance;
	EndLocation = EndLocation + StartLocation;

	FCollisionQueryParams TraceParams(FName(TEXT("Instruct Trace")), true, nullptr);
	FCollisionResponseParams ResponseParams;

	GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_WorldDynamic, TraceParams, ResponseParams);
}

/*
* Creates and adds the Main HUD to the trainer's screen
*/
void ATrainerController::ToggleMainHUD()
{
	// If MainHUD is set in BP_TrainerController
	if (MainHUD) {
		// If we haven't initialized MainHUD
		if (!MainHUDInstance) {
			// Create a MainHUD instance
			MainHUDInstance = CreateWidget(this, MainHUD);
		}

		// If it isn't visible yet, add it to the viewport!
		if (!MainHUDInstance->GetIsVisible())
		{
			MainHUDInstance->AddToViewport();
		}
		else
		{
			MainHUDInstance->RemoveFromViewport();
		}
	}
}

// Returns or initializes the value of trainer in the TrainerController
ATrainer * ATrainerController::GetTrainer()
{
	if (this->Trainer)
		return this->Trainer;
	else
	{
		ATrainer * Trainer = Cast<ATrainer>(this->GetCharacter());
		this->SetTrainer(Trainer);
		return this->Trainer;
	}
}

// Sets the value of Trainer in the trainer controller
void ATrainerController::SetTrainer(ATrainer* Trainer)
{
	if (!this->Trainer)
	{
		this->Trainer = Trainer;
	}
}

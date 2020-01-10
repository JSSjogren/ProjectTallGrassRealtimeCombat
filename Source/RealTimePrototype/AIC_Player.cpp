// Fill out your copyright notice in the Description page of Project Settings.


#include "AIC_Player.h"

void AAIC_Player::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);

	ATrainer* Trainer = Cast<ATrainer>(this->GetPawn());
	Trainer->RepossessOldController();
}
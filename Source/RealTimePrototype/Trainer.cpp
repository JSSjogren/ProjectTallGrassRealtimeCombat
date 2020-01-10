// Fill out your copyright notice in the Description page of Project Settings.


#include "Trainer.h"
#include <RealTimePrototype\TrainerController.h>

// Sets default values
ATrainer::ATrainer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATrainer::BeginPlay()
{
	Super::BeginPlay();
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("We are using FPSCharacter!"));
	}
	
	// Spawning in an AI Controller for the player. Can be used for AI movements.
	const FVector Location = this->GetActorLocation();
	const FRotator Rotation = FRotator(0.f, 0.f, 0.f);
	AIController = Cast<AAIController>(GetWorld()->SpawnActor(this->AIControllerClass.Get(), &Location, &Rotation));
}

// Called every frame
void ATrainer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// Without this, the player will drift off the circle as they move.
	if (CombatStarted && BattleSpline)
	{
		if (Cast<ATrainerController>(this->GetController()))
		{
			// We need to make sure the player has been moved outside the circle before we do this set location.
			if (Cast<ATrainerController>(this->GetController())->MoveFinished)
			{
				FVector Location = BattleSpline->FindLocationClosestToWorldLocation(this->GetActorLocation(), ESplineCoordinateSpace::World);
				// We don't want to use the Z location of the spline. This will dampen the jump effect which is annoying.
				this->SetActorLocation(FVector(Location.X, Location.Y, this->GetActorLocation().Z));
			}
		}
	}
}

// Called to bind functionality to input
void ATrainer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InputComponent->BindAxis("MoveForward", this, &ATrainer::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ATrainer::MoveRight);
	InputComponent->BindAxis("TurnRate", this, &ATrainer::TurnRate);
	InputComponent->BindAxis("Turn", this, &ATrainer::Turn);
	InputComponent->BindAxis("LookUpRate", this, &ATrainer::LookUpRate);
	InputComponent->BindAxis("LookUp", this, &ATrainer::LookUp);

	InputComponent->BindAction("Jump", IE_Pressed, this, &ATrainer::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &ATrainer::StopJumping);
	InputComponent->BindAction("ToggleMonster", IE_Released, this, &ATrainer::ToggleMonster);
	InputComponent->BindAction("StartCombat", IE_Released, this, &ATrainer::CheckRightClick);
}

void ATrainer::MoveForward(float AxisValue)
{
	if (!CombatStarted)
	{
		FRotator moveOnPlane = FRotator(0.f, this->GetControlRotation().Yaw, 0.f);
		AddMovementInput(FRotationMatrix(moveOnPlane).GetScaledAxis(EAxis::X), AxisValue);
	}
}

void ATrainer::MoveRight(float AxisValue)
{
	if (CombatStarted && BattleSpline)
	{
		if (Cast<ATrainerController>(this->GetController()))
		{
			if (Cast<ATrainerController>(this->GetController())->MoveFinished)
			{
				FVector ClosestLocation = BattleSpline->FindTangentClosestToWorldLocation(this->GetActorLocation(), ESplineCoordinateSpace::Local);
				ClosestLocation = ClosestLocation * -1;
				AddMovementInput(ClosestLocation, AxisValue);
			}
		}
	}
	else
	{
		FRotator moveOnPlane = FRotator(0.f, this->GetControlRotation().Yaw, 0.f);
		AddMovementInput(FRotationMatrix(moveOnPlane).GetScaledAxis(EAxis::Y), AxisValue);
	}
}

void ATrainer::TurnRate(float AxisValue)
{
	this->AddControllerYawInput(AxisValue * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ATrainer::Turn(float AxisValue)
{
	this->AddControllerYawInput(AxisValue);
}

void ATrainer::LookUpRate(float AxisValue)
{
	this->AddControllerPitchInput(AxisValue * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ATrainer::LookUp(float AxisValue)
{
	this->AddControllerPitchInput(AxisValue);
}

void ATrainer::Jump()
{
	this->bPressedJump = true;
}

void ATrainer::StopJumping()
{
	this->bPressedJump = false;
}

void ATrainer::MoveTo(FVector Location)
{
	this->OldController = this->Controller;
	this->Controller = this->AIController;
	this->AIController->Possess(this);

	this->AIController->MoveToLocation(Location);
	ATrainerController* TrainerController = Cast<ATrainerController>(this->OldController);
	TrainerController->MoveFinished = false;
}

void ATrainer::RepossessOldController()
{
	this->Controller = this->OldController;
	this->OldController->Possess(this);
	ATrainerController* TrainerController = Cast<ATrainerController>(this->OldController);
	TrainerController->MoveFinished = true;
}

/**
* Depending on the current status of MonToggled,
* this function is responsible for either destroying
* or spawning the player's current sidekick.
*/
void ATrainer::ToggleMonster()
{
	// Destroy follower
	if (MonToggled)
	{
		Sidekick->Destroy();
		Sidekick = nullptr;
		MonToggled = false;
	}
	// Spawn follower, set the trainer's variable, and then update the BB of the follower.
	// PlayerPawn in the follower's blackboard is used to keep track of who to follow.
	else
	{
		Sidekick = GetWorld()->SpawnActor<AMonster>(FollowerClass, this->GetActorLocation(), this->GetActorRotation());
		Sidekick->GetBBComponent()->SetValueAsObject("PlayerPawn", this);
		MonToggled = true;
	}
}

void ATrainer::CheckRightClick()
{
	if (!CombatStarted)
	{
		AttemptStartCombat();
	}
	else
	{
		CombatRightClick();
	}
}

/**
* Checks conditions and attempts to start combat.
* If we can start combat, then this function will trigger
* the function StartCombat.
*/
void ATrainer::AttemptStartCombat()
{
	// We only want to try and start combat if the sidekick mon is toggled.
	if (MonToggled)
	{
		FHitResult HitResult = this->LineTrace();

		if (HitResult.Actor->GetClass()->GetName().Contains("BP_Kappa"))
		{
			UE_LOG(LogTemp, Warning, TEXT("HitMon %s"), *HitResult.Actor->GetClass()->GetName())
			StartCombat(HitResult);
		}
	}
}

void ATrainer::StartCombat(FHitResult HitResult)
{
	CombatStarted = true;

	AMonster * EnemyMon = Cast<AMonster>(HitResult.Actor.Get());
	// Set follower Blackboard values
	this->Sidekick->GetBBComponent()->SetValueAsObject(FName("MonToFight"), EnemyMon);
	this->Sidekick->GetBBComponent()->SetValueAsBool(FName("InCombat"), true);
	this->Sidekick->GetBBComponent()->SetValueAsVector(FName("CombatStartLocation"), this->GetActorLocation() + 100);
	this->Sidekick->GetBBComponent()->SetValueAsVector(FName("CombatMoveToLocation"), this->GetActorLocation() + 100);

	// Set enemy mon Blackboard values
	EnemyMon->GetBBComponent()->SetValueAsBool(FName("BattleStarted"), true);
	EnemyMon->GetBBComponent()->SetValueAsVector(FName("CombatStartLocation"), this->GetActorLocation() - 100);

	// Init Battle Circle Spline values
	FVector Location = this->GetActorLocation();
	FRotator Rotation = FRotator(0,0,0);
	FVector Scale = FVector(2.25f, 2.25f, 2.25f);

	// Create battle circle actor and then set 3D scale after... Wouldn't accept FTransform for some reason.
	AActor* BattleCircle = this->GetWorld()->SpawnActor<AActor>(BattleAreaSpline, Location, Rotation);
	BattleCircle->SetActorScale3D(Scale);

	if (BattleCircle)
	{
		
		USplineComponent* Spline = Cast<USplineComponent>(BattleCircle->GetDefaultSubobjectByName(FName("Spline")));
		if (Spline)
		{
			this->BattleSpline = Spline;
			UE_LOG(LogTemp, Warning, TEXT("Spline"))
			FVector ClosestLocation = Spline->FindLocationClosestToWorldLocation(this->GetActorLocation(), ESplineCoordinateSpace::World);
			this->MoveTo(ClosestLocation);
		}
	}
	//UE_LOG(LogTemp, Warning, TEXT("Location: %s"), *ClosestLocation.ToString())
	/*this->MoveTo(Spline->)*/
}

void ATrainer::CombatRightClick()
{
	FHitResult HitResult = this->LineTrace();
	this->Sidekick->GetBBComponent()->SetValueAsVector(FName("CombatMoveToLocation"), HitResult.ImpactPoint);
	/*if (HitResult.Actor.Get()->GetClass()->GetName().Contains("Landscape"))
	{

	}*/
}

/**
* Used for line tracing when starting combat or directing mon in combat.
*/
FHitResult ATrainer::LineTrace()
{
	// Initializing all line trace values
	APlayerCameraManager* CameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	
	const FVector& Start = CameraManager->GetCameraLocation();
	const FVector& End = (CameraManager->GetActorForwardVector() * 3000) + Start;
	
	FHitResult HitResult(ForceInit);
	
	ECollisionChannel CollisionChannel = ECC_Pawn;
	
	FCollisionQueryParams TraceParams(FName(TEXT("Combat Trace")), true, this);
	TraceParams.bTraceComplex = true;
	TraceParams.bReturnPhysicalMaterial = false;
	TraceParams.AddIgnoredActor(this);

	// Executing line trace and returning HitResult to caller function
	this->GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, CollisionChannel, TraceParams);

	return HitResult;
}

//void ATrainer::OnMoveCompleted(uint32 RequestID, EPathFollowingResult::Type Result)
//{
//	UE_LOG(LogTemp, Warning, TEXT("MoveCompleted"));
//	if (Result == EPathFollowingResult::Success)
//		UE_LOG(LogTemp, Warning, TEXT("Success"));
//}
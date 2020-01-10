// Fill out your copyright notice in the Description page of Project Settings.

#include "Monster.h"
#include "TrainerController.h"
#include "Trainer.h"
#include "GameplayTagContainer.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "MonAttributeSet.h"
#include "AbilitySystemComponent.h"

// Sets default values
AMonster::AMonster()
{
	// Our ability system component.
	AbilitySystem = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystem"));

	// Define attribute set for monsters.
	AttributeSet = CreateDefaultSubobject<UMonAttributeSet>(TEXT("AttributeSet"));

 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMonster::BeginPlay()
{
	Super::BeginPlay();
	if (AbilitySystem)
	{
		FGameplayAbilityActorInfo* actorInfo = new FGameplayAbilityActorInfo();
		actorInfo->InitFromActor(this, this, AbilitySystem);
		AbilitySystem->AbilityActorInfo = TSharedPtr<FGameplayAbilityActorInfo>(actorInfo);

		if (HasAuthority() && Ability1)
		{
			AbilitySystem->GiveAbility(FGameplayAbilitySpec(Ability1.GetDefaultObject(), 1, 0));
		}
		if (HasAuthority() && Ability2)
		{
			AbilitySystem->GiveAbility(FGameplayAbilitySpec(Ability2.GetDefaultObject(), 1, 0));
		}
		if (HasAuthority() && Ability3)
		{
			AbilitySystem->GiveAbility(FGameplayAbilitySpec(Ability3.GetDefaultObject(), 1, 0));
		}
		if (HasAuthority() && Ability4)
		{
			AbilitySystem->GiveAbility(FGameplayAbilitySpec(Ability4.GetDefaultObject(), 1, 0));
		}
		AbilitySystem->InitAbilityActorInfo(this, this);
	}
}

// Called every frame
void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMonster::SetBTComponent(UBehaviorTree* BTComponent)
{
	if (!this->BTComponent)
		this->BTComponent = BTComponent;
}

UBehaviorTree* AMonster::GetBTComponent()
{
	return this->BTComponent;
}

void AMonster::SetBBComponent(UBlackboardComponent* BBComponent)
{
	if (!this->BBComponent)
		this->BBComponent = BBComponent;
}

UBlackboardComponent* AMonster::GetBBComponent()
{
	if (!this->BBComponent)
	{
		this->BBComponent = Cast<AAIController>(this->Controller)->GetBlackboardComponent();
	}
	return this->BBComponent;
}

void AMonster::ExecuteMonMove(int MonMoveNum)
{
	FGameplayEventData Payload;
	FGameplayTag Tag;
	Payload.Instigator = this;
	Payload.Target = this;

	if (AbilitySystem)
	{
		switch (MonMoveNum)
		{
		case 1:
			Tag = FGameplayTag::RequestGameplayTag(this->getAbility1Tag());
			Payload.EventTag = Tag;
			UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this, Tag, Payload);
			break;

		case 2:
			Tag = FGameplayTag::RequestGameplayTag(this->getAbility2Tag());
			Payload.EventTag = Tag;
			UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this, Tag, Payload);
			break;

		case 3:
			Tag = FGameplayTag::RequestGameplayTag(this->getAbility3Tag());
			Payload.EventTag = Tag;
			UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this, Tag, Payload);
			break;

		case 4:
			Tag = FGameplayTag::RequestGameplayTag(this->getAbility4Tag());
			Payload.EventTag = Tag;
			UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this, Tag, Payload);
			break;
		}
	}
}

FName AMonster::getAbility1Tag() const
{
    return Ability1Tag;
}

void AMonster::setAbility1Tag(FName AbilityTag)
{
	if (!AbilityTag.IsEqual("Unbound"))
	{
		if (!getAbility2Tag().IsEqual(AbilityTag) && !getAbility3Tag().IsEqual(AbilityTag) && !getAbility4Tag().IsEqual(AbilityTag))
		{
			UE_LOG(LogTemp, Warning, TEXT("Please1 %s"), *AbilityTag.ToString());
			this->Ability1Tag = AbilityTag;
		}
	}
	else
	{
		this->Ability1Tag = AbilityTag;
	}
}

FName AMonster::getAbility2Tag() const
{
    return Ability2Tag;
}

void AMonster::setAbility2Tag(FName AbilityTag)
{
	if (!AbilityTag.IsEqual("Unbound"))
	{
		if (!getAbility1Tag().IsEqual(AbilityTag) && !getAbility3Tag().IsEqual(AbilityTag) && !getAbility4Tag().IsEqual(AbilityTag))
		{
			UE_LOG(LogTemp, Warning, TEXT("Please2 %s"), *AbilityTag.ToString());
			this->Ability2Tag = AbilityTag;
		}
	}
	else
	{
		this->Ability2Tag = AbilityTag;
	}
}

FName AMonster::getAbility3Tag() const
{
    return Ability3Tag;
}

void AMonster::setAbility3Tag(FName AbilityTag)
{
	if (!AbilityTag.IsEqual("Unbound"))
	{
		if (!getAbility1Tag().IsEqual(AbilityTag) && !getAbility2Tag().IsEqual(AbilityTag) && !getAbility4Tag().IsEqual(AbilityTag))
		{
			UE_LOG(LogTemp, Warning, TEXT("Please2 %s"), *AbilityTag.ToString());
			this->Ability3Tag = AbilityTag;
		}
	}
	else
	{
		this->Ability3Tag = AbilityTag;
	}
}

FName AMonster::getAbility4Tag() const
{
    return Ability4Tag;
}

void AMonster::setAbility4Tag(FName AbilityTag)
{
	if (!AbilityTag.IsEqual("Unbound"))
	{
		if (!getAbility1Tag().IsEqual(AbilityTag) && !getAbility2Tag().IsEqual(AbilityTag) && !getAbility3Tag().IsEqual(AbilityTag))
		{
			UE_LOG(LogTemp, Warning, TEXT("Please2 %s"), *AbilityTag.ToString());
			this->Ability4Tag = AbilityTag;
		}
	}
	else
	{
		this->Ability4Tag = AbilityTag;
	}
}

bool AMonster::getIsEating() const
{
    return isEating;
}

void AMonster::setIsEating(bool isEating)
{
    this->isEating = isEating;
}

float AMonster::getLevel() const
{
    return Level;
}

void AMonster::setLevel(float Level)
{
    this->Level = Level;
}

bool AMonster::getWild() const
{
    return Wild;
}

void AMonster::setWild(bool Wild)
{
    this->Wild = Wild;
}

float AMonster::getCurrentXP() const
{
    return CurrentXP;
}

void AMonster::setCurrentXP(float CurrentXP)
{
    this->CurrentXP = CurrentXP;
}

float AMonster::getXPForNextLevel() const
{
    return XPForNextLevel;
}

void AMonster::setXPForNextLevel(float XPForNextLevel)
{
    this->XPForNextLevel = XPForNextLevel;
}

FName AMonster::getSpeciesName() const
{
    return SpeciesName;
}

void AMonster::setSpeciesName(FName SpeciesName)
{
    this->SpeciesName = SpeciesName;
}

FText AMonster::getNickName() const
{
    return NickName;
}

void AMonster::setNickName(FText NickName)
{
    this->NickName = NickName;
}

bool AMonster::GetIsInCombat()
{
	return IsInCombat;
}

void AMonster::SetIsInCombat(bool IsInCombat)
{
	this->IsInCombat = IsInCombat;
}

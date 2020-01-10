// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BehaviorTree.h"
#include "AIController.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "Monster.generated.h"

UENUM(BlueprintType)
enum class AbilityInput : uint8
{
	UseMove1 UMETA(DisplayName = "Use Move 1"), //This maps the first ability(input ID should be 0 in int) to the action mapping(which you define in the project settings) by the name of "UseAbility1". "Use Spell 1" is the blueprint name of the element.
	UseMove2 UMETA(DisplayName = "Use Move 2"), //Maps ability 2(input ID 1) to action mapping UseAbility2. "Use Spell 2" is mostly used for when the enum is a blueprint variable.
	UseMove3 UMETA(DisplayName = "Use Move 3"),
	UseMove4 UMETA(DisplayName = "Use Move 4")

		//You may also do something like define an enum element name that is not actually mapped to an input, for example if you have a passive ability that isn't supposed to have an input. This isn't usually necessary though as you usually grant abilities via input ID,
		//which can be negative while enums cannot. In fact, a constant called "INDEX_NONE" exists for the exact purpose of rendering an input as unavailable, and it's simply defined as -1.
		//Because abilities are granted by input ID, which is an int, you may use enum elements to describe the ID anyway however, because enums are fancily dressed up ints.
};

UCLASS()
class REALTIMEPROTOTYPE_API AMonster : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

private:

	UBehaviorTree * BTComponent = nullptr;
	UBlackboardComponent* BBComponent = nullptr;

	bool isEating;

	float Level;
	bool Wild;
	float CurrentXP;
	float XPForNextLevel;
	FName SpeciesName;
	FText NickName;
	bool IsInCombat;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Abilities)
		TMap<int32, FName> SkillTree;

	// Sets default values for this pawn's properties
	AMonster();

	/** Our Ability System */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Abilities, meta = (AllowPrivateAccess = "true"))
		UAbilitySystemComponent* AbilitySystem;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Abilities)
		UAttributeSet* AttributeSet;

	UAbilitySystemComponent* GetAbilitySystemComponent() const override //We add this function, overriding it from IAbilitySystemInterface.
	{
		return AbilitySystem;
	};

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	AActor* Trainer;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** These are used to give the Mons access to their moves */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Abilities)
		TSubclassOf<class UGameplayAbility> Ability1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Abilities)
		TSubclassOf<class UGameplayAbility> Ability2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Abilities)
		TSubclassOf<class UGameplayAbility> Ability3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Abilities)
		TSubclassOf<class UGameplayAbility> Ability4;
	
	/** These are used to execute the appropriate moves on input*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Abilities)
		FName Ability1Tag = FName("move.electroball");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Abilities)
		FName Ability2Tag = FName("move.punch");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Abilities)
		FName Ability3Tag;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Abilities)
		FName Ability4Tag;

	void SetBTComponent(UBehaviorTree* BTComponent);
	UBehaviorTree* GetBTComponent();
	void SetBBComponent(UBlackboardComponent* BBComponent);
	UBlackboardComponent* GetBBComponent();

	UFUNCTION(BlueprintCallable)
		void ExecuteMonMove(int MonMoveNum);
	
	UFUNCTION(BlueprintCallable)
    FName getAbility1Tag() const;
	UFUNCTION(BlueprintCallable)
    void setAbility1Tag(FName AbilityTag);

	UFUNCTION(BlueprintCallable)
    FName getAbility2Tag() const;
	UFUNCTION(BlueprintCallable)
    void setAbility2Tag(FName AbilityTag);

	UFUNCTION(BlueprintCallable)
    FName getAbility3Tag() const;
	UFUNCTION(BlueprintCallable)
    void setAbility3Tag(FName AbilityTag);

	UFUNCTION(BlueprintCallable)
    FName getAbility4Tag() const;
	UFUNCTION(BlueprintCallable)
    void setAbility4Tag(FName AbilityTag);

	UFUNCTION(BlueprintCallable)
    bool getIsEating() const;
	UFUNCTION(BlueprintCallable)
    void setIsEating(bool isEating);

	UFUNCTION(BlueprintCallable)
    float getLevel() const;
	UFUNCTION(BlueprintCallable)
    void setLevel(float Level);

	UFUNCTION(BlueprintCallable)
    bool getWild() const;
	UFUNCTION(BlueprintCallable)
    void setWild(bool Wild);

	UFUNCTION(BlueprintCallable)
    float getCurrentXP() const;
	UFUNCTION(BlueprintCallable)
    void setCurrentXP(float CurrentXP);

	UFUNCTION(BlueprintCallable)
    float getXPForNextLevel() const;
	UFUNCTION(BlueprintCallable)
    void setXPForNextLevel(float XPForNextLevel);

	UFUNCTION(BlueprintCallable)
    FName getSpeciesName() const;
	UFUNCTION(BlueprintCallable)
    void setSpeciesName(FName SpeciesName);

	UFUNCTION(BlueprintCallable)
    FText getNickName() const;
	UFUNCTION(BlueprintCallable)
    void setNickName(FText NickName);

	UFUNCTION(BlueprintCallable)
		bool GetIsInCombat();
	UFUNCTION(BlueprintCallable)
		void SetIsInCombat(bool IsInCombat);
};

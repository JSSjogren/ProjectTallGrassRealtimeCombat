// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "UObject/CoreNet.h"
#include "UnrealNetwork.h"
#include "AbilitySystemComponent.h"
#include "MonAttributeSet.generated.h"

	// Uses macros from AttributeSet.h
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class REALTIMEPROTOTYPE_API UMonAttributeSet : public UAttributeSet
{

	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, Category = "Mon Attributes", ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UMonAttributeSet, Health)

	UPROPERTY(BlueprintReadOnly, Category = "Mon Attributes", ReplicatedUsing = OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UMonAttributeSet, MaxHealth)
	
		UPROPERTY(BlueprintReadOnly, Category = "Mon Attributes", ReplicatedUsing = OnRep_Stamina)
		FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS(UMonAttributeSet, Stamina)

		UPROPERTY(BlueprintReadOnly, Category = "Mon Attributes", ReplicatedUsing = OnRep_MaxStamina)
		FGameplayAttributeData MaxStamina;
	ATTRIBUTE_ACCESSORS(UMonAttributeSet, MaxStamina)

	FGameplayAttribute HealthAttribute();
	FGameplayAttribute MaxHealthAttribute();
	FGameplayAttribute StaminaAttribute();
	FGameplayAttribute MaxStaminaAttribute();

	UFUNCTION()
		virtual void OnRep_Health();
	UFUNCTION()
		virtual void OnRep_MaxHealth();
	UFUNCTION()
		virtual void OnRep_Stamina();
	UFUNCTION()
		virtual void OnRep_MaxStamina();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
};

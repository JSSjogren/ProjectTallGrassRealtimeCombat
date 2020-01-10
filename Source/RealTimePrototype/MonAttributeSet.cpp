// Fill out your copyright notice in the Description page of Project Settings.


#include "MonAttributeSet.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"
#include <GeneratedCodeHelpers.h>

FGameplayAttribute UMonAttributeSet::HealthAttribute()
{
	static UProperty* Property = FindFieldChecked<UProperty>(UMonAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UMonAttributeSet, Health));
	return FGameplayAttribute(Property);
}

FGameplayAttribute UMonAttributeSet::MaxHealthAttribute()
{
	static UProperty* Property = FindFieldChecked<UProperty>(UMonAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UMonAttributeSet, MaxHealth));
	return FGameplayAttribute(Property);
}

FGameplayAttribute UMonAttributeSet::StaminaAttribute()
{
	static UProperty* Property = FindFieldChecked<UProperty>(UMonAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UMonAttributeSet, Stamina));
	return FGameplayAttribute(Property);
}

FGameplayAttribute UMonAttributeSet::MaxStaminaAttribute()
{
	static UProperty* Property = FindFieldChecked<UProperty>(UMonAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UMonAttributeSet, MaxStamina));
	return FGameplayAttribute(Property);
}

void UMonAttributeSet::OnRep_Health()
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMonAttributeSet, Health);
}

void UMonAttributeSet::OnRep_MaxHealth()
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMonAttributeSet, MaxHealth);
}

void UMonAttributeSet::OnRep_Stamina()
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMonAttributeSet, Stamina);
}

void UMonAttributeSet::OnRep_MaxStamina()
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMonAttributeSet, MaxStamina);
}

void UMonAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UMonAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMonAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMonAttributeSet, Stamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMonAttributeSet, MaxStamina, COND_None, REPNOTIFY_Always);
}

void UMonAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));
	}
	else if (Data.EvaluatedData.Attribute == GetStaminaAttribute())
	{
		SetStamina(FMath::Clamp(GetStamina(), 0.0f, GetMaxStamina()));
	}
}

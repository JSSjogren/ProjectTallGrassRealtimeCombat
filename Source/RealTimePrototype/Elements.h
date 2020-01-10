// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedEnum.h"
#include "Elements.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum Elements
{
	FIRE     UMETA(DisplayName = "Fire"),
	WATER     UMETA(DisplayName = "Water"),
	NATURE     UMETA(DisplayName = "Nature"),
	ELECTRICITY     UMETA(DisplayName = "Electricity"),
	EARTH     UMETA(DisplayName = "Earth"),
	WIND     UMETA(DisplayName = "Wind"),
	DARK     UMETA(DisplayName = "Dark"),
	DRAGON     UMETA(DisplayName = "Dragon"),
	LIGHT     UMETA(DisplayName = "Light"),
	ARCANE     UMETA(DisplayName = "Arcane")
};

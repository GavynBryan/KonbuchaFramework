// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "KonGameplayAbility.generated.h"

class AKonBaseCharacter;

UCLASS(Abstract)
class KONBUCHA_API UKonGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UKonGameplayAbility(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UFUNCTION(BlueprintCallable)
	AKonBaseCharacter* GetKonCharacterFromActorInfo() const;
};

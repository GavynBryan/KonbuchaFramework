// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTaskOwnerInterface.h"
#include "UObject/Object.h"
#include "EventFlowchart.generated.h"

class AKonBaseCharacter;
static TMap<FName, TWeakObjectPtr<AKonBaseCharacter>> CachedCharacters;

class AKonBaseCharacter;
/**
 * 
 */
UCLASS(Blueprintable)
class KONBUCHA_API UEventFlowchart : public UObject, public IGameplayTaskOwnerInterface
{
	GENERATED_BODY()
public:
	virtual void OnGameplayTaskInitialized(UGameplayTask& Task) override;
protected:
	virtual UWorld* GetWorld() const override;
};

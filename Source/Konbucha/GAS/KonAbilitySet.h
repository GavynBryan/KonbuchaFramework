// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KonGameplayAbility.h"
#include "Engine/DataAsset.h"
#include "KonAbilitySet.generated.h"

USTRUCT(BlueprintType)
struct FKonAbilitySet_GameplayAbility
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UKonGameplayAbility> Ability = nullptr;

	UPROPERTY(EditDefaultsOnly)
	int32 AbilityLevel = 1;

	UPROPERTY(EditDefaultsOnly)
	int32 InputID = -1;
	
};

/**
 * Store handles to GAS structures to revoke
 */
USTRUCT(BlueprintType)
struct FKonAbilitySet_GrantedHandles
{
	GENERATED_BODY()

public:
	void AddAbilitySpecHandle(const FGameplayAbilitySpecHandle& Handle);
	
	void TakeFromAbilitySystem(UAbilitySystemComponent* ASC);
	
protected:
	
	UPROPERTY()
	TArray<FGameplayAbilitySpecHandle> AbilitySpecHandles;
};

/**
 * DataAsset to grant gameplay abilities from weapons and events
 */
UCLASS()
class KONBUCHA_API UKonAbilitySet : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	void GiveToAbilitySystem(UAbilitySystemComponent* ASC, FKonAbilitySet_GrantedHandles* OutGrantedHandles = nullptr);

protected:
	UPROPERTY(EditDefaultsOnly)
	TArray<FKonAbilitySet_GameplayAbility> GrantedAbilities;
};

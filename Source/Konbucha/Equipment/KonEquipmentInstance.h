// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "UObject/Object.h"
#include "Konbucha//GAS/KonAbilitySet.h"
#include "KonEquipmentInstance.generated.h"

/**
 * Class representing an instance of Equipment.
 * This class is responsible for managing the abilities associated with the equipment and handling equipment events.
 */
UCLASS(BlueprintType)
class KONBUCHA_API UKonEquipmentInstance : public UObject
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditDefaultsOnly)
	UKonAbilitySet* AbilitiesToGrant;
public:
	UPROPERTY(BlueprintReadOnly)
	bool IsEquipped;
private:
	FKonAbilitySet_GrantedHandles GrantedHandles;
	
public:
	UFUNCTION(BlueprintCallable)
	virtual void Activate(UAbilitySystemComponent* ASC);
	UFUNCTION(BlueprintCallable)
	virtual void Equip(UAbilitySystemComponent* ASC);
	UFUNCTION(BlueprintCallable)
	virtual void Unequip(UAbilitySystemComponent* ASC);

	UFUNCTION(BlueprintImplementableEvent)
	void OnActivate();
	UFUNCTION(BlueprintImplementableEvent)
	void OnEquip();
	UFUNCTION(BlueprintImplementableEvent)
	void OnUnequip();
};

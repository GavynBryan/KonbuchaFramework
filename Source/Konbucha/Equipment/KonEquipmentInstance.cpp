// Fill out your copyright notice in the Description page of Project Settings.


#include "KonEquipmentInstance.h"

#include "Abilities/Tasks/AbilityTask_WaitAbilityActivate.h"

void UKonEquipmentInstance::Activate(UAbilitySystemComponent* ASC)
{
	OnActivate();
}

void UKonEquipmentInstance::Equip(UAbilitySystemComponent* ASC)
{
	AbilitiesToGrant->GiveToAbilitySystem(ASC, &GrantedHandles);
	IsEquipped = true;

	OnEquip();
}


void UKonEquipmentInstance::Unequip(UAbilitySystemComponent* ASC)
{
	GrantedHandles.TakeFromAbilitySystem(ASC);
	IsEquipped = false;

	OnUnequip();
}

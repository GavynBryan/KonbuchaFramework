// Fill out your copyright notice in the Description page of Project Settings.


#include "KonAbilitySet.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemLog.h"

void FKonAbilitySet_GrantedHandles::AddAbilitySpecHandle(const FGameplayAbilitySpecHandle& Handle)
{
	if(Handle.IsValid()) {
		AbilitySpecHandles.Add(Handle);
	}
}

void FKonAbilitySet_GrantedHandles::TakeFromAbilitySystem(UAbilitySystemComponent* ASC)
{
	check(ASC);
	for (const FGameplayAbilitySpecHandle& AbilityHandle : AbilitySpecHandles) {
		if(AbilityHandle.IsValid()) {
			ASC->ClearAbility(AbilityHandle);
		}
	}
}

void UKonAbilitySet::GiveToAbilitySystem(UAbilitySystemComponent* ASC,
	FKonAbilitySet_GrantedHandles* OutGrantedHandles)
{
	check(ASC);
	for (int32 i = 0; i < GrantedAbilities.Num(); i ++) {
		const FKonAbilitySet_GameplayAbility AbilityToGrant = GrantedAbilities[i];
		
		if(!IsValid(AbilityToGrant.Ability)) {
			UE_LOG(LogAbilitySystem, Error, TEXT("GrantedGameplayAbilities[%d] on ability set [%s] is not valid."), i, *GetNameSafe(this));
			continue;
		}

		UKonGameplayAbility* AbilityCDO = AbilityToGrant.Ability->GetDefaultObject<UKonGameplayAbility>();
		FGameplayAbilitySpec AbilitySpec(AbilityCDO, AbilityToGrant.AbilityLevel, AbilityToGrant.InputID);
		
		const FGameplayAbilitySpecHandle AbilitySpecHandle = ASC->GiveAbility(AbilitySpec);
		if(OutGrantedHandles) {
			OutGrantedHandles->AddAbilitySpecHandle(AbilitySpecHandle);
		}
	}
}


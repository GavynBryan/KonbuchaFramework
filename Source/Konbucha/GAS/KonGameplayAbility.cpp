// Fill out your copyright notice in the Description page of Project Settings.


#include "KonGameplayAbility.h"
#include "Konbucha/Character/KonBaseCharacter.h"

UKonGameplayAbility::UKonGameplayAbility(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

AKonBaseCharacter* UKonGameplayAbility::GetKonCharacterFromActorInfo() const
{
	return (CurrentActorInfo ? Cast<AKonBaseCharacter>(CurrentActorInfo->AvatarActor.Get()) : nullptr);
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "KonHealthAttributeSet.h"

#include "GameplayEffectExtension.h"
#include "Konbucha/Character/KonBaseCharacter.h"

void UKonHealthAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	
	float HealthBeforeChange = GetHealth();

	const FGameplayEffectContextHandle& EffectContext = Data.EffectSpec.GetEffectContext();
	AActor* Instigator = EffectContext.GetOriginalInstigator();
	AActor* Causer = EffectContext.GetEffectCauser();

	if(Data.EvaluatedData.Attribute == GetDamageAttribute()) {
		const float LocalDamageDone = GetDamage();
		SetDamage(0.0f);

		const float NewHealth = GetHealth() - LocalDamageDone;
		SetHealth(FMath::Clamp(NewHealth, 0.0, GetMaxHealth()));
	}

	if(GetHealth() != HealthBeforeChange) {
		OnHealthChanged.Broadcast(Instigator, Causer, &Data.EffectSpec, Data.EvaluatedData.Magnitude, HealthBeforeChange, GetHealth());
	}

	if(GetHealth() <= 0.0f && !OutOfHealth) {
		OnOutOfHealth.Broadcast(Instigator, Causer, &Data.EffectSpec, Data.EvaluatedData.Magnitude, HealthBeforeChange, GetHealth());
		OutOfHealth = true;
	}
}

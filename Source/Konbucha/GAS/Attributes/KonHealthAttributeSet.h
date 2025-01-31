// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "KonAttributeSet.h"
#include "KonHealthAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class KONBUCHA_API UKonHealthAttributeSet : public UKonAttributeSet
{
	GENERATED_BODY()
public:
	ATTRIBUTE_ACCESSORS(UKonHealthAttributeSet, Health);
	ATTRIBUTE_ACCESSORS(UKonHealthAttributeSet, MaxHealth);
	ATTRIBUTE_ACCESSORS(UKonHealthAttributeSet, Damage);

	mutable FZeldaAttributeEvent OnHealthChanged;
	mutable FZeldaAttributeEvent OnOutOfHealth;
	
private:
	UPROPERTY()
	FGameplayAttributeData Health;
	UPROPERTY()
	FGameplayAttributeData MaxHealth;
	UPROPERTY()
	FGameplayAttributeData Damage;

	bool OutOfHealth;
	
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
};

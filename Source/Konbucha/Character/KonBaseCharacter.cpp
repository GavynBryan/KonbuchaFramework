// Fill out your copyright notice in the Description page of Project Settings.


#include "KonBaseCharacter.h"

#include "AbilitySystemComponent.h"
#include "NavigationSystemTypes.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Konbucha//KonGameplayTags.h"
#include "Konbucha/GAS/Attributes/KonHealthAttributeSet.h"


// Sets default values
AKonBaseCharacter::AKonBaseCharacter()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystem");
	CharacterAttributeSet = CreateDefaultSubobject<UKonHealthAttributeSet>("CharacterAttributes");
}

void AKonBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	if(AbilitySystemComponent) {
		InitDefaultAttributes();

		//Broadcast the default health value as to update the GUI
		OnHealthChanged.Broadcast(GetHealth(), GetHealth(), nullptr);
	}
}

void AKonBaseCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	if(AbilitySystemComponent) {
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}
}

void AKonBaseCharacter::OnMovementModeChanged(EMovementMode PrevMovementMode, uint8 PreviousCustomMode)
{
	Super::OnMovementModeChanged(PrevMovementMode, PreviousCustomMode);

	const FGameplayTag* PrevMoveTag = KonGameplayTags::MovementModeTagMap.Find(PrevMovementMode);
	const FGameplayTag* NewMoveTag = KonGameplayTags::MovementModeTagMap.Find(GetCharacterMovement()->MovementMode);

	if(PrevMoveTag != nullptr) {
		AbilitySystemComponent->RemoveLooseGameplayTag(*PrevMoveTag);
	}

	if(NewMoveTag != nullptr) {
		AbilitySystemComponent->AddLooseGameplayTag(*NewMoveTag);
	}
}

void AKonBaseCharacter::HandleHealthChanged(AActor* DamageInstigator, AActor* DamageCauser,
	const FGameplayEffectSpec* DamageEffectSpec, float DamageMagnitude, float OldValue, float NewValue)
{
	OnHealthChanged.Broadcast(OldValue, NewValue, DamageInstigator);
}

void AKonBaseCharacter::HandleOutOfHealth(AActor* DamageInstigator, AActor* DamageCauser,
	const FGameplayEffectSpec* DamageEffectSpec, float DamageMagnitude, float OldValue, float NewValue)
{
	if(UCharacterMovementComponent* MovementComponent = Cast<UCharacterMovementComponent>(GetMovementComponent())) {
		MovementComponent->StopMovementImmediately();
		MovementComponent->DisableMovement();
	}
	OnDeathStarted.Broadcast(this);
}

void AKonBaseCharacter::InitDefaultAttributes()
{
	if(!AbilitySystemComponent || !DefaultAttributeEffect) return;

	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	const FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributeEffect, 1.0f, EffectContext);
	if(SpecHandle.IsValid()) {
		AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
	}
	
	CharacterAttributeSet->OnHealthChanged.AddUObject(this, &ThisClass::HandleHealthChanged);
	CharacterAttributeSet->OnOutOfHealth.AddUObject(this, &ThisClass::HandleOutOfHealth);
	
}

UAbilitySystemComponent* AKonBaseCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

float AKonBaseCharacter::GetHealth() const
{
	if(!CharacterAttributeSet) return 0.0f;
	return CharacterAttributeSet->GetHealth();
}

float AKonBaseCharacter::GetMaxHealth() const
{
	if(!CharacterAttributeSet) return 0.0f;
	return CharacterAttributeSet->GetMaxHealth();
}

float AKonBaseCharacter::GetHealthPercentage() const
{
	if(!CharacterAttributeSet) return 0.0f;
	return CharacterAttributeSet->GetHealth() / CharacterAttributeSet->GetMaxHealth();
}

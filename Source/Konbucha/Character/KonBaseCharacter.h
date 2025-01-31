// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffect.h"
#include "GameFramework/Character.h"
#include "Konbucha/GAS//Attributes/KonHealthAttributeSet.h"
#include "KonBaseCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FKonHealth_DeathEvent, AActor*, OwningActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FKonHealth_AttributeChanged, float, OldValue, float, NewValue, AActor*, Instigator);

UCLASS()
class KONBUCHA_API AKonBaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	// Sets default values for this character's properties
	AKonBaseCharacter();
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FName NameID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FString DisplayName;

protected:

	/** Ability System */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Abilities, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<const UKonHealthAttributeSet> CharacterAttributeSet;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> DefaultAttributeEffect;

protected:
	virtual void PostInitializeComponents() override;
	void InitDefaultAttributes();
	
	virtual void OnMovementModeChanged(EMovementMode PrevMovementMode, uint8 PreviousCustomMode) override;

	void HandleHealthChanged(AActor* DamageInstigator, AActor* DamageCauser, const FGameplayEffectSpec* DamageEffectSpec, float DamageMagnitude, float OldValue, float NewValue);
	virtual void HandleOutOfHealth(AActor* DamageInstigator, AActor* DamageCauser, const FGameplayEffectSpec* DamageEffectSpec, float DamageMagnitude, float OldValue, float NewValue);
	

public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UFUNCTION(BlueprintCallable)
	float GetHealth() const;
	UFUNCTION(BlueprintCallable)
	float GetMaxHealth() const;
	UFUNCTION(BlueprintCallable)
	float GetHealthPercentage() const;

	UPROPERTY(BlueprintAssignable)
	FKonHealth_AttributeChanged OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FKonHealth_DeathEvent OnDeathStarted;
};

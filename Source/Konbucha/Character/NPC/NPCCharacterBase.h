// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Konbucha/Character/KonBaseCharacter.h"
#include "NPCCharacterBase.generated.h"

class UDialogueData;

UCLASS()
class KONBUCHA_API ANPCCharacterBase : public AKonBaseCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANPCCharacterBase();
	
	UFUNCTION(BlueprintNativeEvent)
	void HandleDialogue(UDialogueData* Data);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};

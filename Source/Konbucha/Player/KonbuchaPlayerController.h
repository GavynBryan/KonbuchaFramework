// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "KonbuchaPlayerController.generated.h"

class UDialogueComponent;
/**
 * 
 */
UCLASS()
class KONBUCHA_API AKonbuchaPlayerController : public APlayerController
{
	GENERATED_BODY()

	AKonbuchaPlayerController();

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UDialogueComponent> DialogueComponent;
};

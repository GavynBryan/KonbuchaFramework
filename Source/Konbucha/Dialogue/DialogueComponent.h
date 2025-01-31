// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DialogueComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDialogueCompleted);

class UDialogueData;

UENUM(BlueprintType)
enum EDialogueState
{
	NONE,
	TYPING,
	COMPLETED
};

UCLASS(Blueprintable, meta=(BlueprintSpawnableComponent))
class KONBUCHA_API UDialogueComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFUNCTION()
	bool TryDisplayDialogue(UDialogueData* DialogueData, const FString& SpeakerName);
	
	UFUNCTION(BlueprintNativeEvent)
	void DisplayDialogue(UDialogueData* DialogueData, const FString& SpeakerName);

	UFUNCTION(BlueprintCallable)
	void ProceedDialogue();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EDialogueState> CurrentDialogueState = NONE;

	UPROPERTY(BlueprintAssignable)
	FOnDialogueCompleted OnDialogueCompleted;
private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UDialogueData> CurrentDialogue;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EventFlowTask.h"
#include "GameplayTask.h"
#include "Konbucha/Dialogue/DialogueData.h"
#include "EventFlowTask_DialogueNode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDialogueNodeOutput);

class UDialogueData;
class UEventFlowchart;

UCLASS()
class KONBUCHA_API UEventFlowTask_DialogueNode : public UEventFlowTask
{
	GENERATED_BODY()

	UPROPERTY(BlueprintAssignable, meta=(DisplayName="Started"))
	FDialogueNodeOutput OnStarted;
	
	UPROPERTY(BlueprintAssignable, meta=(DisplayName="Completed"))
	FDialogueNodeOutput OnComplete;

	UPROPERTY(BlueprintAssignable, meta=(DisplayName="Fail"))
	FDialogueNodeOutput OnFailure;

	virtual void Activate() override;
	
	UFUNCTION(BlueprintCallable, Category="EventFlow|Tasks", meta = (HidePin = "OwningFlowchart", DefaultToSelf = "OwningFlowchart", BlueprintInternalUseOnly = "TRUE"))
	static UEventFlowTask_DialogueNode* DialogueNode(UEventFlowchart* OwningFlowchart, UDialogueData* InDialogueData);

	UFUNCTION()
	void OnDialogueCompleted();

private:
	UDialogueData* DialogueData;
};

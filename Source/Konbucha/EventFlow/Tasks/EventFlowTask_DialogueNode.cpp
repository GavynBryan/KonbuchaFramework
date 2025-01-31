// Fill out your copyright notice in the Description page of Project Settings.


#include "EventFlowTask_DialogueNode.h"

#include "Konbucha/Character/KonBaseCharacter.h"
#include "Konbucha/Character/NPC/NPCCharacterBase.h"
#include "Konbucha/Dialogue/DialogueComponent.h"
#include "Konbucha/Player/KonbuchaPlayerController.h"

void UEventFlowTask_DialogueNode::Activate()
{
	AKonBaseCharacter* Speaker = FindCharacter(DialogueData->SpeakerID);
	FString DisplayName = TEXT("");

	if(Speaker) {
		DisplayName = Speaker->DisplayName;
	}

	if(AKonbuchaPlayerController* PC = Cast<AKonbuchaPlayerController>(GetWorld()->GetFirstPlayerController())) {
		if(!PC->DialogueComponent->TryDisplayDialogue(DialogueData, DisplayName)) {
			OnFailure.Broadcast();
			EndTask();
			return;
		}
		//Delegate completion of this node to player input via DialogueComponent
		PC->DialogueComponent->OnDialogueCompleted.AddDynamic(this, &UEventFlowTask_DialogueNode::OnDialogueCompleted);

		OnStarted.Broadcast();

		if(ANPCCharacterBase* NPC = Cast<ANPCCharacterBase>(Speaker)) {
			NPC->HandleDialogue(DialogueData);
		}
		return;
	}
	EndTask();
}

UEventFlowTask_DialogueNode* UEventFlowTask_DialogueNode::DialogueNode(UEventFlowchart* OwningFlowchart, UDialogueData* InDialogueData)
{
	UEventFlowTask_DialogueNode* DialogueTask = CreateEventFlowTask<UEventFlowTask_DialogueNode>(OwningFlowchart);
	DialogueTask->DialogueData = InDialogueData;

	return DialogueTask;
}

void UEventFlowTask_DialogueNode::OnDialogueCompleted()
{
	OnComplete.Broadcast();

	if (AKonbuchaPlayerController* PC = Cast<AKonbuchaPlayerController>(GetWorld()->GetFirstPlayerController())) {
		PC->DialogueComponent->OnDialogueCompleted.RemoveDynamic(this, &UEventFlowTask_DialogueNode::OnDialogueCompleted);
	}
	
	EndTask();
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueComponent.h"
#include "DialogueData.h"


bool UDialogueComponent::TryDisplayDialogue(UDialogueData* DialogueData, const FString& SpeakerName)
{
	if(!IsValid(DialogueData)) {
		UE_LOG(LogTemp, Warning, TEXT("DisplayDialogue_Implementation: Invalid DialogueData. Aborting."));
		return false;
	}

	if(CurrentDialogue != nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("DisplayDialogue_Implementation: Tried initiating dialogue before conversation ended. Aborting."));
		return false;
	}
	
	CurrentDialogue = DialogueData;
	CurrentDialogueState = TYPING;
	DisplayDialogue(DialogueData, SpeakerName);
	
	return true;
}

void UDialogueComponent::DisplayDialogue_Implementation(UDialogueData* DialogueData, const FString& SpeakerName)
{

}

void UDialogueComponent::ProceedDialogue()
{
	CurrentDialogue = nullptr;
	CurrentDialogueState = NONE;
	
	OnDialogueCompleted.Broadcast();
}

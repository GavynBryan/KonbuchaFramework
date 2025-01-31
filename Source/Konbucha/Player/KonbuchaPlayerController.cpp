// Fill out your copyright notice in the Description page of Project Settings.


#include "KonbuchaPlayerController.h"
#include "Konbucha/Dialogue/DialogueComponent.h"

AKonbuchaPlayerController::AKonbuchaPlayerController()
{
	DialogueComponent = CreateDefaultSubobject<UDialogueComponent>(TEXT("DialogueComponent"));
}
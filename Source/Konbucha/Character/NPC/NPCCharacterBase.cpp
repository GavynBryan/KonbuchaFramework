// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCCharacterBase.h"


// Sets default values
ANPCCharacterBase::ANPCCharacterBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ANPCCharacterBase::HandleDialogue_Implementation(UDialogueData* Data)
{
}

// Called when the game starts or when spawned
void ANPCCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

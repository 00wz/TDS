// Fill out your copyright notice in the Description page of Project Settings.


#include "StateEffects/MyTPS_StateEffect_Frozen.h"

#include "Character/TPSCharacter.h"

bool UMyTPS_StateEffect_Frozen::InitObject(AActor* Actor)
{
	Character = Cast<ATPSCharacter>(Actor);
	if(Character)
	{
		Super::InitObject(Actor);
		Character->bFrozen = true;
	}
	return true;
}

void UMyTPS_StateEffect_Frozen::DestroyObject()
{
	if(Character)
	{
		Character->bFrozen = false;
	}
	Super::DestroyObject();
}

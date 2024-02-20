// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/TPSCharacter.h"
#include "StateEffects/TPS_StateEffect.h"
#include "MyTPS_StateEffect_Frozen.generated.h"

/**
 * 
 */
UCLASS()
class TPS_API UMyTPS_StateEffect_Frozen : public UTPS_StateEffect_ExecuteTimer
{
	GENERATED_BODY()

public:
	bool InitObject(AActor* Actor) override;
	void DestroyObject() override;

private:
	ATPSCharacter* Character;
};

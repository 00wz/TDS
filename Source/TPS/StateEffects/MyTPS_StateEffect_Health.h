// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/TPSHealthComponent.h"
#include "StateEffects/TPS_StateEffect.h"
#include "MyTPS_StateEffect_Health.generated.h"

/**
 * 
 */
UCLASS()
class TPS_API UMyTPS_StateEffect_Health : public UTPS_StateEffect_ExecuteTimer
{
	GENERATED_BODY()
	
public:
	bool InitObject(AActor* Actor) override;
	void DestroyObject() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float HealthAdd = 50.f;

private:
	UTPSHealthComponent* HealthComponent;
	float addedHealth;
};

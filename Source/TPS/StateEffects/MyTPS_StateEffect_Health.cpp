// Fill out your copyright notice in the Description page of Project Settings.


#include "StateEffects/MyTPS_StateEffect_Health.h"
#include "Kismet/KismetMathLibrary.h"

bool UMyTPS_StateEffect_Health::InitObject(AActor* Actor)
{
	auto healthComponents = Actor->GetComponentsByClass(UTPSHealthComponent::StaticClass());
	if(healthComponents.IsValidIndex(0))
	{
		HealthComponent = Cast<UTPSHealthComponent>(healthComponents[0]);
		addedHealth = UKismetMathLibrary::Min(
			100.f-HealthComponent->GetCurrentHealth(),
			HealthAdd);
		HealthComponent->ChangeHealthValue(addedHealth);
	}
	return Super::InitObject(Actor);
}

void UMyTPS_StateEffect_Health::DestroyObject()
{
	if(HealthComponent)
	{
		HealthComponent->ChangeHealthValue(-addedHealth);
	}
	Super::DestroyObject();
}

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/TPS_IGameActor.h"
#include "StateEffects/TPS_StateEffect.h"
#include "TPS_EnvironmentStructure.generated.h"

UCLASS()
class TPS_API ATPS_EnvironmentStructure : public AActor, public ITPS_IGameActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATPS_EnvironmentStructure();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	bool ReplicateSubobjects(class UActorChannel* Channel, class FOutBunch* Bunch, FReplicationFlags* RepFlags) override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	EPhysicalSurface GetSurfuceType() override;	
	
	TArray<UTPS_StateEffect*> GetAllCurrentEffects() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void RemoveEffect(UTPS_StateEffect* RemoveEffect);
	void RemoveEffect_Implementation(UTPS_StateEffect* RemoveEffect)override;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void AddEffect(UTPS_StateEffect* newEffect);
	void AddEffect_Implementation(UTPS_StateEffect* newEffect)override;

	//Effect
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Setting")
	TArray<UTPS_StateEffect*> Effects;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug")
	TArray<UParticleSystemComponent*> ParticleSystemEffects;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setting")
	FVector OffsetEffect = FVector(0);

	UFUNCTION()
	void SwitchEffect(UTPS_StateEffect* Effect, bool bIsAdd);

	UPROPERTY(ReplicatedUsing = EffectAdd_OnRep);
	UTPS_StateEffect* EffectAdd = nullptr;
	UPROPERTY(ReplicatedUsing = EffectRemove_OnRep);
	UTPS_StateEffect* EffectRemove = nullptr;

	UFUNCTION()
		void EffectAdd_OnRep();
	UFUNCTION()
		void EffectRemove_OnRep();


};

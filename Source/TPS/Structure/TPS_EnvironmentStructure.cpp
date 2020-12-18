// Fill out your copyright notice in the Description page of Project Settings.


#include "TPS_EnvironmentStructure.h"
#include "Materials/MaterialInterface.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "Engine/ActorChannel.h"

// Sets default values
ATPS_EnvironmentStructure::ATPS_EnvironmentStructure()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetReplicates(true);
}

// Called when the game starts or when spawned
void ATPS_EnvironmentStructure::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATPS_EnvironmentStructure::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

EPhysicalSurface ATPS_EnvironmentStructure::GetSurfuceType()
{
	EPhysicalSurface Result = EPhysicalSurface::SurfaceType_Default;
	UStaticMeshComponent* myMesh = Cast<UStaticMeshComponent>(GetComponentByClass(UStaticMeshComponent::StaticClass()));
	if (myMesh)
	{
		UMaterialInterface* myMaterial = myMesh->GetMaterial(0);
		if (myMaterial)
		{
			Result = myMaterial->GetPhysicalMaterial()->SurfaceType;
		}
	}
	return Result;
}
TArray<UTPS_StateEffect*> ATPS_EnvironmentStructure::GetAllCurrentEffects()
{
	return Effects;
}

void ATPS_EnvironmentStructure::RemoveEffect_Implementation(UTPS_StateEffect* RemoveEffect)
{
	Effects.Remove(RemoveEffect);

	EffectRemove = RemoveEffect;
	SwitchEffect(EffectRemove, false);
}

void ATPS_EnvironmentStructure::AddEffect_Implementation(UTPS_StateEffect* newEffect)
{
	Effects.Add(newEffect);

	EffectAdd = newEffect;
	SwitchEffect(EffectAdd, true);
}

void ATPS_EnvironmentStructure::SwitchEffect(UTPS_StateEffect* Effect, bool bIsAdd)
{
	if (bIsAdd)
	{
		if (Effect && Effect->ParticleEffect)
		{
			FName NameBoneToAttached = Effect->BoneName;
			FVector Loc = OffsetEffect;

			USceneComponent* SceneComponent = GetRootComponent();
			if (SceneComponent)
			{
				UParticleSystemComponent* newPartileSystem = UGameplayStatics::SpawnEmitterAttached(Effect->ParticleEffect, SceneComponent, NAME_None, Loc, FRotator::ZeroRotator, EAttachLocation::SnapToTarget, false);
				ParticleSystemEffects.Add(newPartileSystem);
			}
		}
	}
	else
	{
		int32 i = 0;
		bool bIsFind = false;
		while (i < ParticleSystemEffects.Num() && !bIsFind)
		{
			if (ParticleSystemEffects[i]->Template && Effect->ParticleEffect && Effect->ParticleEffect == ParticleSystemEffects[i]->Template)
			{
				bIsFind = true;
				ParticleSystemEffects[i]->DeactivateSystem();
				ParticleSystemEffects[i]->DestroyComponent();
				ParticleSystemEffects.RemoveAt(i);
			}
			i++;
		}
	}	
}

void ATPS_EnvironmentStructure::EffectAdd_OnRep()
{
	if (EffectAdd)
	{
		SwitchEffect(EffectAdd, true);
	}
}

void ATPS_EnvironmentStructure::EffectRemove_OnRep()
{
	if (EffectRemove)
	{
		SwitchEffect(EffectRemove, false);
	}
}

bool ATPS_EnvironmentStructure::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool Wrote = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

	for (int32 i = 0; i < Effects.Num(); i++)
	{
		if (Effects[i]) { Wrote |= Channel->ReplicateSubobject(Effects[i], *Bunch, *RepFlags); }
	}

	return Wrote;
}

void ATPS_EnvironmentStructure::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATPS_EnvironmentStructure, Effects);
	DOREPLIFETIME(ATPS_EnvironmentStructure, EffectAdd);
	DOREPLIFETIME(ATPS_EnvironmentStructure, EffectRemove);
}
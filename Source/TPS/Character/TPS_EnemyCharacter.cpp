// Fill out your copyright notice in the Description page of Project Settings.


#include "TPS_EnemyCharacter.h"
#include "Net/UnrealNetwork.h"
#include "Engine/ActorChannel.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATPS_EnemyCharacter::ATPS_EnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATPS_EnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATPS_EnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATPS_EnemyCharacter::RemoveEffect_Implementation(UTPS_StateEffect* RemoveEffect)
{
	Effects.Remove(RemoveEffect);

	EffectRemove = RemoveEffect;
	SwitchEffect(EffectRemove, false);
}

void ATPS_EnemyCharacter::AddEffect_Implementation(UTPS_StateEffect* newEffect)
{
	Effects.Add(newEffect);

	EffectAdd = newEffect;
	SwitchEffect(EffectAdd, true);
}

// Called to bind functionality to input
void ATPS_EnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATPS_EnemyCharacter::SwitchEffect(UTPS_StateEffect* Effect, bool bIsAdd)
{
	if (bIsAdd)
	{
		if (Effect && Effect->ParticleEffect)
		{
			FName NameBoneToAttached = Effect->BoneName;
			FVector Loc = FVector(0);

			USkeletalMeshComponent* myMesh = GetMesh();
			if (myMesh)
			{
				UParticleSystemComponent* newPartileSystem = UGameplayStatics::SpawnEmitterAttached(Effect->ParticleEffect, myMesh, NameBoneToAttached, Loc, FRotator::ZeroRotator, EAttachLocation::SnapToTarget, false);
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

void ATPS_EnemyCharacter::EffectAdd_OnRep()
{
	if (EffectAdd)
	{
		SwitchEffect(EffectAdd, true);
	}
}

void ATPS_EnemyCharacter::EffectRemove_OnRep()
{
	if (EffectRemove)
	{
		SwitchEffect(EffectRemove, false);
	}
}

bool ATPS_EnemyCharacter::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool Wrote = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

	for (int32 i = 0; i < Effects.Num(); i++)
	{
		if (Effects[i]) { Wrote |= Channel->ReplicateSubobject(Effects[i], *Bunch, *RepFlags); }
	}

	return Wrote;
}

void ATPS_EnemyCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATPS_EnemyCharacter, Effects);
	DOREPLIFETIME(ATPS_EnemyCharacter, EffectAdd);
	DOREPLIFETIME(ATPS_EnemyCharacter, EffectRemove);
}
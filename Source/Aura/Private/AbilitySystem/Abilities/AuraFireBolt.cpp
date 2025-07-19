// Copyright Alexandru Iancu


#include "AbilitySystem/Abilities/AuraFireBolt.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "Actor/AuraProjectile.h"

FString UAuraFireBolt::GetDescription(int32 Level)
{
	const float ScaledDamage = Damage.GetValueAtLevel(Level);
	const float ManaCost = GetManaCost(Level);
	const float Cooldown = GetCooldown(Level);
	UE_LOG(LogTemp, Warning, TEXT("Final Damage Value: %f"), ScaledDamage);

	if (Level == 1)
	{
		return FString::Printf(TEXT("<Title>FIRE BOLT</>"
			"\n\n<Small>Level: </><Level>%d</>"
			"\n<Small>Mana Cost:</> <ManaCost>%.1f</>"
			"\n<Small>Cooldown:</> <Cooldown>%.1f</>"
			"\n\n<Default>Launches a bolt of fire, exploding on impact and dealing</>"
			" <Damage>%d</> <Default>fire damage with a chance to burn</>"),
			Level,
			FMath::Abs(ManaCost),
			Cooldown,
			FMath::RoundToInt(ScaledDamage));
	}
	else
	{
		return FString::Printf(TEXT("<Title>NEXT LEVEL</>\n\n"
			"\n\n<Small>Level: </><Level>%d</>"
			"\n<Small>Mana Cost:</> <ManaCost>%.1f</>"
			"\n<Small>Cooldown:</> <Cooldown>%.1f</>"
			"\n\n<Default>Launches %d bolts of fire, exploding on impact and dealing</> <Damage>%d</> "
			"<Default>fire damage with a chance to burn</>"),
			Level,
			FMath::Abs(ManaCost),
			Cooldown,
			FMath::Min(Level, NumProjectiles),
			FMath::RoundToInt(ScaledDamage));
	}
}

FString UAuraFireBolt::GetNextLevelDescription(int32 Level)
{
	const float ScaledDamage = Damage.GetValueAtLevel(Level);
	const float ManaCost = GetManaCost(Level);
	const float Cooldown = GetCooldown(Level);
	return FString::Printf(TEXT("<Title>NEXT LEVEL</>"
		"\n\n<Small>Level: </><Level>%d</>"
		"\n<Small>Mana Cost:</> <ManaCost>%.1f</>"
		"\n<Small>Cooldown:</> <Cooldown>%.1f</>"
		"\n\n<Default>Launches %d bolts of fire, exploding on impact and dealing</> <Damage>%d</> "
		"<Default>fire damage with a chance to burn</>"),
		Level,
		FMath::Abs(ManaCost),
		Cooldown,
		FMath::Min(Level, NumProjectiles),
		FMath::RoundToInt(ScaledDamage));
}

void UAuraFireBolt::SpawnProjectiles(const FVector& ProjectileTargetLocation, const FGameplayTag& SocketTag,
	bool bOverridePitch, float PitchOverride, AActor* HomingTarget)
{
	const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();
	if (!bIsServer) return;

	const FVector SocketLocation = ICombatInterface::Execute_GetCombatSocketLocation(
		GetAvatarActorFromActorInfo(),
		SocketTag);
	FRotator Rotation = (ProjectileTargetLocation - SocketLocation).Rotation();
	if (bOverridePitch) Rotation.Pitch = PitchOverride;
	
	const FVector Forward = Rotation.Vector();
	TArray<FRotator> Rotations = UAuraAbilitySystemLibrary::EvenlySpacedRotators(Forward, FVector::UpVector, ProjectileSpread, NumProjectiles);

	for (const FRotator& Rotator : Rotations)
	{
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SocketLocation);
		SpawnTransform.SetRotation(Rotator.Quaternion());

		AAuraProjectile* Projectile = GetWorld()->SpawnActorDeferred<AAuraProjectile>(
			ProjectileClass,
			SpawnTransform,
			GetOwningActorFromActorInfo(),
			Cast<APawn>(GetOwningActorFromActorInfo()),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn
		);

		Projectile->DamageEffectParams = MakeDamageEffectParamsFromClassDefaults();
		Projectile->FinishSpawning(SpawnTransform);
	}
}

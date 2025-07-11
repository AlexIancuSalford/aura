// Copyright Alexandru Iancu


#include "AbilitySystem/Abilities/AuraFireBolt.h"

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

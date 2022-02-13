// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerGameMode.h"
#include "SpawnerManager.h"
#include "Enemy.h"
#include "WaveData.h"

void ATowerGameMode::DamageHealth(const int amount)
{
	if (!isGameOngoing) return;

	health -= amount;
	OnCoreDamaged(amount);

	if (health <= 0) {
		isGameOngoing = false;

		if (spawnerManager != nullptr) {
			//Stop all spawning
			spawnerManager->StopSpawning();
			OnCoreDestroyed.Broadcast(this);
		}
		else {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Error! Unable to stop spawn!"));
		}

	}
}

void ATowerGameMode::OnEnemyReachedCore(AEnemy* enemy)
{
	DamageHealth(enemy->enemyStat.coreDamage);
	coreDamagedCurrentWave = true;
}

void ATowerGameMode::OnCoreDamaged_Implementation(const int amount)
{
}

void ATowerGameMode::OnEnemyKill(AEnemy* enemy, bool playerKilled)
{
	if (!playerKilled) return;

	gold += enemy->enemyStat.goldReward;
}

bool ATowerGameMode::AddGold(const int amount)
{
	if (amount < 0) return false;
	gold += amount;
	return true;
}

bool ATowerGameMode::CheckGold(const int amount)
{
	return amount <= gold;
}

bool ATowerGameMode::UseGold(const int amount)
{
	if (gold < amount) return false;

	gold -= amount;
	return true;
}

void ATowerGameMode::EvaluateWave(UWaveData* waveData)
{
	//if (coreDamageCurrentWave) {
		// no gold reward
	//}
	//else {
		gold += waveData->waveClearReward;
	//}

	// reset
		coreDamagedCurrentWave = false;
}

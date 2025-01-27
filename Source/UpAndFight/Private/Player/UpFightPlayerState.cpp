// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/UpFightPlayerState.h"

AUpFightPlayerState::AUpFightPlayerState()
{
	// Частота обновления серверов клиента
	SetNetUpdateFrequency(100.f);
}

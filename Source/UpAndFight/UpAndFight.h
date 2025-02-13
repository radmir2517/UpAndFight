// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(LogUpAndFight, Log, All);
// дадим имя новому типу коллизии
#define ECC_Projectile ECollisionChannel::ECC_EngineTraceChannel1
#define CUSTOM_DEPTH_RED 250

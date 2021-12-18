#pragma once

#if WITH_AUTOMATION_TESTS

#include "CoreMinimal.h"
#include "Engine/World.h"
#include "Tests/AutomationCommon.h"
#include "Engine/World.h"
#include "Engine/Blueprint.h"

namespace STU
{
namespace Tests
{
constexpr char* PlayerBPName = "Blueprint'/Game/Player/BP_STUPlayerCharacter.BP_STUPlayerCharacter'";
constexpr char* TestLevelName = "/Game/Levels/TestLevel";

template <typename T>
T* CreateBlueprint(UWorld* World, const FString& Name, const FTransform& Transform = FTransform::Identity)
{
    const UBlueprint* Blueprint = LoadObject<UBlueprint>(nullptr, *Name);
    return (World && Blueprint) ? World->SpawnActor<T>(Blueprint->GeneratedClass, Transform) : nullptr;
}

UWorld* GetTestGameWorld();

class LevelScope
{
public:
    LevelScope(const FString& MapName) { AutomationOpenMap(MapName); }
    ~LevelScope() { ADD_LATENT_AUTOMATION_COMMAND(FExitGameCommand); }
};

}  // namespace Tests
}  // namespace STU

#endif
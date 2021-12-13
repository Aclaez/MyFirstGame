#if WITH_AUTOMATION_TESTS

#include "ShootThemUp/Public/Tests/TestUtils.h"

namespace STU
{
namespace Tests
{
UWorld* GetTestGameWorld()
{
    const TIndirectArray<FWorldContext>& WorldContexts = GEngine->GetWorldContexts();
    for (const FWorldContext& Context : WorldContexts)
    {
        if ((Context.WorldType == EWorldType::PIE || Context.WorldType == EWorldType::Game) && Context.World())
        {
            return Context.World();
        }
    }
    return nullptr;
}
}  // namespace Tests
}  // namespace STU

#endif
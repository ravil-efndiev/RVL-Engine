#pragma once

#include <Core/Core.hpp>

#define RVL_PCT(percent) (float)percent / 100.f

namespace Rvl
{

    class Random
    {
    public:
        static void Init();

        static int NextInt();
        static int NextInt(int max);

        static uint32_t NextUint();
        static uint32_t NextUint(uint32_t max);

        static double NextDouble();
        static double NextDouble(double max);

        static float NextFloat();
        static float NextFloat(float max);

        static int IntRange(int min, int max);
        static uint32_t UintRange(uint32_t min, uint32_t max);
        static double DoubleRange(double min, double max);
        static float FloatRange(float min, float max);

        static bool PercentChance(float chance);

    private:
        static std::mt19937 _generator;
    };
}


#pragma once

#include <memory>

struct Position {};

enum class PositionEvaluatorImplementation { NeuralNetwork };

namespace interfaces
{
   class PositionEvaluator
   {
      public:
         virtual ~PositionEvaluator() {};
         virtual void evaluatePosition(const Position & p) = 0;
   };
}

std::unique_ptr<interfaces::PositionEvaluator> createPositionEvaluator(PositionEvaluatorImplementation implementation);
#pragma once

#include <memory>

struct Position {};

namespace interfaces
{
   class PositionEvaluator
   {
      public:
         virtual ~PositionEvaluator() {};
         virtual void evaluatePosition(const Position & p) = 0;
   };
}

enum class PositionEvaluatorImplementation { NeuralNetwork };

class NeuralNetwork : public interfaces::PositionEvaluator
{
   public:
      NeuralNetwork() = default;
      ~NeuralNetwork() override {};
      void evaluatePosition(const Position & p) override;
};

std::unique_ptr<interfaces::PositionEvaluator> createPositionEvaluator(PositionEvaluatorImplementation implementation);
#pragma once

#include "position_evaluation/position_evaluator.h"

class NeuralNetwork : public interfaces::PositionEvaluator
{
   public:
      NeuralNetwork() = default;
      ~NeuralNetwork() override {};
      void evaluatePosition(const Position & p) override;
};
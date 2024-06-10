#include "position_evaluator.h"
#include "exceptions.h"
#include "position_evaluation/neural_network/neural_network.h"

std::unique_ptr<interfaces::PositionEvaluator> createPositionEvaluator(PositionEvaluatorImplementation implementation)
{
   switch (implementation) {
      case PositionEvaluatorImplementation::NeuralNetwork:
      {
         return std::make_unique<NeuralNetwork>();
      }
      default:
      {
         throw exceptions::InvalidEnumOption("Invalid PositionEvaluatorImplementation option");
      }
   }
}
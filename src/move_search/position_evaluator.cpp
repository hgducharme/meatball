#include "position_evaluator.h"
#include "exceptions.h"

void NeuralNetwork::evaluatePosition(const Position & p)
{  
}

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
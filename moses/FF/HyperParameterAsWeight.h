#pragma once

#include "StatelessFeatureFunction.h"

namespace Moses
{
class DecodeStep;

/**
  * Baseclass for phrase-table or generation table feature function
 **/
class HyperParameterAsWeight : public StatelessFeatureFunction
{
public:
  HyperParameterAsWeight(const std::string &line);

  virtual bool IsUseable(const FactorMask &mask) const
  { return true; }

  virtual void Evaluate(const Phrase &source
                        , const TargetPhrase &targetPhrase
                        , ScoreComponentCollection &scoreBreakdown
                        , ScoreComponentCollection &estimatedFutureScore) const
  {}

  virtual void Evaluate(const InputType &input
                        , const InputPath &inputPath
                        , const TargetPhrase &targetPhrase
                        , ScoreComponentCollection &scoreBreakdown
                        , ScoreComponentCollection *estimatedFutureScore = NULL) const
  {}

  virtual void Evaluate(const Hypothesis& hypo,
                        ScoreComponentCollection* accumulator) const
  {}

  /**
    * Same for chart-based features.
    **/
  virtual void EvaluateChart(const ChartHypothesis &hypo,
                             ScoreComponentCollection* accumulator) const
  {}

};

} // namespace




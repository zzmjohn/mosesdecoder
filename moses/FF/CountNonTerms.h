#pragma once

#include "StatelessFeatureFunction.h"

namespace Moses
{

class CountNonTerms : public StatelessFeatureFunction
{
public:
  CountNonTerms(const std::string &line);
  bool IsUseable(const FactorMask &mask) const
  { return true; }

  void Evaluate(const Phrase &source
                , const TargetPhrase &targetPhrase
                , ScoreComponentCollection &scoreBreakdown
                , ScoreComponentCollection &estimatedFutureScore) const;

  void Evaluate(const InputType &input
                , const InputPath &inputPath
                , const TargetPhrase &targetPhrase
                , ScoreComponentCollection &scoreBreakdown
                , ScoreComponentCollection *estimatedFutureScore = NULL) const
  {}

  void Evaluate(const Hypothesis& hypo,
                ScoreComponentCollection* accumulator) const
  {}

  void EvaluateChart(
    const ChartHypothesis& hypo,
    ScoreComponentCollection* accumulator) const
  {}

  void SetParameter(const std::string& key, const std::string& value);

protected:
  bool m_all, m_sourceSyntax, m_targetSyntax;
};

}


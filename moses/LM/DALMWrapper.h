// $Id$
#pragma once

#include <vector>
#include <boost/bimap.hpp>
#include "Implementation.h"
#include "moses/Hypothesis.h"

namespace DALM
{
class Logger;
class Vocabulary;
class State;
class LM;

typedef unsigned int VocabId;
}

namespace Moses
{
class Factor;

class LanguageModelDALM : public LanguageModel
{
public:
  LanguageModelDALM(const std::string &line);
  virtual ~LanguageModelDALM();
  
  void Load();

  virtual const FFState *EmptyHypothesisState(const InputType &/*input*/) const;

  virtual void CalcScore(const Phrase &phrase, float &fullScore, float &ngramScore, size_t &oovCount) const;

  virtual FFState *Evaluate(const Hypothesis &hypo, const FFState *ps, ScoreComponentCollection *out) const;

  virtual FFState *EvaluateChart(const ChartHypothesis& hypo, int featureID, ScoreComponentCollection *out) const;

  virtual bool IsUseable(const FactorMask &mask) const;

	virtual void SetParameter(const std::string& key, const std::string& value);
	
protected:
  const Factor *m_beginSentenceFactor;

  FactorType m_factorType;

  std::string	m_filePath;
  size_t			m_nGramOrder; //! max n-gram length contained in this LM

	DALM::Logger *m_logger;
	DALM::Vocabulary *m_vocab;
	DALM::LM *m_lm;
	DALM::VocabId wid_start, wid_end;

	mutable std::vector<DALM::VocabId> m_vocabMap;

	void CreateVocabMapping(const std::string &wordstxt);
	DALM::VocabId GetVocabId(const Factor *factor) const;

private:
  // Convert last words of hypothesis into vocab ids, returning an end pointer.
  DALM::VocabId *LastIDs(const Hypothesis &hypo, DALM::VocabId *indices) const {
    DALM::VocabId *index = indices;
    DALM::VocabId *end = indices + m_nGramOrder - 1;
    int position = hypo.GetCurrTargetWordsRange().GetEndPos();
    for (; ; ++index, --position) {
      if (index == end) return index;
      if (position == -1) {
        *index = wid_start;
        return index + 1;
      }
      *index = GetVocabId(hypo.GetWord(position).GetFactor(m_factorType));
    }
  }
};

}


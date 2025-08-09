#ifndef RESPWAVEFORMGENERATOR_H
#define RESPWAVEFORMGENERATOR_H
#include "idatagenerator.h"
class RespWaveFormGenerator : public IDataGenerator {
public:
  RespWaveFormGenerator();
  virtual ~RespWaveFormGenerator() = default;
  virtual const qreal &generateData() override;

private:
  qreal m_phase;
  qreal m_frequency;
  qreal m_samplingRate;
  qreal m_currentValue;
};

#endif // RESPWAVEFORMGENERATOR_H

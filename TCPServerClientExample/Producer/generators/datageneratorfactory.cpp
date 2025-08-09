#include "datageneratorfactory.h"
#include "bodytemperaturegenerator.h"
#include "ecggenerator.h"
#include "etco2generator.h"
#include "heartrategenerator.h"
#include "nibpdiastolicgenerator.h"
#include "nibpsystolicgenerator.h"
#include "ppggenerator.h"
#include "resprategenerator.h"
#include "respwaveformgenerator.h"
#include "spo2generator.h"

std::unique_ptr<IDataGenerator> DataGeneratorFactory::create(MessageType type) {
  switch (type) {
  case MessageType::ECG:
    return std::make_unique<ECGGenerator>();
  case MessageType::PPG:
    return std::make_unique<PPGGenerator>();
  case MessageType::RespiratoryWaveForm:
    return std::make_unique<RespWaveFormGenerator>();
  case MessageType::HeartRate:
    return std::make_unique<HeartRateGenerator>();
  case MessageType::RespiratoryRate:
    return std::make_unique<RespRateGenerator>();
  case MessageType::Spo2:
    return std::make_unique<Spo2Generator>();
  case MessageType::NIBPDiastole:
    return std::make_unique<NIBPDiastolicGenerator>();
  case MessageType::NIBPSystole:
    return std::make_unique<NIBPSystolicGenerator>();
  case MessageType::BodyTemp:
    return std::make_unique<BodyTemperatureGenerator>();
  case MessageType::EtCo2:
    return std::make_unique<EtCO2Generator>();
  default:
    return nullptr;
  }
}

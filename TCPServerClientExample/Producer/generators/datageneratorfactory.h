#ifndef DATAGENERATORFACTORY_H
#define DATAGENERATORFACTORY_H

#include "commonMessages.h"
#include "idatagenerator.h"
#include <memory>
class DataGeneratorFactory {
public:
  static std::unique_ptr<IDataGenerator> create(MessageType type);
};

#endif // DATAGENERATORFACTORY_H

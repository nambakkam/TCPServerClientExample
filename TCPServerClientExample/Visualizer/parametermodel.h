#ifndef PARAMETERMODEL_H
#define PARAMETERMODEL_H

#include "commonMessages.h"
#include <QAbstractListModel>
#include <QJsonObject>

struct ParameterItem {
  CommonMessages::MessageType type;
  QString name;
  QString units;
  double value;
  double minValue;
  double maxValue;
  QString needleColor;
  QString progressColor;
};

class ParameterModel : public QAbstractListModel {
  Q_OBJECT

public:
  enum ParameterRoles {
    TypeRole = Qt::UserRole + 1,
    NameRole,
    UnitsRole,
    ValueRole,
    MinValueRole,
    MaxValueRole,
    NeedleColorRole,
    ProgressColorRole
  };
  Q_ENUM(ParameterRoles)

  explicit ParameterModel(QObject *parent = nullptr);

  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override;
  QHash<int, QByteArray> roleNames() const override;

public slots:
  void updateFromJson(const QJsonObject &obj);

private:
  int findIndexByType(CommonMessages::MessageType type) const;

  QVector<ParameterItem> m_parameters;
};

#endif // PARAMETERMODEL_H

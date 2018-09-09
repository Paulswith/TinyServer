#ifndef TSBODIESMODEL_H
#define TSBODIESMODEL_H

#include <QStandardItemModel>


class TSBodiesModel : public QStandardItemModel
{
public:
//    explicit TSBodiesModel();
    explicit TSBodiesModel(QObject *parent = nullptr);
};

#endif // TSBODIESMODEL_H

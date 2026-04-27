#ifndef MODELPARTLIST_H
#define MODELPARTLIST_H

#include <QAbstractItemModel>
#include <QString>

class ModelPart;

class ModelPartList : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit ModelPartList(const QString &name, QObject *parent = nullptr);
    ~ModelPartList() override;

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;

    ModelPart* getRootItem() const;

private:
    ModelPart* getItem(const QModelIndex &index) const;

    ModelPart* m_rootItem = nullptr;
    QString    m_name;
};

#endif // MODELPARTLIST_H

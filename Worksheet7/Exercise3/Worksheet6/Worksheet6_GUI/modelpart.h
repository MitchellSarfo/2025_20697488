#ifndef MODELPART_H
#define MODELPART_H

#include <QVector>
#include <QVariant>

class ModelPart
{
public:
    explicit ModelPart(const QVector<QVariant> &data, ModelPart *parent = nullptr);
    ModelPart(const QString &name, const QString &visible, ModelPart *parent = nullptr);
    ~ModelPart();

    void appendChild(ModelPart *child);

    ModelPart* child(int row) const;
    int childCount() const;

    int columnCount() const;
    QVariant data(int column) const;

    int row() const;
    ModelPart* parentItem() const;

    bool setData(int column, const QVariant &value);

private:
    QVector<ModelPart*> m_children;
    QVector<QVariant>  m_itemData;
    ModelPart*         m_parent = nullptr;
};

#endif // MODELPART_H

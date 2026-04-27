#include "ModelPart.h"

ModelPart::ModelPart(const QVector<QVariant> &data, ModelPart *parent)
    : m_itemData(data), m_parent(parent)
{
}

ModelPart::ModelPart(const QString &name, const QString &visible, ModelPart *parent)
    : m_itemData({ name, visible }), m_parent(parent)
{
}

ModelPart::~ModelPart()
{
    qDeleteAll(m_children);
    m_children.clear();
}

void ModelPart::appendChild(ModelPart *child)
{
    if (!child) return;
    m_children.append(child);
}

ModelPart* ModelPart::child(int row) const
{
    if (row < 0 || row >= m_children.size()) return nullptr;
    return m_children.at(row);
}

int ModelPart::childCount() const
{
    return m_children.size();
}

int ModelPart::columnCount() const
{
    return m_itemData.size();
}

QVariant ModelPart::data(int column) const
{
    if (column < 0 || column >= m_itemData.size()) return {};
    return m_itemData.at(column);
}

int ModelPart::row() const
{
    if (!m_parent) return 0;
    return m_parent->m_children.indexOf(const_cast<ModelPart*>(this));
}

ModelPart* ModelPart::parentItem() const
{
    return m_parent;
}

bool ModelPart::setData(int column, const QVariant &value)
{
    if (column < 0 || column >= m_itemData.size()) return false;
    m_itemData[column] = value;
    return true;
}

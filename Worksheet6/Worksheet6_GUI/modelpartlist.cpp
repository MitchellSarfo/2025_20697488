#include "ModelPartList.h"
#include "ModelPart.h"

ModelPartList::ModelPartList(const QString &name, QObject *parent)
    : QAbstractItemModel(parent), m_name(name)
{
    // Header row (2 columns): Part name, Visible
    m_rootItem = new ModelPart(QVector<QVariant>{ "Part", "Visible" });
}

ModelPartList::~ModelPartList()
{
    delete m_rootItem;
    m_rootItem = nullptr;
}

ModelPart* ModelPartList::getRootItem() const
{
    return m_rootItem;
}

ModelPart* ModelPartList::getItem(const QModelIndex &index) const
{
    if (index.isValid()) {
        auto *item = static_cast<ModelPart*>(index.internalPointer());
        if (item) return item;
    }
    return m_rootItem;
}

QModelIndex ModelPartList::index(int row, int column, const QModelIndex &parentIndex) const
{
    if (!hasIndex(row, column, parentIndex)) return {};

    ModelPart *parentItem = getItem(parentIndex);
    ModelPart *childItem = parentItem->child(row);
    if (!childItem) return {};

    return createIndex(row, column, childItem);
}

QModelIndex ModelPartList::parent(const QModelIndex &index) const
{
    if (!index.isValid()) return {};

    ModelPart *childItem = getItem(index);
    ModelPart *parentItem = childItem->parentItem();

    if (!parentItem || parentItem == m_rootItem) return {};
    return createIndex(parentItem->row(), 0, parentItem);
}

int ModelPartList::rowCount(const QModelIndex &parentIndex) const
{
    if (parentIndex.column() > 0) return 0;
    ModelPart *parentItem = getItem(parentIndex);
    return parentItem->childCount();
}

int ModelPartList::columnCount(const QModelIndex &parentIndex) const
{
    Q_UNUSED(parentIndex);
    return m_rootItem ? m_rootItem->columnCount() : 0;
}

QVariant ModelPartList::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) return {};

    if (role != Qt::DisplayRole && role != Qt::EditRole) return {};

    ModelPart *item = getItem(index);
    return item->data(index.column());
}

Qt::ItemFlags ModelPartList::flags(const QModelIndex &index) const
{
    if (!index.isValid()) return Qt::NoItemFlags;
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
}

QVariant ModelPartList::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        return m_rootItem->data(section);
    }
    return {};
}

bool ModelPartList::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role != Qt::EditRole || !index.isValid()) return false;

    ModelPart *item = getItem(index);
    if (!item->setData(index.column(), value)) return false;

    emit dataChanged(index, index, {Qt::DisplayRole, Qt::EditRole});
    return true;
}

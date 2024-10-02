#include <QAbstractTableModel>
#include <QVector>

class TaskModel : public QAbstractTableModel {
    Q_OBJECT

public:
    struct Task {
        QString name;
        QString description;
        int priority;
        QString status;
        QDate deadline;
        QDateTime creationTime;
    };

    TaskModel(QObject *parent = nullptr) : QAbstractTableModel(parent) {}

    // 返回行数
    int rowCount(const QModelIndex &parent = QModelIndex()) const override {
        return tasks.size();
    }

    // 返回列数
    int columnCount(const QModelIndex &parent = QModelIndex()) const override {
        return 6;  // Task 有 6 个字段
    }

    // 返回每个单元格的数据
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override {
        if (!index.isValid() || role != Qt::DisplayRole)
            return QVariant();

        const Task &task = tasks[index.row()];
        switch (index.column()) {
            case 0: return task.name;
            case 1: return task.description;
            case 2: return task.priority;
            case 3: return task.status;
            case 4: return task.deadline.toString();
            case 5: return task.creationTime.toString();
            default: return QVariant();
        }
    }

    // 设置列头的名称
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override {
        if (role != Qt::DisplayRole)
            return QVariant();

        if (orientation == Qt::Horizontal) {
            switch (section) {
                case 0: return "Name";
                case 1: return "Description";
                case 2: return "Priority";
                case 3: return "Status";
                case 4: return "Deadline";
                case 5: return "Creation Time";
                default: return QVariant();
            }
        }
        return QVariant();
    }

    // 添加任务
    void addTask(const Task &task) {
        beginInsertRows(QModelIndex(), tasks.size(), tasks.size());
        tasks.append(task);
        endInsertRows();
    }

private:
    QVector<Task> tasks;
};

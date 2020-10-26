#pragma once
#include <QAbstractListModel>
#include <unordered_set>
#include <filesystem>
#include <deque>
#include <QString>
#include <QStringList>



namespace std
{
    template<>
    struct hash<std::filesystem::path>
    {
        std::size_t operator()(const std::filesystem::path& path)const
        {
            return std::hash<std::string>()(path.u8string());
        }
    };
}

namespace Hix
{
	namespace QML
	{
		class FilesystemModel : public QAbstractListModel
		{
            Q_OBJECT
            Q_PROPERTY(QString folder READ folder WRITE setFolder NOTIFY folderChanged)
            Q_PROPERTY(QString parentFolder READ parentFolder NOTIFY folderChanged)
            Q_PROPERTY(QStringList nameFilters READ nameFilters WRITE setNameFilters)
            Q_PROPERTY(bool showFiles READ showFiles WRITE setShowFiles REVISION 1)
            Q_PROPERTY(bool showDirs READ showDirs WRITE setShowDirs)
            Q_PROPERTY(bool showDirsFirst READ showDirsFirst WRITE setShowDirsFirst)
            Q_PROPERTY(bool sortReversed READ sortReversed WRITE setSortReversed)
            Q_PROPERTY(SortField sortField READ sortField WRITE setSortField)

        public:
            explicit FilesystemModel(QObject* parent = nullptr);


            int rowCount(const QModelIndex& parent) const override;
            QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const override;
            QVariant data(const QModelIndex& index, int role) const override;
            QHash<int, QByteArray> roleNames() const override;


            enum class SortField { Unsorted, Name, Time, Size, Type };
            Q_ENUM(SortField)
            SortField sortField() const;
            void setSortField(SortField field);
            QString folder() const;
            void setFolder(const QString& folder);
            QString parentFolder() const;
            bool showFiles() const;
            void setShowFiles(bool showFiles);
            bool showDirs() const;
            void setShowDirs(bool showDirs);
            bool showDirsFirst() const;
            void setShowDirsFirst(bool showDirsFirst);
            QStringList nameFilters() const;
            void setNameFilters(const QStringList& filters);
            bool sortReversed() const;
            void setSortReversed(bool rev);

            Q_INVOKABLE bool isFolder(int index) const;
            Q_INVOKABLE QVariant get(int idx, const QString& property) const;
            Q_INVOKABLE int indexOf(const QString& file) const;
            Q_INVOKABLE QString getUSB() const;

        signals:
            void folderChanged();
            void rowCountChanged() const;
            void folderChangeError();

        private:
            std::filesystem::path _current;
            QHash<int, QByteArray> _roleNames;
            SortField _sortField = SortField::Name;
            std::unordered_set<std::filesystem::path> _nameFilters;
            bool _sortReversed = false;
            bool _showFiles = true;
            bool _showDirs = true;
            bool _showDirsFirst = false;
            bool _caseSensitive = true;
            bool _sortCaseSensitive = true;
            std::deque<std::filesystem::path> _data;

            void updateSorting();
            void applyNameFilter();

		};


	}
}

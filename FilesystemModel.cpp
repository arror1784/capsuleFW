#include "FilesystemModel.h"
#include <chrono>
using namespace Hix;
using namespace Hix::QML;



inline QString fromStdPath(const std::filesystem::path& path)
{
    auto u8str = path.u8string();
    return QString::fromUtf8(u8str.c_str(), u8str.size());
}
inline std::filesystem::path fromQtPath(const QString& path)
{
    return std::filesystem::u8path(path.toUtf8().toStdString());
}

//jesus what the fuck?

enum Roles {
    FileNameRole = Qt::UserRole + 1,
    FilePathRole = Qt::UserRole + 2,
    FileBaseNameRole = Qt::UserRole + 3,
    FileSuffixRole = Qt::UserRole + 4,
    FileSizeRole = Qt::UserRole + 5,
    FileLastModifiedRole = Qt::UserRole + 6,
    //FileLastReadRole = Qt::UserRole + 7,
    FileIsDirRole = Qt::UserRole + 7,
    //FileUrlRole = Qt::UserRole + 9
};



Hix::QML::FilesystemModel::FilesystemModel(QObject* parent)
{
    _roleNames[FileNameRole] = "fileName";
    _roleNames[FilePathRole] = "filePath";
    _roleNames[FileBaseNameRole] = "fileBaseName";
    _roleNames[FileSuffixRole] = "fileSuffix";
    _roleNames[FileSizeRole] = "fileSize";
    _roleNames[FileLastModifiedRole] = "fileModified";
    //_roleNames[FileLastReadRole] = "fileAccessed";
    _roleNames[FileIsDirRole] = "fileIsDir";
    //_roleNames[FileUrlRole] = "fileURL";

}

int Hix::QML::FilesystemModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return _data.size();
}

QModelIndex Hix::QML::FilesystemModel::index(int row, int column, const QModelIndex& parent) const
{
    return createIndex(row, 0);
}

QVariant Hix::QML::FilesystemModel::data(const QModelIndex& index, int role) const
{

    QVariant rv;

    if (index.row() >= _data.size())
        return rv;
    std::error_code hiddenError;
    auto& e = _data[index.row()];
    switch (role)
    {
    case FileNameRole:
        rv = fromStdPath(e.filename());
        break;
    case FilePathRole:
        rv = fromStdPath(e);
        break;
    case FileBaseNameRole:
        rv = fromStdPath(e.stem());
        break;
    case FileSuffixRole:
        rv = fromStdPath(e.extension());
        break;
    case FileSizeRole:
        rv= (uint)std::filesystem::file_size(e, hiddenError);
        break;
    case FileLastModifiedRole:
    {
        auto timePt = std::filesystem::last_write_time(e, hiddenError);
        auto microsecondsUTC = std::chrono::duration_cast<std::chrono::microseconds>(timePt.time_since_epoch()).count();
        rv = (uint)microsecondsUTC;
        break;
    }
    //case FileLastReadRole:
    //{
    //    auto timePt = std::filesystem::last_write_time(e, hiddenError);
    //    auto microsecondsUTC = std::chrono::duration_cast<std::chrono::microseconds>(timePt.time_since_epoch()).count();
    //    rv = microsecondsUTC;
    //    break;
    //}   
    case FileIsDirRole:
        rv = std::filesystem::is_directory(e);
        break;
    //case FileUrlRole:
    //    rv = QUrl::fromLocalFile(e.filePath());
    //    break;
    default:
        break;
    }
    return rv;
}

QHash<int, QByteArray> Hix::QML::FilesystemModel::roleNames() const
{
    return _roleNames;
}

Hix::QML::FilesystemModel::SortField Hix::QML::FilesystemModel::sortField() const
{
    return _sortField;
}

void Hix::QML::FilesystemModel::setSortField(SortField field)
{
    if (field != _sortField) {
        _sortField = field;
        updateSorting();
    }
}

QString Hix::QML::FilesystemModel::folder() const
{

    return fromStdPath(_current);
}

void Hix::QML::FilesystemModel::setFolder(const QString& folder)
{
    auto path = fromQtPath(folder);
    beginResetModel();
    _current = path;
    if (!std::filesystem::exists(_current) || !std::filesystem::is_directory(_current))
    {
        _data.clear();
        endResetModel();
        emit rowCountChanged();
    }
    else
    {
        _data.clear();
        //populate file list
        for (const auto& entry : std::filesystem::directory_iterator(path))
        {
            if (std::filesystem::is_regular_file(entry) && _showFiles)
            {
                _data.emplace_back(entry);
            }
            if (std::filesystem::is_directory(entry) && _showDirs)
            {
                _data.emplace_back(entry);
            }
        }
        applyNameFilter();
        updateSorting();
        //signal end of change
        endResetModel();
        emit rowCountChanged();
        emit folderChanged();
    }
}

QString Hix::QML::FilesystemModel::parentFolder() const
{
    return fromStdPath(_current.parent_path());
}

bool Hix::QML::FilesystemModel::showFiles() const
{
    return _showFiles;
}

void Hix::QML::FilesystemModel::setShowFiles(bool showFiles)
{
    _showFiles = showFiles;
}

bool Hix::QML::FilesystemModel::showDirs() const
{
    return _showDirs;
}

void Hix::QML::FilesystemModel::setShowDirs(bool showDirs)
{
    _showDirs = showDirs;
}

bool Hix::QML::FilesystemModel::showDirsFirst() const
{
    return _showDirsFirst;
}

void Hix::QML::FilesystemModel::setShowDirsFirst(bool showDirsFirst)
{
    _showDirsFirst = showDirsFirst;
}

QStringList Hix::QML::FilesystemModel::nameFilters() const
{
    QStringList qtList;
    for (auto& e : _nameFilters)
    {
        qtList.push_back(fromStdPath(e));
    }
    return qtList;
}

void Hix::QML::FilesystemModel::setNameFilters(const QStringList& filters)
{
    std::unordered_set<std::filesystem::path> newFilters;
    for (auto& e : filters)
    {
        newFilters.insert(fromQtPath(e));
    }
    if (_nameFilters != newFilters)
    {
        _nameFilters = newFilters;
        applyNameFilter();
    }
}

bool Hix::QML::FilesystemModel::sortReversed() const
{
    return _sortReversed;
}

void Hix::QML::FilesystemModel::setSortReversed(bool rev)
{
    _sortReversed = rev;
}

bool Hix::QML::FilesystemModel::isFolder(int index) const
{
    return std::filesystem::is_directory(_current);
}

QVariant Hix::QML::FilesystemModel::get(int idx, const QString& property) const
{
    return QVariant();
}

int Hix::QML::FilesystemModel::indexOf(const QString& file) const
{
    return  int();
}



void updateSortingImpl(bool isDir, bool isReverse,
    FilesystemModel::SortField sort,  std::deque<std::filesystem::path>& paths)
{
    switch (sort) {
    case FilesystemModel::SortField::Unsorted:
        return;
        break;
    case FilesystemModel::SortField::Name:
        std::sort(paths.begin(), paths.end(),
            [isReverse](const std::filesystem::path& a, const std::filesystem::path& b) ->bool {
                return  isReverse ^ (a.filename() > b.filename());
            });
        break;
    case FilesystemModel::SortField::Time:
        std::sort(paths.begin(), paths.end(),
            [isReverse](const std::filesystem::path& a, const std::filesystem::path& b) ->bool {
                std::error_code hiddenError;
                return  isReverse ^ (std::filesystem::last_write_time(a, hiddenError) >
                    std::filesystem::last_write_time(b, hiddenError));
            });
        break;
    case FilesystemModel::SortField::Size:
        if (!isDir)
        {
            std::sort(paths.begin(), paths.end(),
                [isReverse](const std::filesystem::path& a, const std::filesystem::path& b) ->bool {
                    std::error_code hiddenError;
                    return  isReverse ^ (std::filesystem::file_size(a, hiddenError) >
                        std::filesystem::file_size(b, hiddenError));
                });
        }
        break;
    case FilesystemModel::SortField::Type:
        if (!isDir)
        {
            std::sort(paths.begin(), paths.end(),
                [isReverse](const std::filesystem::path& a, const std::filesystem::path& b) ->bool {
                    return  isReverse ^ (a.extension() > b.extension());
                });
        }
        break;
    }
}

void Hix::QML::FilesystemModel::updateSorting()
{
    //divide into directories and files
    std::deque<std::filesystem::path> files;
    std::deque<std::filesystem::path> dirs;
    for (auto& e : _data)
    {
        if (std::filesystem::is_directory(e))
            dirs.emplace_back(e);
        else
            files.emplace_back(e);
    }
    updateSortingImpl(true, _sortReversed, _sortField, dirs);
    updateSortingImpl(false, _sortReversed, _sortField, files);
    //if show directory first
    if (_showDirsFirst)
    {
        dirs.insert(dirs.end(), files.begin(), files.end());
        _data = std::move(dirs);
    }
    else
    {
        files.insert(files.end(), dirs.begin(), dirs.end());
        _data = std::move(files);
    }
}

void Hix::QML::FilesystemModel::applyNameFilter()
{
    auto itr = _data.begin();
    while (itr != _data.end())
    {
        if (std::filesystem::is_regular_file(*itr) && _nameFilters.find(itr->extension()) == _nameFilters.cend())
            itr = _data.erase(itr);
        else
            ++itr;
    }
}

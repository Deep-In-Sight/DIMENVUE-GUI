#include <scanView.hpp>
#include <context.hpp>

namespace dimenvue
{
    namespace backend
    {
        struct ScanViewInterface::Impl
        {
            void reset()
            {
                _stats.isDirty = false;
                // clear all dataset
            }

            void save()
            {
                if (!_stats.isDirty)
                {
                    return;
                }
                setDirty(false);
                _stats.modifiedTime = std::tm();
            }

            void load()
            {
                // open dataset
            }

            void setDirty(bool dirty)
            {
                _stats.isDirty = dirty;
                if (_dirtyCallback)
                {
                    _dirtyCallback(dirty);
                }
            }

            bool getDirty()
            {
                return _stats.isDirty;
            }

            void setDirtyCallback(std::function<void(bool)> callback)
            {
                _dirtyCallback = callback;
            }

            std::string getThumbnail()
            {
                // save thumbnail to a tmp file
                return "/path/to/thumbnail.png";
            }

            void readStatsFromDataset(const std::string &path)
            {
                _stats.name = "Scan Name";
                _stats.path = path;
                _stats.createdTime = std::tm();
                _stats.modifiedTime = std::tm();
                _stats.areaSizeSqM = 100.0f;
                _stats.densityPercentage = 0.5f;
                setDirty(false);
                _stats.thumbnailPath = getThumbnail();
            }

            std::function<void(bool)> _dirtyCallback;
            ScanStats _stats;
        };

        ScanViewInterface::ScanViewInterface(const std::string &path) : _impl(new Impl)
        {
            _impl->readStatsFromDataset(path);
        }

        ScanViewInterface::~ScanViewInterface() = default;

        void ScanViewInterface::reset()
        {
            _impl->reset();
        }

        void ScanViewInterface::save()
        {
            _impl->save();
        }

        bool ScanViewInterface::isDirty()
        {
            return _impl->_stats.isDirty;
        }

        void ScanViewInterface::setDirtyCallback(std::function<void(bool)> callback)
        {
            _impl->setDirtyCallback(callback);
        }

        bool ScanViewInterface::isLowDensity()
        {
            return true;
        }

        const ScanStats &ScanViewInterface::getStats() const
        {
            return _impl->_stats;
        }
    } // namespace backend
} // namespace dimenvue
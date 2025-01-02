#include <scanView.hpp>
#include <context.hpp>
#include <thread>
#include <iostream>

namespace dimenvue
{
    namespace backend
    {
        struct ScanViewInterface::Impl
        {
            ~Impl() {
                if (simRunning)
                {
                    std::system("simulation.sh stop");
                }
            }
            
            void initialize(const std::string& path) {
                readStatsFromDataset(path);
                std::cout << "starting sim playback" << std::endl;
                startSimPlayback();
            }

            void reset()
            {
                _stats.isDirty = false;
                std::cout << "restarting sim playback" << std::endl;
                startSimPlayback();
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

            void startSimPlayback()
            {
                std::cout << "Starting sim playback" << std::endl;

                if (simRunning)
                {
                    std::system("simulation.sh stop");
                }
                
                std::system("simulation.sh start");
                simRunning = true;
            }

            
            static bool simRunning;
            std::function<void(bool)> _dirtyCallback;
            ScanStats _stats;
        };

        bool ScanViewInterface::Impl::simRunning = false;

        ScanViewInterface::ScanViewInterface(const std::string &path) : _impl(new Impl)
        {
            std::cout << "ScanViewInterface constructor" << std::endl;
            _impl->initialize(path);
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
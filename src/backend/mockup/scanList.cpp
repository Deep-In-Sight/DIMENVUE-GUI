#include <scanList.hpp>
#include <scanView.hpp>
#include <thread>

namespace dimenvue
{
    namespace backend
    {
        struct ScanListInterface::Impl
        {
            void initializeList()
            {
                for (int i = 0; i < 10; i++)
                {
                    _scanList.push_back(std::make_shared<ScanViewInterface>("dataset_name.hdf5"));
                }
            }

            bool uploadItems(const std::list<ScanViewPtr> &scans)
            {
                std::this_thread::sleep_for(std::chrono::seconds(1));
                return true;
            }

            bool deleteItems(const std::list<ScanViewPtr> &scans)
            {
                std::this_thread::sleep_for(std::chrono::seconds(1));

                return true;
            }
            std::shared_ptr<ScanViewInterface> create(const std::string &scanName)
            {
                auto newScan = std::make_shared<ScanViewInterface>(scanName);
                _scanList.push_back(newScan);
                return newScan;
            }

            std::list<ScanViewPtr> _scanList;
        };

        ScanListInterface::ScanListInterface() : _impl(new Impl)
        {
            _impl->initializeList();
        }

        ScanListInterface::~ScanListInterface() = default;

        const std::list<ScanViewPtr> &ScanListInterface::getScanList()
        {
            return _impl->_scanList;
        }

        std::future<bool> ScanListInterface::uploadAsync(const std::list<ScanViewPtr> &scans)
        {
            return std::async(std::launch::async, [this, scans]
                              { return _impl->uploadItems(scans); });
        }

        std::future<bool> ScanListInterface::synchronizeAllScansAsync()
        {
            return std::async(std::launch::async, [this]
                              { return _impl->uploadItems(_impl->_scanList); });
        }

        std::future<bool> ScanListInterface::deleteAsync(const std::list<ScanViewPtr> &scans)
        {
            return std::async(std::launch::async, [this, scans]
                              { return _impl->deleteItems(scans); });
        }

        ScanViewPtr ScanListInterface::createNewScan(const std::string &scanName)
        {
            return _impl->create(scanName);
        }

    } // namespace backend
} // namespace dimenvue
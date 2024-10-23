#pragma once

#include <string>
#include <list>
#include <memory>
#include <future>

namespace dimenvue
{
    namespace backend
    {

        class ScanViewInterface;
        using ScanViewPtr = std::shared_ptr<ScanViewInterface>;

        /**
         * @brief an interface to manage list of scan views.
         *
         */
        class ScanListInterface
        {
        public:
            /**
             * @brief Construct a new Scan List Interface object.
             * It checks internal storage for dataset files, and create a view for each of them.
             *
             */
            ScanListInterface();
            ~ScanListInterface();

            /**
             * @brief Get the Scan List object
             *
             * @return const std::list<ScanViewPtr>&
             */
            const std::list<ScanViewPtr> &getScanList();
            /**
             * @brief upload the selected scans to remote server asynchronously. Return true if uploaded, false otherwise.
             *
             * @param scans
             * @return std::future<bool> caller should check the status of this future, either blocking or non-blocking.
             */
            std::future<bool> uploadAsync(const std::list<ScanViewPtr> &scans);
            /**
             * @brief upload all new and modified scans to remote server asynchronously. Return true if uploaded, false otherwise.
             *
             * @return std::future<bool>
             */
            std::future<bool> synchronizeAllScansAsync();
            /**
             * @brief delete the selected scans from local storage asynchronously. Return true if deleted, false otherwise.
             *
             * @param scans
             * @return std::future<bool> caller should check the status of this future, either blocking or non-blocking.
             */
            std::future<bool> deleteAsync(const std::list<ScanViewPtr> &scans);
            /**
             * @brief Check if a scan with the same name already exists.
             *
             * @param scanName
             * @return true
             * @return false
             */
            bool isScanNameExist(const std::string &scanName);
            /**
             * @brief Create a new ScanView object and set context current ScanView.
             *
             * @param scanName
             */
            ScanViewPtr createNewScan(const std::string &scanName = "");

        private:
            struct Impl;
            std::unique_ptr<Impl> _impl;
        };
    } // namespace backend
} // namespace dimenvue
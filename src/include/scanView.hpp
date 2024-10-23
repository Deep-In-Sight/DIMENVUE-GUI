#pragma once

#include <string>
#include <ctime>
#include <memory>
#include <functional>

namespace dimenvue
{
    namespace backend
    {

        struct ScanStats
        {
            std::string name;
            std::string path;
            std::tm createdTime;
            std::tm modifiedTime;
            float areaSizeSqM;
            float densityPercentage;
            bool isDirty;
            std::string thumbnailPath;
        };

        /**
         * @brief the interface to provide access to a scan dataset. A scan view gives an handle to the underlying dataset (probably a hdf5 construct) and its stats.
         *
         */
        class ScanViewInterface
        {
        public:
            /**
             * @brief Construct a new Scan View Interface object.
             * Open the dataset with given name, and read the stats.
             *
             * @param name
             */
            ScanViewInterface(const std::string &name);
            ~ScanViewInterface();

            /**
             * @brief clear all dataset and reset the stats.
             *
             */
            void reset();
            /**
             * @brief save dataset to disk
             *
             */
            void save();
            /**
             * @brief true if the dataset is not saved, false otherwise.
             *
             * @return true
             * @return false
             */
            bool isDirty();
            /**
             * @brief Set a callback to notify that dataset is dirty.
             * For example, for UI to know and enable the save button.
             *
             * @param callback
             */
            void setDirtyCallback(std::function<void(bool)> callback);
            /**
             * @brief check if scan has low density
             *
             * @return true
             * @return false
             */
            bool isLowDensity();
            /**
             * @brief Get the statistics of the dataset.
             *
             * @return const ScanStats&
             */
            const ScanStats &getStats() const;

        protected:
            struct Impl;
            std::unique_ptr<Impl> _impl;
        };
    }
}
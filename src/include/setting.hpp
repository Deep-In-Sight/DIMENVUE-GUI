#pragma once

#include <string>
#include <map>
#include <memory>
#include <vector>
#include <future>

namespace dimenvue
{
    namespace backend
    {
        using UserInfo = std::map<std::string, std::string>;
        using DeviceInfo = std::map<std::string, std::string>;

        /**
         * @brief interface to the setting of the device.
         *
         */
        class SettingInterface
        {
        public:
            SettingInterface();
            ~SettingInterface();

            /**
             * @brief get a list of wifi ssids.
             *
             * @return const std::vector<std::string>
             */
            const std::vector<std::string> getSSIDList();
            /**
             * @brief connect to a wifi with the given SSID and password. Return true if connected, false otherwise.
             *
             * @param SSID
             * @param password
             * @return std::future<bool> caller should check the status of this future, either blocking or non-blocking.
             */
            std::future<bool> connectWifiAsync(const std::string &SSID, const std::string &password);
            /**
             * @brief authenticate an user with the given user and password. Return true if authenticated, false otherwise.
             *
             * @param user
             * @param password
             * @return std::future<bool> caller should check the status of this future, either blocking or non-blocking.
             */
            std::future<bool> userLoginAsync(const std::string &user, const std::string &password);
            /**
             * @brief Get the Current Wifi SSID object.
             *
             * @return const std::string&
             */
            const std::string &getCurrentWifiSSID();
            /**
             * @brief Get the Device Info object. Check keys for the information.
             *
             * @return const DeviceInfo&
             */
            const DeviceInfo &getDeviceInfo();
            /**
             * @brief Get the User Info object. Check keys for the information.
             *
             * @return const UserInfo&
             */
            const UserInfo &getUserInfo();

        private:
            struct Impl;
            std::unique_ptr<Impl> _impl;
        };
    } // namespace backend
} // namespace dimenvue
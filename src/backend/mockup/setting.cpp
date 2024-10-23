#include <setting.hpp>
#include <systemStatus.hpp>

namespace dimenvue
{
    namespace backend
    {
        struct SettingInterface::Impl
        {
            Impl()
            {
                _currentUser["Name"] = "Deep In Sight";
                _currentUser["Email"] = "dinsight@dinsight.ai";
                _currentDevice["Model Name"] = "Dimenvue";
                _currentDevice["Serial Number"] = "0123456789ABCDEF";
                _currentDevice["Firmware Version"] = "0.0.1";
            }

            std::vector<std::string> getSSIDList()
            {
                return {"wifi", "wifi1", "wifi2"};
            }

            bool connectWifi(const std::string &ssid, const std::string &password)
            {
                std::this_thread::sleep_for(std::chrono::seconds(1));
                if (ssid == "wifi" && password == "password")
                {
                    _currentSSID = ssid;
                    return true;
                }
                return false;
            }

            bool userLogin(const std::string &user, const std::string &password)
            {
                std::this_thread::sleep_for(std::chrono::seconds(1));
                if (user == "user" && password == "password")
                {
                    return true;
                }
                return false;
            }

            UserInfo _currentUser;
            DeviceInfo _currentDevice;
            std::string _currentSSID;
        };

        SettingInterface::SettingInterface() : _impl(new Impl) {}
        SettingInterface::~SettingInterface() = default;

        const std::vector<std::string> SettingInterface::getSSIDList()
        {
            return _impl->getSSIDList();
        }

        std::future<bool> SettingInterface::connectWifiAsync(const std::string &ssid, const std::string &password)
        {
            return std::async(std::launch::async, [this, ssid, password]
                              { return _impl->connectWifi(ssid, password); });
        }

        const std::string &SettingInterface::getCurrentWifiSSID()
        {
            return _impl->_currentSSID;
        }

        std::future<bool> SettingInterface::userLoginAsync(const std::string &user, const std::string &password)
        {
            return std::async(std::launch::async, [this, user, password]
                              { return _impl->userLogin(user, password); });
        }

        const UserInfo &SettingInterface::getUserInfo()
        {
            return _impl->_currentUser;
        }

        const DeviceInfo &SettingInterface::getDeviceInfo()
        {
            return _impl->_currentDevice;
        }
    } // namespace backend
} // namespace dimenvue
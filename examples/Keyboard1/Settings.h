// Settings.h
#ifndef SETTINGS_H
#define SETTINGS_H

#include <Preferences.h> // For NVS storage; use LittleFS if preferred

class Settings {
private:
    static Settings instance; // The single instance
    char deviceName[32];      // Fixed-size array for heap efficiency
    char wifiSSID[32];        // Fixed-size array for heap efficiency
    Preferences prefs;        // NVS storage handler

    // Private constructor to prevent multiple instances
    Settings() {
        strcpy(deviceName, "ESP32_Device"); // Default value
        strcpy(wifiSSID, "MyWiFi");         // Default value
    }

    // Save settings to NVS
    void saveToNVS() {
        prefs.begin("app_settings", false); // Open NVS in read-write mode
        prefs.putString("device_name", deviceName);
        prefs.putString("wifi_ssid", wifiSSID);
        prefs.end();
    }

    // Load settings from NVS
    void loadFromNVS() {
        prefs.begin("app_settings", true); // Open NVS in read-only mode
        prefs.getString("device_name", deviceName, sizeof(deviceName));
        prefs.getString("wifi_ssid", wifiSSID, sizeof(wifiSSID));
        prefs.end();
    }

public:
    // Get the single instance
    static Settings& getInstance() {
        return instance;
    }

    // Initialize settings (call once in setup())
    void begin() {
        loadFromNVS(); // Load saved settings on startup
    }

    // Getters (read-only access)
    const char* getDeviceName() const { return deviceName; }
    const char* getWifiSSID() const { return wifiSSID; }

    // Setters (modify and save automatically)
    void setDeviceName(const char* name) {
        strncpy(deviceName, name, sizeof(deviceName) - 1);
        deviceName[sizeof(deviceName) - 1] = '\0'; // Ensure null termination
        saveToNVS(); // Persist changes
    }

    void setWifiSSID(const char* ssid) {
        strncpy(wifiSSID, ssid, sizeof(wifiSSID) - 1);
        wifiSSID[sizeof(wifiSSID) - 1] = '\0'; // Ensure null termination
        saveToNVS(); // Persist changes
    }
};

// Declare the global reference
extern Settings& settings;

#endif
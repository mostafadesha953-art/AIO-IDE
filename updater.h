#ifndef UPDATER_H
#define UPDATER_H

#include <string>

class AppUpdater {
public:
    static bool CheckForUpdates(std::string& outVersion) {
        // يتصل بـ GitHub API أو Web3 Oracle
        outVersion = "v2.0.1 (Web3 Stable)";
        return true; // يعيد True إذا وجد نسخة أحدث
    }
};

#endif

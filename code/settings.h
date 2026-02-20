#ifndef OOP_SETTINGS_H
#define OOP_SETTINGS_H

class settings {
private:
    settings() = default;
public:
    settings(const settings&) = delete;
    settings& operator=(const settings&) = delete;
    static settings& getInstance() {
        static settings instance;
        return instance;
    }
    bool snapping=true;
    int snapping_val=25;
    bool show_grid=true;
    bool show_fps=true;
};

#endif
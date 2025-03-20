#pragma once
// clay
#include <clay/application/desktop/AppDesktop.h>

class DemoApp : public clay::AppDesktop {
public:
    DemoApp();

    void loadResources() override;
};
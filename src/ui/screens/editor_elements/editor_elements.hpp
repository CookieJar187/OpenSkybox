#pragma once

#include <iostream>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "state.hpp"
#include "config.hpp"

namespace EditorElements
{
    // File menu bar
    class FileMenuBarUi
    {
    private:
        State *state;

    public:
        FileMenuBarUi(State *state);
        void build();
    };

    // SkyConfig Elements
    namespace PropertiesUiElement
    {
        // SkyConfig > Atmosphere
        class AtmosphereUi
        {
        private:
            State *state;
            Config *config;

        public:
            AtmosphereUi(
                State *state,
                Config *config
            );
            void build();
        };

        // SkyConfig > Sun
        class SunUi
        {
        private:
            State *state;
            Config *config;

        public:
            SunUi(
                State *state,
                Config *config
            );
            void build();
        };

        // SkyConfig > Clouds
        class CloudsUi
        {
        private:
            State *state;
            Config *config;

        public:
            CloudsUi(
                State *state,
                Config *config
            );
            void build();
        };
    }

    // SkyConfig
    class PropertiesUi
    {
    private:
        State *state;
        Config *config;

        PropertiesUiElement::AtmosphereUi atmosphereUi{
            state,
            config
        };
        PropertiesUiElement::SunUi sunUi{
            state,
            config
        };
        PropertiesUiElement::CloudsUi cloudsUi{
            state,
            config
        };

    public:
        PropertiesUi(
            State *state,
            Config *config
        );
        void build();
    };

    // Camera settings
    class CameraSettingsUi
    {
    private:
        Config *config;

    public:
        CameraSettingsUi(Config *config);
        void build();
    };
}
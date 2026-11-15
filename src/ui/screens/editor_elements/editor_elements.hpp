#pragma once

#include <iostream>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "state.hpp"
#include "properties.hpp"

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

    // Properties Elements
    namespace PropertiesUiElement
    {
        // Properties > Atmosphere
        class AtmosphereUi
        {
        private:
            State *state;
            ::Properties *properties;

        public:
            AtmosphereUi(
                State *state,
                ::Properties *properties
            );
            void build();
        };

        // Properties > Sun
        class SunUi
        {
        private:
            State *state;
            ::Properties *properties;

        public:
            SunUi(
                State *state,
                ::Properties *properties
            );
            void build();
        };

        // Properties > Clouds
        class CloudsUi
        {
        private:
            State *state;
            ::Properties *properties;

        public:
            CloudsUi(
                State *state,
                ::Properties *properties
            );
            void build();
        };
    }

    // Properties
    class PropertiesUi
    {
    private:
        State *state;
        ::Properties *properties;

        PropertiesUiElement::AtmosphereUi atmosphereUi{
            state,
            properties
        };
        PropertiesUiElement::SunUi sunUi{
            state,
            properties
        };
        PropertiesUiElement::CloudsUi cloudsUi{
            state,
            properties
        };

    public:
        PropertiesUi(
            State *state,
            ::Properties *properties
        );
        void build();
    };
}
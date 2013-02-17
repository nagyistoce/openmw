#ifndef MWGUI_WINDOW_PINNABLE_BASE_H
#define MWGUI_WINDOW_PINNABLE_BASE_H

#include "window_base.hpp"

namespace MWGui
{
    class WindowManager;

    class WindowPinnableBase: public WindowBase
    {
    public:
        WindowPinnableBase(const std::string& parLayout, MWBase::WindowManager& parWindowManager);
        bool pinned() { return mPinned; }

    private:
        void onWindowButtonPressed(MyGUI::Window* sender, const std::string& eventName);

    protected:
        virtual void onPinToggled() = 0;

        MyGUI::Widget* mPinButton;
        bool mPinned;
        bool mVisible;
    };
}

#endif

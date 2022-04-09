////////////////////////////////////////////////////////////////////////////////
// Galaxian clone
//
// Copyright (c) 2022 Kwena Mashamaite (kwena.mashamaite1@gmail.com)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
////////////////////////////////////////////////////////////////////////////////

#ifndef GALAXIAN_CLOSABLEPANEL_H
#define GALAXIAN_CLOSABLEPANEL_H

#include <IME/ui/widgets/Panel.h>

namespace gui {
    /**
     * @brief A panel with a close button
     */
    class ClosablePanel : public ime::ui::Panel {
    public:
        /**
         * @brief Constructor
         * @param width Width of the panel relative to the size of its
         *        parent
         * @param height Height of the panel relative to the size of its
         *        parent
         * @return The new Panel
         *
         * * The relative size is specified in percentages as shown:
         *
         * @code
         * auto panel = ClosablePanel({"50%", "20%"});
         * @endcode
         *
         * By default, the new panel is the same size as its parent
         */
        explicit ClosablePanel(const std::string& width = "100%", const std::string& height = "100%");

        /**
         * @brief Close the panel
         *
         * Note that closing the panel hides it and invokes the 'onClose'
         * handlers. This is the default behavior of the panels close
         * button
         *
         * @see onClose
         */
        void close();

        /**
         * @brief Execute callback when the panel is closed
         * @param callback The function to be executed when the panel is closed
         *
         * The panel can be closed by clicking the panels close button or by
         * calling the close() function
         *
         * @see close
         */
        void onClose(const ime::Callback<>& callback);

    private:
        std::string m_closeBtnName;
    };
}

#endif //GALAXIAN_CLOSABLEPANEL_H

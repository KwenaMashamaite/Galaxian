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

#ifndef GALAXIAN_FLAGSHIP_H
#define GALAXIAN_FLAGSHIP_H

#include "Galaxian.h"
#include <vector>

class Escort;

/**
 * @brief An enemy attack ship that is accompanied by at most, two Escort
 *        ships as defense
 */
class Flagship : public Galaxian {
public:
    /**
     * @brief Constructor
     * @param scene The scene the flagship belongs to
     */
    explicit Flagship(ime::Scene& scene);

    /**
     * @brief Assign an escort to the flagship
     * @param escort The escort to be assigned
     * @return True if the escort was added or false of it was rejected
     *
     * @note The escort will be rejected if it is already escorting
     * another flagship or it has already dived without a flagship or
     * when this flagship has already met the maximum number of escorts
     *
     * @warning @a escort must not be a @a nullptr
     *
     * @see removeEscort
     */
    bool addEscort(Escort* escort);

    /**
     * @brief Remove an escort from the flagship
     * @param escort The escort to be removed
     *
     * @warning @a escort must not be a @a nullptr
     *
     * @see addEscort
     */
    void removeEscort(Escort* escort);

    /**
     * @brief Get the flagships escorts
     * @return The flagships escorts
     */
    std::vector<Escort*> getEscorts() const;

    /**
     * @brief Get the number of escorts currently escorting the flagship
     * @return The number of the flagships current escorts
     */
    unsigned int getEscortCount() const;

    /**
     * @brief Check if an escort ship is currently escorting this flagship
     * @param escort The escort to be checked
     * @return True if the flagship is currently escorted by the specified
     *         escort ship, false otherwise
     *
     * @warning @a escort must not be a @a nullptr
     */
    bool isEscortedBy(Escort* escort) const;

    /**
     * @brief Check if the flagship is currently being escorted or not
     * @return True if escorted, false otherwise
     */
    bool isEscorted() const;

    /**
     * @brief Get the maximum number of escorts a flagship is allowed
     * @return The maximum number of escorts a flagship can have
     */
    static unsigned int getMaxNumEscorts();

    /**
     * @brief Get the name of the class
     * @return The name of the class as declared
     */
    std::string getClassName() const override;

private:
    std::vector<Escort*> m_escorts; //!< Escorts
};

#endif //GALAXIAN_FLAGSHIP_H

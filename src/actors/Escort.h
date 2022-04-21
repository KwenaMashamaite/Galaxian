#ifndef GALAXIAN_ESCORT_H
#define GALAXIAN_ESCORT_H

#include "Galaxian.h"

class Flagship;

/**
 * @brief An enemy attack ship that can serve as an escort for a Flagship (red galaxian)
 */
class Escort : public Galaxian {
public:
    /**
     * @brief Constructor
     * @param scene The scene the escort belongs to
     */
    explicit Escort(ime::Scene& scene);

    /**
     * @brief Check if this escort ship is currently escorting a flagship
     * @return True if currently escorting a flagship, false otherwise
     *
     * By default, the ship is not escorting
     */
    bool isEscorting() const;

    /**
     * @brief Set the flagship to escort
     * @param flagship The flagship to be escorted
     *
     * Note that an escort ship can only escort one flagship at a time.
     * Furthermore an escort can only happen if both the flagship and
     * the escort ship are in formation.
     *
     * By default, the flagship is nullptr. That is, the ship is not escorting
     *
     * @warning @a flagship must not be a nullptr
     *
     * @see getFlagship
     */
    void setFlagship(Flagship* flagship);

    /**
     * @brief Get the flagship being escorted
     * @return The escorted flagship
     *
     * @see setFlagship
     */
    Flagship* flagship();
    const Flagship* flagship() const;

    /**
     * @brief Get the points awarded to the player when an escort is shot down
     * @return Points the player scored by shooting down the escort ship
     */
    int getPoints() const override;

    /**
     * @brief Get the name of the class
     * @return The name of the class as declared
     */
    std::string getClassName() const override;

    /**
     * @brief Dive towards the player
     * @param deltaTime Time passed since last dive update
     */
    void dive(float deltaTime) override;

private:
    Flagship* m_flagship;
};

#endif //GALAXIAN_ESCORT_H

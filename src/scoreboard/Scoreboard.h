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

#ifndef GALAXIAN_SCOREBOARD_H
#define GALAXIAN_SCOREBOARD_H

#include "Score.h"
#include <vector>
#include <string>
#include <functional>

/**
 * @brief A class for loading/saving Score's from/to the disk
 */
class Scoreboard {
public:
    /**
     * @brief Constructor
     * @param path The path to the scores file on the disk
     * @param filename The name of the file that contains the scores
     *
     * @a filename must not be preceded by the path
     */
    Scoreboard(const std::string& path, const std::string &filename);

    /**
     * @brief Load scores from a file on the disk
     * @throws std::runtime_error if the specified file cannot be opened
     *         for reading
     *
     * The scores will be loaded from the file specified during
     * instantiation
     *
     * @see save
     */
    void load();

    /**
     * @brief Write scores to a file on the disk
     * @throws std::runtime_error if the specified file cannot be opened
     *         for writing
     *
     * Note that this function will overwrite the file the scores
     * were read from
     *
     * @see load
     */
    void save();

    /**
     * @brief Add a score
     * @param score The score to be added
     *
     * The scoreboard is automatically sorted after the score is added.
     * Furthermore, the scores are sorted in descending order
     *
     * @see addScores
     */
    void addScore(const Score &score);

    /**
     * @brief Add multiple scores
     * @param scores The scores to be added
     *
     * The scoreboard is automatically sorted after the scores are added.
     * Furthermore, the scores are sorted in descending order
     *
     * @see addScore
     */
    void addScores(const std::vector<Score>& scores);

    /**
     * @brief Get the score with the highest value
     * @return A score with the highest value
     *
     * @warning The scoreboard must not be empty
     */
    const Score& getTopScore() const;

    /**
     * @brief Get the number of scores in the Scoreboard
     * @return The number of scores in the Scoreboard
     */
    std::size_t getScoreCount() const;

    /**
     * @brief Execute a callback for each score in the Scoreboard
     * @param callback The function to be executed
     */
    void forEach(std::function<void(const Score&)> callback);

private:
    std::vector<Score> m_highScores; //!< High scores read from dis
    std::string m_path;              //!< The path to the high scores file to be read/written
    std::string m_filename;          //!< The name of the high scores file to be read/written
};

#endif

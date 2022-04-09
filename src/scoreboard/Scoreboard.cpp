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

#include "Scoreboard.h"
#include <algorithm>
#include <fstream>
#include <filesystem>
#include <exception>

///////////////////////////////////////////////////////////////
void sort(std::vector<Score> vec) {
    std::sort(vec.begin(), vec.end(), std::greater<>());
}

///////////////////////////////////////////////////////////////
Scoreboard::Scoreboard(const std::string &path, const std::string &filename) :
    m_path(path),
    m_filename(filename)
{
    if (!std::filesystem::exists(m_path))
        std::filesystem::create_directory(m_path);
}

///////////////////////////////////////////////////////////////
void Scoreboard::load() {
    std::ifstream infile(m_path + "/" + m_filename, std::ios::in | std::ios::binary);

    if (infile.is_open()) {
        infile.seekg(0, std::ios::end);
        auto numRecords = infile.tellg() / sizeof(Score);
        infile.seekg(0, std::ios::beg);

        Score score;

        for (int i = 0; i < numRecords; i++) {
            infile.read(reinterpret_cast<char *>(&score), sizeof(Score));
            m_highScores.push_back(score);
        }

        infile.close();
    } else
        throw std::runtime_error("Failed to open high score file '" + m_path + "/" + m_filename + "' for reading");
}

///////////////////////////////////////////////////////////////
void Scoreboard::save() {
    std::ofstream outfile(m_path + "/" + m_filename, std::ios::out | std::ios::binary);

    if (outfile.is_open()) {
        for (auto& highScore : m_highScores)
            outfile.write(reinterpret_cast<char*>(&highScore), sizeof(Score));

        outfile.close();
    } else
        throw std::runtime_error("Failed to open high score file '" + m_path + "/" + m_filename + "' for writing");
}

///////////////////////////////////////////////////////////////
void Scoreboard::addScore(const Score &score) {
    m_highScores.emplace_back(score);
    sort(m_highScores);
}

///////////////////////////////////////////////////////////////
void Scoreboard::addScores(const std::vector<Score> &scores) {
    if (!scores.empty()) {
        for (auto &score: scores)
            m_highScores.emplace_back(score);

        sort(m_highScores);
    }
}

///////////////////////////////////////////////////////////////
const Score& Scoreboard::getTopScore() const {
    return m_highScores.front();
}

///////////////////////////////////////////////////////////////
std::size_t Scoreboard::getScoreCount() const {
    return m_highScores.size();
}

///////////////////////////////////////////////////////////////
void Scoreboard::forEach(std::function<void(const Score&)> callback) {
    for (const auto& score : m_highScores)
        callback(score);
}

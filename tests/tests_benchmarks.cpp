//
// Created by robin on 13.01.2021.
//

#include "../external_libs/catch.hpp"
#include "../include/external/nlohmann.hpp"
#include "../include/external/picojson.hpp"
#include "../include/external/gason.hpp"
#include "../include/tileson.h"

//Must be defined after Tileson
#include "../include/json/Gason.hpp"

TEST_CASE( "Run benchmarks on all supported json-backends + Gason", "[json][benchmarks]" )
{
    fs::path pathLocal {"../../content/test-maps/ultimate_test.json"};
    fs::path pathTravis {"../content/test-maps/ultimate_test.json"};
    fs::path pathToUse = (fs::exists(pathLocal)) ? pathLocal : pathTravis;

    tson::Tileson nlohmann {std::make_unique<tson::NlohmannJson>()};
    tson::Tileson picojson {std::make_unique<tson::PicoJson>()};
    tson::Tileson g {std::make_unique<tson::Gason>()};
    tson::Tileson j11 {std::make_unique<tson::Json11>()};

    auto startNlohmann = std::chrono::steady_clock::now();
    auto nlohmannMap = nlohmann.parse(pathToUse);
    auto endNlohmann = std::chrono::steady_clock::now();
    std::chrono::duration<double> msNlohmann = (endNlohmann-startNlohmann) * 1000;

    auto startPicoJson = std::chrono::steady_clock::now();
    auto picojsonMap = picojson.parse(pathToUse);
    auto endPicoJson = std::chrono::steady_clock::now();
    std::chrono::duration<double> msPicoJson = (endPicoJson-startPicoJson) * 1000;

    auto startGason = std::chrono::steady_clock::now();
    auto gasonMap = g.parse(pathToUse);
    auto endGason = std::chrono::steady_clock::now();
    std::chrono::duration<double> msGason = (endGason-startGason) * 1000;

    auto startJ11 = std::chrono::steady_clock::now();
    auto j11Map = j11.parse(pathToUse);
    auto endJ11 = std::chrono::steady_clock::now();
    std::chrono::duration<double> msJ11 = (endJ11-startJ11) * 1000;

    std::cout << "Nlohmann parse time: " << msNlohmann.count() << " ms\n";
    std::cout << "PicoJson parse time: " << msPicoJson.count() << " ms\n";
    std::cout << "Gason parse time: " << msGason.count() << " ms\n";
    std::cout << "Json11 parse time: " << msJ11.count() << " ms\n";

    REQUIRE(nlohmannMap->getStatus() == tson::ParseStatus::OK);
    REQUIRE(picojsonMap->getStatus() == tson::ParseStatus::OK);
    REQUIRE(gasonMap->getStatus() == tson::ParseStatus::OK);
}